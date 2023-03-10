
#include "DocumentServer.h"
#include "DocumentServerMessages.refl.meta.h"

#include <sb/vector.h>
#include <filesystem>
#include <cstdarg>

#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormDataChangePacket.h"

#include "StormSockets/StormSocketBackend.h"
#include "StormSockets/StormSocketServerFrontendWebsocket.h"

#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/Document/Document.h"

#include "DocumentServerVCSGit.refl.meta.h"
#include "DocumentServerVCSPerforce.refl.meta.h"

namespace fs = std::filesystem;

DocumentServer::DocumentServer() :
  m_DocumentCompiler(this),
  m_AddRequests(65536),
  m_AddResponses(65536),
  m_CheckoutRequests(1024),
  m_CheckoutResponses(1024),
  m_StatusQueries(8092),
  m_StatusQueryResponses(8092)
{
  m_RootPath = GetCanonicalRootPath();
  m_FilesystemWatcher = std::make_unique<FileSystemWatcher>(m_RootPath, [this] { m_Semaphore.Release(1); });

  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.NumIOThreads = 1;
  backend_settings.NumSendThreads = 1;

  m_Backend = std::make_unique<StormSockets::StormSocketBackend>(backend_settings);

  StormSockets::StormSocketServerFrontendWebsocketSettings document_server_settings;
  document_server_settings.ListenSettings.Port = 27800;
  document_server_settings.EventSemaphore = &m_Semaphore;

  StormSockets::StormSocketServerFrontendWebsocketSettings asset_server_settings;
  asset_server_settings.ListenSettings.Port = 27801;
  asset_server_settings.EventSemaphore = &m_Semaphore;

  StormSockets::StormSocketServerFrontendWebsocketSettings reload_server_settings;
  reload_server_settings.ListenSettings.Port = 27802;
  reload_server_settings.EventSemaphore = &m_Semaphore;

  StormSockets::StormSocketServerFrontendWebsocketSettings compiler_server_settings;
  compiler_server_settings.ListenSettings.Port = 27803;
  compiler_server_settings.EventSemaphore = &m_Semaphore;
  
  m_DocServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(document_server_settings, m_Backend.get());
  m_AssetServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(asset_server_settings, m_Backend.get());
  m_ReloadServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(reload_server_settings, m_Backend.get());
  m_CompilerServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(compiler_server_settings, m_Backend.get());

  auto vcs_settings = FileReadFullAsString("vcs_settings.txt");
  DocumentServerVCSInitData init_data;

  StormReflParseJson(init_data, vcs_settings.c_str());

  switch(init_data.Type)
  {
  default:
  case DocumentServerVCSType::Git:
    m_VCS = std::make_unique<DocumentServerVCSGit>();
    break;
#ifdef ENABLE_PERFORCE
  case DocumentServerVCSType::Perforce:
    m_VCS = std::make_unique<DocumentServerVCSPerforce>();
    break;
#endif
  }

  auto project_dir = FileReadFullAsString("project_dir.txt");
  if(project_dir.empty())
  {
    project_dir = ".";
  }

  while(isspace(project_dir.back()) || project_dir.back() == 0)
  {
    project_dir.pop_back();
  }

  auto project_dir_path = fs::canonical(project_dir);
  m_VCS->Init(vcs_settings, project_dir_path.string(), m_RootPath, [this](const std::string & msg) { Log("VCS Error: %s", msg.c_str()); });

  m_VCSThread = std::thread([this]() { VCSThread(); });
}

DocumentServer::~DocumentServer()
{
  m_DocServerFrontend.release();
  m_AssetServerFrontend.release();
  m_ReloadServerFrontend.release();
  m_CompilerServerFrontend.release();
  m_Backend.release();
}

void DocumentServer::Run()
{
  while (m_Quit == false)
  {
    m_Semaphore.WaitOne();

    StormSockets::StormSocketEventInfo event_info;
    while (m_DocServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientConnected)
      {
        HandleDocumentClientConnected(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        Log("Got document handshake complete");
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Data)
      {
        HandleDocumentClientData(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        HandleDocumentClientDisconnected(event_info);
      }
    }

    while (m_AssetServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientConnected)
      {
        Log("Got asset server connection");
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Data)
      {
        HandleAssetClientData(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        HandleAssetClientDisconnect(event_info);
      }
    }

    while (m_ReloadServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        HandleReloadClientConnected(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        HandleReloadClientDisconnected(event_info);
      }
    }

    while (m_CompilerServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientConnected)
      {
        HandleCompilerClientConnect(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Data)
      {
        HandleCompilerClientData(event_info);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        HandleCompilerClientDisconnect(event_info);
      }
    }

    ProcessFileSystemChanges();
    ProcessVersionControl();
  }
}

void DocumentServer::ProcessVersionControl()
{
  DocumentServerVCSQuery query;
  while(m_StatusQueryResponses.TryDequeue(query))
  {
    // Do something with these?
  }

  DocumentServerVCSOperation resp;
  while(m_AddResponses.TryDequeue(resp))
  {
    if(resp.m_Success)
    {
      Log("VCS Added file %s", resp.m_FilePath.c_str());
    }
  }

  while(m_CheckoutResponses.TryDequeue(resp))
  {
    auto itr = m_OpenDocuments.find(crc32(resp.m_FilePath));
    if(itr != m_OpenDocuments.end())
    {
      if (resp.m_Success)
      {
        itr->second.m_Document->Save(m_RootPath);
      }
      else
      {
        for(auto & con : itr->second.m_Connections)
        {
          SendMessageToClient(DocumentClientMessageType::kCheckoutError, con.m_ConnectionId, con.m_DocumentId, resp.m_FilePath);
        }
      }
    }
  }
}

void DocumentServer::ProcessFileSystemChanges()
{
  while (true)
  {
    auto changed_file = m_FilesystemWatcher->GetFileChange();
    if (!changed_file)
    {
      break;
    }

    auto type = std::get<0>(changed_file.Value());
    auto path = std::get<1>(changed_file.Value());
    auto file = std::get<2>(changed_file.Value());
    auto last_modified = std::get<3>(changed_file.Value());

    switch (type)
    {
    case FileSystemOperation::kAdd:
      Log("Added File %s", file.data());
      m_FileNameDatabase.Insert(file.data(), path.data());
      break;
    case FileSystemOperation::kDelete:
      Log("Removed File %s", file.data());
      m_FileNameDatabase.Remove(file.data(), path.data());
      HandleDocumentRemoved(path.data());
      break;
    case FileSystemOperation::kModify:
      Log("Modified File %s", file.data());
      HandleDocumentModified(path.data(), last_modified);
      break;
    default:
      break;
    }

    auto full_path = GetFullPath(path);
    Hash file_hash = crc32(full_path);
    auto itr = m_CachedAssets.find(file_hash);

    if (itr != m_CachedAssets.end())
    {
      if (type == FileSystemOperation::kDelete)
      {
        m_CachedAssets.erase(itr);
      }
      else
      {
        bool retry = true;
        int attempts = 0;
        while (retry)
        {
          File file = FileOpen(full_path.data(), FileOpenMode::kRead);

          if (file.GetFileOpenError())
          {
            if (file.GetFileOpenError() != 13)
            {
              Log("Error File %s", path.data());
              retry = false;
              break;
            }

            attempts++;
            if (attempts > 10)
            {
              Log("Error File %s", path.data());
              retry = false;
              break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
          }
          else
          {
            itr->second = file.ReadFileFull();
            break;
          }
        }

        if (retry == false)
        {
          continue;
        }
      }
    }

    auto response = m_ReloadServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
    auto reload_packet = path;
    response.WriteByteBlock(reload_packet.data(), 0, reload_packet.size());
    m_ReloadServerFrontend->FinalizeOutgoingPacket(response);

    for (auto connection_id : m_ReloadConnections)
    {
      m_ReloadServerFrontend->SendPacketToConnection(response, connection_id);
      Log("Served file change: %s", reload_packet.data());
    }

    m_ReloadServerFrontend->FreeOutgoingPacket(response);
  }
}

void DocumentServer::Log(const char * fmt, ...)
{
  char buf[8092];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  buf[sizeof(buf) - 1] = 0;
  printf("%s\n", buf);

  m_Log.emplace_back(buf);
  if(m_Log.size() > 1000)
  {
    m_Log.pop_front();
  }

  va_end(args);
}

void DocumentServer::LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback)
{
  auto full_path = GetFullPath(path);

  File file = FileOpen(full_path.data(), FileOpenMode::kRead);
  if (file.GetFileOpenError() != 0)
  {
    callback(file_hash, nullptr, 0, time_t{});
    return;
  }

  auto buffer = file.ReadFileFull();
  FileClose(file);

  callback(file_hash, buffer.Get(), buffer.GetSize(), GetLastWriteTime(path));
}

std::string DocumentServer::GetFullPath(const std::string & path)
{
  if (fs::path(path).is_absolute())
  {
    return path;
  }
  else
  {
    return ::GetFullPath(path, m_RootPath);
  }
}

void DocumentServer::HandleDocumentChange(uint32_t file_hash, Document * document, const ReflectionChangeNotification & change)
{
  auto doc_itr = m_OpenDocuments.find(file_hash);
  if (doc_itr == m_OpenDocuments.end())
  {
    return;
  }

  doc_itr->second.m_PendingChanges.emplace_back(change);

  auto change_itr = m_PendingChangedDocuments.find(document->GetFileId());
  if (change_itr == m_PendingChangedDocuments.end())
  {
    m_PendingChangedDocuments.emplace(file_hash, &doc_itr->second);
  }
}

void DocumentServer::HandleDocumentStateChange(uint32_t file_hash, Document * document, DocumentState state, DocumentState prev_state)
{
  auto doc_itr = m_OpenDocuments.find(file_hash);
  if (doc_itr == m_OpenDocuments.end())
  {
    return;
  }

  std::string document_state = std::to_string((int)document->GetState());
  document_state += ' ';
  document_state += std::to_string(doc_itr->second.m_DataGen);
  doc_itr->second.m_DataGen++;

  if (state == DocumentState::kLoaded)
  {
    document_state += ' ';
    document_state += document->GetDocumentJson();
  }

  for (auto client : doc_itr->second.m_Connections)
  {
    SendMessageToClient(DocumentClientMessageType::kDocumentState, client.m_ConnectionId, client.m_DocumentId, document_state);
  }
}

void DocumentServer::HandleDocumentLinksModified(uint32_t file_hash, Document * document)
{
  auto doc_itr = m_OpenDocuments.find(file_hash);
  if (doc_itr == m_OpenDocuments.end())
  {
    return;
  }

  auto packet = StormReflEncodeJson(document->GetLinks());

  for (auto client : doc_itr->second.m_Connections)
  {
    SendMessageToClient(DocumentClientMessageType::kChangeLinks, client.m_ConnectionId, client.m_DocumentId, packet);
  }
}

void DocumentServer::OpenDocumentForClient(czstr path, uint32_t document_id, StormSockets::StormSocketConnectionId client_id)
{
  auto file_hash = crc32lowercase(path);
  auto itr = m_OpenDocuments.find(file_hash);

  auto document = m_DocumentCompiler.GetDocument(path);
  if (itr == m_OpenDocuments.end())
  {
    auto last_write = GetLastWriteTime(path);

    auto result = m_OpenDocuments.emplace(std::make_pair(file_hash, DocumentServerDocumentInfo{ document, 1, last_write }));
    itr = result.first;

    document->SetChangeHandler(Document::DocumentChangeHandler(&DocumentServer::HandleDocumentChange, this));
    document->SetStateChangeHandler(Document::DocumentStateChangeHandler(&DocumentServer::HandleDocumentStateChange, this));
    document->SetLinksChangeHandler(Document::DocumentLinksChangeHandler(&DocumentServer::HandleDocumentLinksModified, this));
    document->AddRef();
  }

  itr->second.m_Connections.emplace_back(DocumentServerDocumentClient{ client_id, document_id });

  auto client = m_DocServerClients.find(client_id);
  if (client == m_DocServerClients.end())
  {
    return;
  }

  client->second.m_DocumentList.emplace_back(DocumentServerClientDocument{ file_hash, document_id });

  auto links_packet = StormReflEncodeJson(document->GetLinks());
  SendMessageToClient(DocumentClientMessageType::kChangeLinks, client_id, document_id, links_packet);

  std::string document_state = std::to_string((int)document->GetState());
  document_state += ' ';
  document_state += std::to_string(itr->second.m_DataGen);

  if (document->GetState() == DocumentState::kLoaded)
  {
    document_state += ' ';
    document_state += document->GetDocumentJson();
  }

  SendMessageToClient(DocumentClientMessageType::kDocumentState, client_id, document_id, document_state);
}

void DocumentServer::SendPendingChanges()
{
  for (auto & val : m_PendingChangedDocuments)
  {
    if (val.second->m_Document->GetState() != DocumentState::kLoaded)
    {
      continue;
    }

    std::vector<std::string> changes;
    for (auto & change : val.second->m_PendingChanges)
    {
      changes.emplace_back(StormDataCreateChangePacket(change));
    }

    val.second->m_PendingChanges.clear();

    std::string data_gen = std::to_string(val.second->m_DataGen);
    std::string change_packet = StormReflEncodeJson(changes);

    for (auto & client : val.second->m_Connections)
    {
      std::string document_id = std::to_string(client.m_DocumentId);

      auto writer = m_DocServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
      writer.WriteByteBlock("kChange ", 0, 8);
      writer.WriteByteBlock(document_id.data(), 0, document_id.length());
      writer.WriteByte(' ');
      writer.WriteByteBlock(data_gen.data(), 0, data_gen.length());
      writer.WriteByte(' ');
      writer.WriteByteBlock(change_packet.data(), 0, change_packet.size());
      m_DocServerFrontend->FinalizeOutgoingPacket(writer);

      m_DocServerFrontend->SendPacketToConnectionBlocking(writer, client.m_ConnectionId);
      m_DocServerFrontend->FreeOutgoingPacket(writer);
    }

    val.second->m_DataGen++;
  }

  m_PendingChangedDocuments.clear();
}

NullOptPtr<DocumentServerDocumentInfo> DocumentServer::GetDocumentForClient(uint32_t document_id, StormSockets::StormSocketConnectionId client_id)
{
  auto client = m_DocServerClients.find(client_id);
  if (client == m_DocServerClients.end())
  {
    return nullptr;
  }

  for (auto & doc : client->second.m_DocumentList)
  {
    if (doc.m_DocumentId == document_id)
    {
      auto doc_itr = m_OpenDocuments.find(doc.m_FileId);
      if (doc_itr == m_OpenDocuments.end())
      {
        return nullptr;
      }

      return &doc_itr->second;
    }
  }

  return nullptr;
}

void DocumentServer::HandleDocumentModified(czstr path, time_t last_modified)
{
  auto file_id = crc32lowercase(path);

  auto doc_itr = m_OpenDocuments.find(file_id);
  if (doc_itr != m_OpenDocuments.end())
  {
    if (doc_itr->second.m_LastModifiedTime < last_modified)
    {
      m_DocumentCompiler.ReloadDocument(path);
      SendPendingChanges();
    }
  }
  else
  {
    m_DocumentCompiler.ReloadDocument(path);
    SendPendingChanges();
  }
}

void DocumentServer::HandleDocumentRemoved(czstr path)
{
  auto file_id = crc32lowercase(path);

  auto doc_itr = m_OpenDocuments.find(file_id);
  if (doc_itr != m_OpenDocuments.end())
  {
    for (std::size_t index = 0, end = doc_itr->second.m_Connections.size(); index < end; index++)
    {
      auto dead_client_id = doc_itr->second.m_Connections[index].m_ConnectionId;
      auto dead_client_itr = m_DocServerClients.find(dead_client_id);
      if (dead_client_itr != m_DocServerClients.end())
      {
        for (std::size_t index = 0, end = dead_client_itr->second.m_DocumentList.size(); index < end; index++)
        {
          if (dead_client_itr->second.m_DocumentList[index].m_FileId == file_id)
          {
            vremove_index_quick(dead_client_itr->second.m_DocumentList, index);
            break;
          }
        }

        SendMessageToClient(DocumentClientMessageType::kDocumentClosed, dead_client_id, doc_itr->second.m_Connections[index].m_DocumentId, "");
      }
    }

    doc_itr->second.m_Document->DecRef();
    m_OpenDocuments.erase(doc_itr);
  }
}

bool DocumentServer::ProcessMessage(StormSockets::StormSocketConnectionId client_id, char * msg, std::size_t length)
{
  const char * start_msg = msg;

  Log("%s", msg);

  Hash hash = crc32begin();
  while (length > 0)
  {
    if (*msg == ' ' || *msg == 0)
    {
      break;
    }

    hash = crc32additive(hash, *msg);
    msg++;
  }

  hash = crc32end(hash);
  msg++;

  if (length == 0)
  {
    return false;
  }

  DocumentServerMessageType type = DocumentServerMessageType::kUnknown;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    return false;
  }

  if(type == DocumentServerMessageType::kShutdown)
  {
    for(auto & doc : m_OpenDocuments)
    {
      doc.second.m_Document->Save(m_RootPath);
    }

    m_Quit = true;
    m_Semaphore.Release(1);
    return true;
  }

  uint32_t document_id = std::strtoul(msg, &msg, 10);
  if (document_id == 0)
  {
    return false;
  }

  msg++;

  switch (type)
  {
  case DocumentServerMessageType::kNew:
    {
      const char * file_name = msg;
      auto full_path = GetFullPath(file_name);
      auto file = FileOpen(full_path.data(), FileOpenMode::kRead);

      if (file.GetFileOpenError() != 0)
      {
        auto new_file = FileOpen(full_path.data(), FileOpenMode::kWrite);
        if (new_file.GetFileOpenError() != 0)
        {
          SendMessageToClient(DocumentClientMessageType::kNewFileError, client_id, document_id, std::to_string(new_file.GetFileOpenError()));
          return true;
        }

        new_file.Write(Document::CreateEmptyFile());
        FileClose(new_file);
      }
      else
      {
        FileClose(file);
      }

      OpenDocumentForClient(file_name, document_id, client_id);
      m_AddRequests.Enqueue(file_name);
      m_AddedAssets.emplace(crc32(file_name));
    }
    break;
  case DocumentServerMessageType::kOpen:
    {
      const char * file_name = msg;
      auto full_path = GetFullPath(file_name);
      auto file = FileOpen(full_path.data(), FileOpenMode::kRead);

      if (file.GetFileOpenError() != 0)
      {
        SendMessageToClient(DocumentClientMessageType::kOpenFileError, client_id, document_id, std::to_string(file.GetFileOpenError()));
        return true;
      }
      else
      {
        FileClose(file);
      }

      OpenDocumentForClient(file_name, document_id, client_id);
      if(m_AddedAssets.find(crc32(file_name)) == m_AddedAssets.end())
      {
        m_AddRequests.Enqueue(file_name);
        m_AddedAssets.emplace(crc32(file_name));
      }
    }
    break;
  case DocumentServerMessageType::kChange:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document == nullptr)
      {
        break;
      }

      std::vector<std::pair<int, std::string>> change_list;
      if (StormReflParseJson(change_list, msg) == false)
      {
        break;
      }

      DocumentServerDocumentClient * doc_client = nullptr;
      for (auto & client : document->m_Connections)
      {
        if (client.m_ConnectionId == client_id)
        {
          doc_client = &client;
        }
      }

      if (doc_client == nullptr)
      {
        break;
      }

      for (auto & change : change_list)
      {
        auto type = std::get<0>(change);
        auto & change_packet = std::get<1>(change);

        if(type == 0)
        {
          ReflectionChangeNotification change_notification;

          StormDataParseChangePacket(change_notification, change_packet.data());

          document->m_Document->ApplyChange(change_notification);
        }
        if (type == 1)
        {
          std::tuple<std::string, std::string, std::string> link_data;
          StormReflParseJson(link_data, change_packet.data());

          auto & src_document = std::get<0>(link_data);
          auto & src_path = std::get<1>(link_data);
          auto & dst_path = std::get<2>(link_data);

          document->m_Document->AddLink(src_document.data(), src_path.data(), dst_path.data());
        }
        else if (type == 2)
        {
          std::tuple<std::string, std::string, std::string> link_data;
          StormReflParseJson(link_data, change_packet.data());

          auto & src_document = std::get<0>(link_data);
          auto & src_path = std::get<1>(link_data);
          auto & dst_path = std::get<2>(link_data);

          auto file_id = crc32lowercase(src_document);
          document->m_Document->RemoveLink(file_id, src_path.data(), dst_path.data());
        }
      }

      document->m_Document->CommitUndo();
      SendPendingChanges();

      SendMessageToClient(DocumentClientMessageType::kChangeOk, client_id, document_id, "");

      auto response = m_ReloadServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
      auto reload_packet = document->m_Document->GetPath();
      response.WriteByteBlock(reload_packet.data(), 0, reload_packet.size());
      m_ReloadServerFrontend->FinalizeOutgoingPacket(response);

      for (auto connection_id : m_ReloadConnections)
      {
        m_ReloadServerFrontend->SendPacketToConnection(response, connection_id);
        Log("Document file change: %s\n", reload_packet.data());
      }

      m_ReloadServerFrontend->FreeOutgoingPacket(response);

    }
    break;
  case DocumentServerMessageType::kClose:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document == nullptr)
      {
        break;
      }

      for (std::size_t index = 0, end = document->m_Connections.size(); index < end; index++)
      {
        if (document->m_Connections[index].m_ConnectionId == client_id)
        {
          vremove_index_quick(document->m_Connections, index);
          break;
        }
      }

      auto client_itr = m_DocServerClients.find(client_id);
      if (client_itr != m_DocServerClients.end())
      {
        for (std::size_t index = 0, end = client_itr->second.m_DocumentList.size(); index < end; index++)
        {
          if (client_itr->second.m_DocumentList[index].m_FileId == document->m_Document->GetFileId())
          {
            vremove_index_quick(client_itr->second.m_DocumentList, index);
            break;
          }
        }
      }

      if (document->m_Connections.size() == 0)
      {
        auto file_id = document->m_Document->GetFileId();
        document->m_Document->Save(m_RootPath);
        document->m_Document->DecRef();
        m_OpenDocuments.erase(file_id);
      }

      SendMessageToClient(DocumentClientMessageType::kDocumentClosed, client_id, document_id, "");
    }
    break;

  case DocumentServerMessageType::kDelete:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document)
      {
        FileDelete(document->m_Document->GetPath().data());
      }
    }
    break;

  case DocumentServerMessageType::kSave:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document)
      {
        if(document->m_Document->Save(m_RootPath))
        {
          document->m_LastModifiedTime = time(nullptr);
        }
        else
        {
          if(m_CheckedOutAssets.find(document->m_Document->GetFileId()) != m_CheckedOutAssets.end())
          {
            m_CheckoutRequests.Enqueue(document->m_Document->GetPath());
            m_CheckedOutAssets.emplace(document->m_Document->GetFileId());
          }
        }
      }
    }
    break;
  case DocumentServerMessageType::kUndo:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document)
      {
        document->m_Document->Undo();
      }

      SendPendingChanges();
    }
    break;
  case DocumentServerMessageType::kRedo:
    {
      auto document = GetDocumentForClient(document_id, client_id);
      if (document)
      {
        document->m_Document->Redo();
      }

      SendPendingChanges();
    }
    break;
  default:
    break;
  }

  return true;
}

void DocumentServer::SendMessageToClient(DocumentClientMessageType type, StormSockets::StormSocketConnectionId client_id, uint32_t document_id, const std::string & packet)
{
  std::string data;
  data.reserve(1024);
  data += StormReflGetEnumAsString(type);
  data += ' ';
  data += std::to_string(document_id);
  data += ' ';
  data += packet;

  auto writer = m_DocServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(data.data(), 0, data.size());
  m_DocServerFrontend->FinalizeOutgoingPacket(writer);
  m_DocServerFrontend->SendPacketToConnection(writer, client_id);
  m_DocServerFrontend->FreeOutgoingPacket(writer);
}

void DocumentServer::VCSThread()
{
  std::vector<DocumentServerVCSQuery> status_queries;
  std::vector<DocumentServerVCSOperation> add_requests;

  while(m_Quit == false)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    status_queries.clear();

    DocumentServerVCSQuery query;
    while(m_StatusQueries.TryDequeue(query))
    {
      status_queries.emplace_back(std::move(query));
    }

    if(status_queries.size() > 0)
    {
      m_VCS->GetStatus(status_queries);
      for(auto & elem : status_queries)
      {
        m_StatusQueryResponses.Enqueue(std::move(elem));
      }
    }

    std::string req;
    add_requests.clear();

    while(m_AddRequests.TryDequeue(req))
    {
      add_requests.emplace_back(DocumentServerVCSOperation{ std::move(req) });
    }

    if(add_requests.size())
    {
      m_VCS->Add(add_requests);
      for(auto & elem : add_requests)
      {
        m_AddResponses.Enqueue(std::move(elem));
      }
    }

    while(m_CheckoutRequests.TryDequeue(req))
    {
      DocumentServerVCSOperation resp;
      resp.m_FilePath = req;
      resp.m_Success = m_VCS->Checkout(req);
      m_CheckoutResponses.Enqueue(std::move(resp));
    }
  }
}


void DocumentServer::HandleCompilerClientConnect(StormSockets::StormSocketEventInfo & event_info)
{
  Log("Got compiler server connection");
  m_CompileServerClients.emplace(event_info.ConnectionId, CompilerServerClientInfo{event_info.ConnectionId });
}

void DocumentServer::HandleCompilerClientData(StormSockets::StormSocketEventInfo & event_info)
{
  std::vector<char> recv_buffer;
  recv_buffer.resize(event_info.GetWebsocketReader().GetDataLength() + 1);
  event_info.GetWebsocketReader().ReadByteBlock(recv_buffer.data(), event_info.GetWebsocketReader().GetDataLength());
  recv_buffer[event_info.GetWebsocketReader().GetDataLength()] = 0;

  char * path = recv_buffer.data();
  auto path_hash = crc32lowercase(path);

  Log("Got compiler server request: %s", path);

  Document * document = nullptr;

  auto client_info = m_CompileServerClients.find(event_info.ConnectionId);
  if (client_info == m_CompileServerClients.end())
  {
    Log("Ignoring request due to client not in active clients list");
    return;
  }

  for(auto & elem : client_info->second.m_FileIds)
  {
    if (elem.second == path_hash)
    {
      document = elem.first;
      break;
    }
  }

  if (document == nullptr)
  {
    document = m_DocumentCompiler.GetDocument(path);
    document->AddRef();
    client_info->second.m_FileIds.emplace_back(document, path_hash);
  }

  if (document->GetState() != DocumentState::kLoaded)
  {
    auto response = m_CompilerServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
    m_CompilerServerFrontend->FinalizeOutgoingPacket(response);
    m_CompilerServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
    m_CompilerServerFrontend->FreeOutgoingPacket(response);

    Log("Error File %s", path);
    return;
  }

  auto json = document->GetDocumentJson();

  auto response = m_CompilerServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
  response.WriteByteBlock(json.data(), 0, json.size());
  m_CompilerServerFrontend->FinalizeOutgoingPacket(response);
  m_CompilerServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
  m_CompilerServerFrontend->FreeOutgoingPacket(response);

  Log("Served File %s", path);
}

void DocumentServer::HandleCompilerClientDisconnect(StormSockets::StormSocketEventInfo & event_info)
{
  auto client_info = m_CompileServerClients.find(event_info.ConnectionId);
  if (client_info != m_CompileServerClients.end())
  {
    for (auto elem : client_info->second.m_FileIds)
    {
      elem.first->DecRef();
    }

    m_CompileServerClients.erase(client_info);
  }

  Log("Lost compiler server connection");
  m_DocServerFrontend->FinalizeConnection(event_info.ConnectionId);
}

void DocumentServer::HandleDocumentClientConnected(const StormSockets::StormSocketEventInfo & event_info)
{
  Log("Got document server connection");

  uint32_t connection_id = event_info.ConnectionId;
  m_DocServerClients.emplace(connection_id, DocumentServerClientInfo{});
}

void DocumentServer::HandleDocumentClientData(StormSockets::StormSocketEventInfo & event_info)
{
  if (m_RecvBufferSize < event_info.GetWebsocketReader().GetDataLength() + 1)
  {
    m_RecvBuffer = std::make_unique<char[]>(event_info.GetWebsocketReader().GetDataLength() + 1);
    m_RecvBufferSize = event_info.GetWebsocketReader().GetDataLength() + 1;
  }

  int packet_length = event_info.GetWebsocketReader().GetDataLength();
  m_RecvBuffer[packet_length] = 0;

  event_info.GetWebsocketReader().ReadByteBlock(m_RecvBuffer.get(), event_info.GetWebsocketReader().GetDataLength());
  ProcessMessage(event_info.ConnectionId, m_RecvBuffer.get(), event_info.GetWebsocketReader().GetDataLength());
}

void DocumentServer::HandleDocumentClientDisconnected(StormSockets::StormSocketEventInfo & event_info)
{
  Log("Lost document server connection");

  uint32_t connection_id = event_info.ConnectionId;
  auto client_itr = m_DocServerClients.find(connection_id);
  if (client_itr != m_DocServerClients.end())
  {
    for (auto & doc : client_itr->second.m_DocumentList)
    {
      auto doc_itr = m_OpenDocuments.find(doc.m_FileId);
      if (doc_itr != m_OpenDocuments.end())
      {
        for (std::size_t index = 0, end = doc_itr->second.m_Connections.size(); index < end; index++)
        {
          if (doc_itr->second.m_Connections[index].m_ConnectionId == connection_id)
          {
            vremove_index_quick(doc_itr->second.m_Connections, index);
            break;
          }
        }

        if (doc_itr->second.m_Connections.empty())
        {
          doc_itr->second.m_Document->Save(m_RootPath);
          doc_itr->second.m_Document->DecRef();
          m_OpenDocuments.erase(doc_itr);
        }
      }
    }

    m_DocServerClients.erase(client_itr);
  }

  m_DocServerFrontend->FinalizeConnection(event_info.ConnectionId);
}

void DocumentServer::HandleAssetClientData(StormSockets::StormSocketEventInfo & event_info)
{
  std::vector<char> recv_buffer;
  recv_buffer.resize(event_info.GetWebsocketReader().GetDataLength() + 1);
  event_info.GetWebsocketReader().ReadByteBlock(recv_buffer.data(), event_info.GetWebsocketReader().GetDataLength());
  recv_buffer[event_info.GetWebsocketReader().GetDataLength()] = 0;

  char * path = recv_buffer.data();

  auto full_path = GetFullPath(path);
  Hash file_hash = crc32(full_path);

  auto cache_itr = m_CachedAssets.find(file_hash);
  if (cache_itr == m_CachedAssets.end())
  {
    File file = FileOpen(full_path.data(), FileOpenMode::kRead);

    if (file.GetFileOpenError())
    {
      char error_str[20];
      int str_len = snprintf(error_str, sizeof(error_str), "%d", file.GetFileOpenError());

      auto response = m_AssetServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
      response.WriteByteBlock(error_str, 0, str_len);
      m_AssetServerFrontend->FinalizeOutgoingPacket(response);
      m_AssetServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
      m_AssetServerFrontend->FreeOutgoingPacket(response);

      Log("Error File %s", path);
      return;
    }
    else
    {
      auto result = m_CachedAssets.emplace(file_hash, file.ReadFileFull());
      cache_itr = result.first;

      if(m_AddedAssets.find(file_hash) == m_AddedAssets.end())
      {
        m_AddRequests.Enqueue(path);
        m_AddedAssets.emplace(file_hash);
      }
    }
  }

  auto response = m_AssetServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
  response.WriteByteBlock(cache_itr->second.Get(), 0, cache_itr->second.GetSize());
  m_AssetServerFrontend->FinalizeOutgoingPacket(response);
  m_AssetServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
  m_AssetServerFrontend->FreeOutgoingPacket(response);

  Log("Served File %s", path);
}

void DocumentServer::HandleAssetClientDisconnect(StormSockets::StormSocketEventInfo & event_info)
{
  Log("Lost asset server connection");
  m_DocServerFrontend->FinalizeConnection(event_info.ConnectionId);
}

void DocumentServer::HandleReloadClientConnected(const StormSockets::StormSocketEventInfo & event_info)
{
  Log("Got reload server connection");
  m_ReloadConnections.push_back(event_info.ConnectionId);
}

void DocumentServer::HandleReloadClientDisconnected(StormSockets::StormSocketEventInfo & event_info)
{
  vremove_quick(m_ReloadConnections, event_info.ConnectionId);
  m_ReloadServerFrontend->FinalizeConnection(event_info.ConnectionId);
  Log("Lost reload server connection");
}
