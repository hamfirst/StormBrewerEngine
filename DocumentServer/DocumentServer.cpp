
#include "DocumentServer.h"
#include "DocumentServerMessages.refl.meta.h"

#include <sb/vector.h>

#include <StormRefl/StormReflJsonStd.h>

#include <StormSockets/StormSocketBackend.h>
#include <StormSockets/StormSocketServerFrontendWebsocket.h>

#include <Foundation/FileSystem/File.h>

DocumentServer::DocumentServer() 
{
  m_Semaphore.Init(0);
  m_FilesystemWatcher = std::make_unique<FileSystemWatcher>(m_Semaphore);

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
  
  m_DocServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(document_server_settings, m_Backend.get());
  m_AssetServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(asset_server_settings, m_Backend.get());
  m_ReloadServerFrontend = std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(reload_server_settings, m_Backend.get());
}

DocumentServer::~DocumentServer()
{

}

void DocumentServer::Run()
{
  std::vector<char> recv_buffer;
  while (m_Quit == false)
  {
    StormSockets::StormSocketEventInfo event_info;
    m_Semaphore.WaitOne();
    
    while (m_DocServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientConnected)
      {
        printf("Got document server connection\n");
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        printf("Got document handshake complete\n");
        //m_OpenConnections.push_back(event_info.ConnectionId);
        //for (auto & doc : m_OpenDocuments)
        //{
        //  DocumentServerMessageOpen packet;
        //  packet.m_DocumentId = doc.first;
        //  packet.m_FileName = doc.second.m_Document.GetFileName();
        //  packet.m_FileType = doc.second.m_Document.GetFileType();
        //  packet.m_Data = doc.second.m_Document.SerializeFull();
        //  packet.m_EditorData = doc.second.m_EditorData;
        //  packet.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
        //  packet.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
        //  packet.m_State.m_IsModified = doc.second.m_Document.IsModified();

        //  SendMessageToClient(event_info.ConnectionId, packet);
        //}

        DocumentServerMessageInitComplete response;
        response.m_Version = kDocumentServerVersion;
        SendMessageToClient(event_info.ConnectionId, response);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Data)
      {
        //if (m_RecvBufferSize < event_info.GetWebsocketReader().GetDataLength() + 1)
        //{
        //  m_RecvBuffer = std::make_unique<char[]>(event_info.GetWebsocketReader().GetDataLength() + 1);
        //  m_RecvBufferSize = event_info.GetWebsocketReader().GetDataLength() + 1;
        //}

        //event_info.GetWebsocketReader().ReadByteBlock(m_RecvBuffer.get(), event_info.GetWebsocketReader().GetDataLength() + 1);
        //ProcessMessage(event_info.ConnectionId, m_RecvBuffer.get(), event_info.GetWebsocketReader().GetDataLength() + 1);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        printf("Lost document server connection\n");
        //vremove_quick(m_OpenConnections, event_info.ConnectionId);
        m_DocServerFrontend->FinalizeConnection(event_info.ConnectionId);
      }
    }

    while (m_AssetServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientConnected)
      {
        printf("Got asset server connection\n");
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Data)
      {
        recv_buffer.resize(event_info.GetWebsocketReader().GetDataLength() + 1);
        event_info.GetWebsocketReader().ReadByteBlock(recv_buffer.data(), event_info.GetWebsocketReader().GetDataLength());
        recv_buffer[event_info.GetWebsocketReader().GetDataLength()] = 0;        

        char * path = recv_buffer.data();
        Hash file_hash = crc32(path);

        auto cache_itr = m_CachedAssets.find(file_hash);
        if (cache_itr == m_CachedAssets.end())
        {
          File file = FileOpen(path, FileOpenMode::kRead);

          if (file.GetFileOpenError())
          {
            char error_str[20];
            int str_len = snprintf(error_str, sizeof(error_str), "%d", file.GetFileOpenError());

            auto response = m_AssetServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
            response.WriteByteBlock(error_str, 0, str_len);
            m_AssetServerFrontend->FinalizeOutgoingPacket(response);
            m_AssetServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
            m_AssetServerFrontend->FreeOutgoingPacket(response);

            printf("Error File %s\n", path);
            continue;
          }
          else
          {
            auto result = m_CachedAssets.emplace(std::make_pair(file_hash, file.ReadFileFull()));
            cache_itr = result.first;
          }
        }

        auto response = m_AssetServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
        response.WriteByteBlock(cache_itr->second.Get(), 0, cache_itr->second.GetSize());
        m_AssetServerFrontend->FinalizeOutgoingPacket(response);
        m_AssetServerFrontend->SendPacketToConnection(response, event_info.ConnectionId);
        m_AssetServerFrontend->FreeOutgoingPacket(response);

        printf("Served File %s\n", path);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        printf("Lost asset server connection\n");
        m_DocServerFrontend->FinalizeConnection(event_info.ConnectionId);
      }
    }

    while (m_ReloadServerFrontend->GetEvent(event_info))
    {
      if (event_info.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        printf("Got reload server connection\n");
        m_ReloadConnections.push_back(event_info.ConnectionId);
      }
      else if (event_info.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        vremove_quick(m_ReloadConnections, event_info.ConnectionId);
        m_ReloadServerFrontend->FinalizeConnection(event_info.ConnectionId);
        printf("Lost reload server connection\n");
      }
    }

    while (true)
    {
      auto changed_file = m_FilesystemWatcher->GetFileChange();
      if (!changed_file)
      {
        break;
      }


      Hash file_hash = crc32(changed_file->second);
      auto itr = m_CachedAssets.find(file_hash);
      if (itr != m_CachedAssets.end())
      {
        if (changed_file->first == FileSystemOperation::kDelete)
        {
          m_CachedAssets.erase(itr);
        }
        else
        {
          bool retry = true;
          int attempts = 0;
          while (retry)
          {
            File file = FileOpen(changed_file->second.data(), FileOpenMode::kRead);

            if (file.GetFileOpenError())
            {
              if (file.GetFileOpenError() != 13)
              {
                printf("Error File %s\n", changed_file->second.data());
                retry = false;
                break;
              }

              attempts++;
              if (attempts > 10)
              {
                printf("Error File %s\n", changed_file->second.data());
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
      response.WriteByteBlock(changed_file->second.data(), 0, changed_file->second.size());
      m_ReloadServerFrontend->FinalizeOutgoingPacket(response);

      for (auto connection_id : m_ReloadConnections)
      {
        m_ReloadServerFrontend->SendPacketToConnection(response, connection_id);
        printf("Served file change: %s\n", changed_file->second.data());
      }

      m_ReloadServerFrontend->FreeOutgoingPacket(response);
    }
  }
}

bool DocumentServer::ProcessMessage(StormSockets::StormSocketConnectionId client_id, char * msg, std::size_t length)
{
  //const char * start_msg = msg;

  //Hash hash = crc32begin();
  //while (length > 0)
  //{
  //  if (*msg == ' ' || *msg == 0)
  //  {
  //    break;
  //  }

  //  hash = crc32additive(hash, *msg);
  //  msg++;
  //}

  //hash = crc32end(hash);
  //msg++;

  //if (length == 0)
  //{
  //  return false;
  //}

  //DocumentServerMessageType type = DocumentServerMessageType::kUnknown;
  //if (StormReflGetEnumFromHash(type, hash) == false)
  //{
  //  return false;
  //}

  //switch (type)
  //{
  //case DocumentServerMessageType::kCreateRequest:
  //  {
  //    DocumentServerMessageCreateRequest packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    if (FileExists(packet.m_FileName.data()))
  //    {
  //      DocumentServerMessageOpenError error;
  //      error.m_FileName = packet.m_FileName;
  //      error.m_FileType = packet.m_FileType;
  //      error.m_Error = "File already exists";
  //      SendMessageToClient(client_id, error);
  //    }
  //    else
  //    {
  //      File file = FileOpen(packet.m_FileName.data(), FileOpenMode::kWrite);
  //      if (file.GetFileOpenError())
  //      {
  //        DocumentServerMessageOpenError error;
  //        error.m_FileName = packet.m_FileName;
  //        error.m_FileType = packet.m_FileType;
  //        error.m_Error = "Could not open file";
  //        SendMessageToClient(client_id, error);
  //      }
  //      else
  //      {
  //        m_OpenDocuments.emplace(std::make_pair(m_NextDocumentId, DocumentData{ Document(packet.m_FileName, packet.m_FileType, packet.m_Data) }));

  //        DocumentServerMessageOpen response;
  //        response.m_DocumentId = m_NextDocumentId;
  //        response.m_FileName = packet.m_FileName;
  //        response.m_FileType = packet.m_FileType;
  //        response.m_Data = packet.m_Data;
  //        response.m_EditorData = "";
  //        SendMessageToAllClients(response);
  //        m_NextDocumentId++;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kOpenRequest:
  //  {
  //    DocumentServerMessageOpenRequest packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    File file = FileOpen(packet.m_FileName.data(), FileOpenMode::kRead);
  //    if (file.GetFileOpenError())
  //    {
  //      DocumentServerMessageOpenError error;
  //      error.m_FileName = packet.m_FileName;
  //      error.m_FileType = packet.m_FileType;
  //      error.m_Error = "Could not open file";
  //      SendMessageToClient(client_id, error);
  //    }
  //    else
  //    {
  //      DocumentServerMessageFinalizeRequest response;
  //      response.m_FileName = packet.m_FileName;
  //      response.m_FileType = packet.m_FileType;
  //      response.m_Data.resize(file.GetFileLength() + 1);
  //      file.Read(gsl::span<uint8_t>((uint8_t *)response.m_Data.data(), file.GetFileLength()), file.GetFileLength());
  //      SendMessageToClient(client_id, response);
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kOpenFinalizeReponse:
  //  {
  //    DocumentServerMessageFinalizeResponse packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    // Make sure this guy isn't already open
  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_FileName == doc.second.m_Document.GetFileName())
  //      {
  //        return true;
  //      }
  //    }

  //    m_OpenDocuments.emplace(std::make_pair(m_NextDocumentId, DocumentData{ Document(packet.m_FileName, packet.m_FileType, packet.m_Data) }));

  //    DocumentServerMessageOpen response;
  //    response.m_DocumentId = m_NextDocumentId;
  //    response.m_FileName = packet.m_FileName;
  //    response.m_FileType = packet.m_FileType;
  //    response.m_Data = packet.m_Data;
  //    response.m_EditorData = "";
  //    SendMessageToAllClients(response);
  //    m_NextDocumentId++;
  //  }
  //  break;
  //case DocumentServerMessageType::kSetEditorData:
  //  {
  //    DocumentServerMessageSetEditorData packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_DocumentId == doc.first)
  //      {
  //        doc.second.m_EditorData = packet.m_EditorData;
  //        break;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kChangeRequest:
  //  {
  //    DocumentServerMessageChangeRequest packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    DocumentChangeList change_notifications;
  //    for (auto & change_data : packet.m_Changes)
  //    {
  //      ReflectionChangeNotification notification;
  //      if (StormDataParseChangePacket(notification, change_data.data()))
  //      {
  //        change_notifications.emplace_back(std::move(notification));
  //      }
  //    }

  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_DocumentId == doc.first)
  //      {
  //        doc.second.m_Document.ApplyChanges(change_notifications);

  //        DocumentServerMessageApplyChange response;
  //        response.m_DocumentId = packet.m_DocumentId;
  //        response.m_Changes = std::move(packet.m_Changes);
  //        response.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
  //        response.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
  //        response.m_State.m_IsModified = doc.second.m_Document.IsModified();

  //        SendMessageToAllClientsExcept(client_id, response);

  //        DocumentServerMessageChangeState change_state;
  //        change_state.m_DocumentId = packet.m_DocumentId;
  //        change_state.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
  //        change_state.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
  //        change_state.m_State.m_IsModified = doc.second.m_Document.IsModified();
  //        SendMessageToClient(client_id, change_state);
  //        break;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kUndo:
  //  {
  //    DocumentServerMessageUndo packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_DocumentId == doc.first)
  //      {
  //        DocumentChangeList applied_changes;
  //        doc.second.m_Document.Undo(applied_changes);

  //        std::vector<std::string> change_list;
  //        for (auto & change : applied_changes)
  //        {
  //          change_list.emplace_back(StormDataCreateChangePacket(change));
  //        }

  //        DocumentServerMessageApplyChange response;
  //        response.m_DocumentId = packet.m_DocumentId;
  //        response.m_Changes = std::move(change_list);
  //        response.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
  //        response.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
  //        response.m_State.m_IsModified = doc.second.m_Document.IsModified();
  //        SendMessageToAllClients(response);
  //        break;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kRedo:
  //  {
  //    DocumentServerMessageUndo packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_DocumentId == doc.first)
  //      {
  //        DocumentChangeList applied_changes;
  //        doc.second.m_Document.Redo(applied_changes);

  //        std::vector<std::string> change_list;
  //        for (auto & change : applied_changes)
  //        {
  //          change_list.emplace_back(StormDataCreateChangePacket(change));
  //        }

  //        DocumentServerMessageApplyChange response;
  //        response.m_DocumentId = packet.m_DocumentId;
  //        response.m_Changes = std::move(change_list);
  //        response.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
  //        response.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
  //        response.m_State.m_IsModified = doc.second.m_Document.IsModified();
  //        SendMessageToAllClients(response);
  //        break;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kSave:
  //  {
  //    DocumentServerMessageSave packet;
  //    if (StormReflParseJson(packet, msg) == false)
  //    {
  //      return false;
  //    }

  //    for (auto & doc : m_OpenDocuments)
  //    {
  //      if (packet.m_DocumentId == doc.first)
  //      {
  //        File file = FileOpen(doc.second.m_Document.GetFileName().data(), FileOpenMode::kWrite);
  //        if (file.GetFileOpenError())
  //        {
  //          DocumentServerMessageSaveError error;
  //          error.m_DocumentId = packet.m_DocumentId;
  //          error.m_Error = "Could not save file!";
  //          SendMessageToClient(client_id, error);
  //          break;
  //        }

  //        std::string full_data = doc.second.m_Document.SerializeFull();
  //        file.Write(gsl::span<uint8_t>((uint8_t *)full_data.data(), full_data.size()), full_data.length());

  //        doc.second.m_Document.ResetModified();

  //        DocumentServerMessageChangeState change_state;
  //        change_state.m_DocumentId = packet.m_DocumentId;
  //        change_state.m_State.m_HasUndo = doc.second.m_Document.HasUndo();
  //        change_state.m_State.m_HasRedo = doc.second.m_Document.HasRedo();
  //        change_state.m_State.m_IsModified = doc.second.m_Document.IsModified();
  //        SendMessageToAllClients(change_state);
  //        break;
  //      }
  //    }
  //  }
  //  break;
  //case DocumentServerMessageType::kClose:
  //  break;
  //}

  return true;
}

template <typename T>
void DocumentServer::SendMessageToClient(StormSockets::StormSocketConnectionId client_id, const T & packet)
{
  std::string data = StormReflGetEnumAsString(T::Type);
  data += " ";
  data += StormReflEncodeJson(packet);

  auto writer = m_DocServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(data.data(), 0, data.size());
  m_DocServerFrontend->FinalizeOutgoingPacket(writer);
  m_DocServerFrontend->SendPacketToConnection(writer, client_id);
  m_DocServerFrontend->FreeOutgoingPacket(writer);
}

template <typename T>
void DocumentServer::SendMessageToAllClients(const T & packet)
{
  std::string data = StormReflGetEnumAsString(T::Type);
  data += " ";
  data += StormReflEncodeJson(packet);

  auto writer = m_DocServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(data.data(), 0, data.size());
  m_DocServerFrontend->FinalizeOutgoingPacket(writer);

  for (auto client_id : m_OpenConnections)
  {
    m_DocServerFrontend->SendPacketToConnection(writer, client_id);
  }

  m_DocServerFrontend->FreeOutgoingPacket(writer);
}

template <typename T>
void DocumentServer::SendMessageToAllClientsExcept(StormSockets::StormSocketConnectionId except_client_id, const T & packet)
{
  std::string data = StormReflGetEnumAsString(T::Type);
  data += " ";
  data += StormReflEncodeJson(packet);

  auto writer = m_DocServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(data.data(), 0, data.size());
  m_DocServerFrontend->FinalizeOutgoingPacket(writer);

  for (auto client_id : m_OpenConnections)
  {
    if (client_id != except_client_id)
    {
      m_DocServerFrontend->SendPacketToConnection(writer, client_id);
    }
  }

  m_DocServerFrontend->FreeOutgoingPacket(writer);
}