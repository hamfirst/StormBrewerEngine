
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/Buffer/BufferUtil.h"
#include "Foundation/Document/Document.h"

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Settings/EngineSettings.refl.h"

#ifndef _WEB
#include <experimental/filesystem>
#endif

#define USE_WEBSOCKET_LOADING


AssetLoader g_AssetLoader;
static AssetReloadInfo * s_AssetReloadList = nullptr;
static bool s_DisableNetworkLoading = false;

static std::string s_AssetServerHost = "localhost";

AssetLoader::AssetLoader() :
#ifndef _WEB
  m_LoadRequests(1024),
  m_LoadResponses(1024),
  m_ModifiedFiles(2048),
#endif
  m_DocumentCompiler(this)
{

}

AssetLoader::~AssetLoader()
{
  ShutDown();
}

void AssetLoader::Init()
{
  m_Running = true;
  m_RootPath = GetCanonicalRootPath();

#ifndef _WEB

  m_LoaderThreads = std::make_unique<std::thread[]>(g_EngineSettings.m_AssetLoadThreads);
  for (int index = 0; index < g_EngineSettings.m_AssetLoadThreads; index++)
  {
    m_LoaderThreads[index] = std::thread(&AssetLoader::LoadThread, this);
  }

#ifdef USE_WEBSOCKET_LOADING
  m_ReloadServerSocket = std::make_unique<WebSocket>();
  m_ReloadThread = std::thread(&AssetLoader::ReloadThread, this);
#endif

#else

#ifdef USE_WEBSOCKET_LOADING
  m_LoaderSocket = std::make_unique<WebSocket>();
  m_LoaderSocket->StartConnect(s_AssetServerHost.data(), 27801, "/", "localhost");

  m_CompilerSocket = std::make_unique<WebSocket>();
  m_CompilerSocket->StartConnect(s_AssetServerHost.data(), 27803, "/", "localhost");

  m_ReloadServerSocket = std::make_unique<WebSocket>();
  m_ReloadServerSocket->StartConnect(s_AssetServerHost.data(), 27802, "/", "localhost");
#endif

#endif
}

void AssetLoader::ShutDown()
{
  if (m_Running == false)
  {
    return;
  }

#ifndef _WEB
  m_Running = false;
  m_LoadSemaphore.Release(g_EngineSettings.m_AssetLoadThreads);

  for (int index = 0; index < g_EngineSettings.m_AssetLoadThreads; index++)
  {
    m_LoaderThreads[index].join();
  }

  m_ReloadServerSocket->Close();
  m_ReloadThread.join();
#else

  m_LoaderSocket->Close();
  m_CompilerSocket->Close();
  m_ReloadServerSocket->Close();

#endif
}

void AssetLoader::RequestFileLoad(Asset * asset, czstr file_path, bool as_document, bool as_reload)
{
  asset->IncRef();

  AssetLoadRequest req_data{ asset, file_path, as_document, as_reload };

#ifndef _WEB
  while (m_LoadRequests.Enqueue(std::move(req_data)) == false)
  {
    std::this_thread::yield();
  }

  m_LoadSemaphore.Release();
#else

  m_PendingRequests.push(req_data);

#endif
}

void AssetLoader::ProcessResponses()
{
#ifdef _WEB

  if (m_ReloadServerSocket->IsConnected() == false)
  {
    if (m_ReloadServerSocket->IsConnecting() == false)
    {
      m_ReloadServerSocket->StartConnect(s_AssetServerHost.data(), 27802, "/", "localhost");
    }
  }
  else
  {
    while (true)
    {
      auto packet = m_ReloadServerSocket->PollPacket();
      if (!packet)
      {
        break;
      }

      ReloadFile(BufferToString(packet->m_Buffer).data());
    }
  }

  if (m_LoaderSocket->IsConnected())
  {
    while (true)
    {
      auto packet = m_LoaderSocket->PollPacket();
      if (packet)
      {
        auto req_data = std::move(m_PendingLoads.front());
        m_PendingLoads.pop();

        AssetLoadResponse resp;
        if (packet->m_Type == WebSocketPacketType::kText)
        {
          req_data.m_Asset->m_LoadError = 1;
          resp = AssetLoadResponse{ req_data.m_Asset, req_data.m_AsDocument, req_data.m_AsReload };
        }
        else
        {
          //printf("Got remote asset file: %s (%d)\n", req_data.m_FilePath.data(), packet->m_Buffer.GetSize());
          req_data.m_Asset->m_LoadError = req_data.m_Asset->PreProcessLoadedData(packet->m_Buffer);
          resp = AssetLoadResponse{ req_data.m_Asset, req_data.m_AsDocument, req_data.m_AsReload, std::move(packet->m_Buffer) };
        }

        FinalizeAssetResponse(resp);
      }
      else
      {
        break;
      }
    }
  }
  else if (m_LoaderSocket->IsConnecting() == false && m_PendingLoads.size() > 0)
  {
    while (m_PendingLoads.size() > 0)
    {
      m_PendingRequests.push(std::move(m_PendingLoads.front()));
      m_PendingLoads.pop();
    }
  }

  if (m_CompilerSocket->IsConnected())
  {
    while (true)
    {
      auto packet = m_CompilerSocket->PollPacket();
      if (packet)
      {
        auto req_data = std::move(m_PendingCompiles.front());
        m_PendingCompiles.pop();

        AssetLoadResponse resp;
        if (packet->m_Type == WebSocketPacketType::kText)
        {
          req_data.m_Asset->m_LoadError = 1;
          resp = AssetLoadResponse{ req_data.m_Asset, req_data.m_AsDocument, req_data.m_AsReload };
        }
        else
        {
          //printf("Got remote document file: %s (%d)\n", req_data.m_FilePath.data(), packet->m_Buffer.GetSize());
          req_data.m_Asset->m_LoadError = req_data.m_Asset->PreProcessLoadedData(packet->m_Buffer);
          resp = AssetLoadResponse{ req_data.m_Asset, req_data.m_AsDocument, req_data.m_AsReload, std::move(packet->m_Buffer) };
        }

        FinalizeAssetResponse(resp);
      }
      else
      {
        break;
      }
    }
  }
  else if (m_CompilerSocket->IsConnecting() == false && m_PendingCompiles.size() > 0)
  {
    while (m_PendingCompiles.size() > 0)
    {
      m_PendingRequests.push(std::move(m_PendingCompiles.front()));
      m_PendingCompiles.pop();
    }
  }

#ifdef USE_WEBSOCKET_LOADING
  if (m_LoaderSocket->IsConnected() && m_CompilerSocket->IsConnected())
  {
    m_DelayRequests = false;
  }

  if (m_LoaderSocket->IsConnecting() == false || m_CompilerSocket->IsConnecting() == false)
  {
    m_DelayRequests = false;
  }

  if (m_LoaderSocket->IsConnected() == false && m_LoaderSocket->IsConnecting() == false)
  {
    ConnectLoaderWebsocket(*m_LoaderSocket.get());
  }

  if (m_CompilerSocket->IsConnected() == false && m_CompilerSocket->IsConnecting() == false)
  {
    ConnectCompilerWebsocket(*m_CompilerSocket.get());
  }

  if (m_DelayRequests && s_DisableNetworkLoading == false)
  {
    return;
  }
#endif

  while (m_PendingRequests.size() > 0)
  {
    auto req_data = std::move(m_PendingRequests.front());
    m_PendingRequests.pop();

    auto asset = req_data.m_Asset;

    Optional<Buffer> buffer;
    if (req_data.m_AsDocument)
    {
#ifdef USE_WEBSOCKET_LOADING
        if (s_DisableNetworkLoading == false)
        {
          if (m_CompilerSocket->IsConnected())
          {
            //printf("Requesting remote document: %s\n", req_data.m_FilePath.data());
            m_CompilerSocket->SendString(req_data.m_FilePath);
            m_PendingCompiles.push(std::move(req_data));
            continue;
          }
        }
#endif

      buffer = LoadFullDocumentRaw(req_data.m_FilePath.data(), req_data.m_Asset->m_LoadError);
    }
    else
    {
#ifdef USE_WEBSOCKET_LOADING
      if (s_DisableNetworkLoading == false)
      {
        if (m_LoaderSocket->IsConnected())
        {
          //printf("Requesting remote file: %s\n", req_data.m_FilePath.data());
          m_LoaderSocket->SendString(req_data.m_FilePath);
          m_PendingLoads.push(std::move(req_data));
          continue;
        }
      }
#endif

      buffer = LoadFullFileRaw(req_data.m_FilePath.data(), req_data.m_Asset->m_LoadError);
    }

    AssetLoadResponse resp;
    if (!buffer)
    {
      //printf("Failed loading asset %s\n", req_data.m_FilePath.data());
      resp = AssetLoadResponse{ asset, req_data.m_AsDocument, req_data.m_AsReload };
    }
    else
    {
      //printf("Successfully loaded asset %s\n", req_data.m_FilePath.data());
      asset->m_LoadError = asset->PreProcessLoadedData(*buffer);
      resp = AssetLoadResponse{ asset, req_data.m_AsDocument, req_data.m_AsReload, std::move(*buffer) };
    }

    FinalizeAssetResponse(resp);
  }

#else

  while (true)
  {
    auto resp = m_LoadResponses.TryDequeue();
    if (!resp)
    {
      break;
    }

    FinalizeAssetResponse(resp.Value());
  }

  while (true)
  {
    auto file = m_ModifiedFiles.TryDequeue();
    if (!file)
    {
      break;
    }

    ReloadFile(file->data());
  }

#endif
}

Optional<Buffer> AssetLoader::LoadFullFile(czstr file_path)
{
  int file_open_error = 0;
  return LoadFullFile(file_path, file_open_error);
}

Optional<Buffer> AssetLoader::LoadFullFile(czstr file_path, int & file_open_error)
{
#ifdef USE_WEBSOCKET_LOADING
  if (s_DisableNetworkLoading == false)
  {
    WebSocket ws;
    auto ws_file = LoadFullFileWebsocket(file_path, file_open_error, ws);
    if (ws_file)
    {
      return ws_file;
    }

    if (file_open_error != 0)
    {
      return{};
    }
  }
#endif

  return LoadFullFileRaw(file_path, file_open_error);
}

Optional<Buffer> AssetLoader::LoadFullFileWebsocket(czstr file_path, int & file_open_error, WebSocket & websocket)
{
  file_open_error = 0;
  if (websocket.IsConnected() == false)
  {
    return{};
  }

  websocket.SendString(file_path);

  auto resp = websocket.RecvPacket();
  if (!resp)
  {
    return{};
  }

  if (resp->m_Type == WebSocketPacketType::kText)
  {
    std::string error_str = BufferToString(resp->m_Buffer);
    file_open_error = atoi(error_str.data());
    return{};
  }

  return std::move(resp->m_Buffer);
}


Optional<Buffer> AssetLoader::LoadFullFileRaw(czstr file_path, int & file_open_error)
{
  auto full_path = GetFullPath(file_path, m_RootPath);

  auto file = FileOpen(full_path.data(), FileOpenMode::kRead);
  if (file.GetFileOpenError())
  {
    file_open_error = file.GetFileOpenError();
    return{};
  }

  auto data_size = file.GetFileLength();
  auto buffer = Buffer(data_size);
  file.Read(gsl::as_span(buffer.Get(), data_size));
  FileClose(file);
  return std::move(buffer);
}

Optional<Buffer> AssetLoader::LoadFullFileInternal(czstr file_path, int & file_open_error, WebSocket & websocket)
{
#ifdef USE_WEBSOCKET_LOADING
  if (s_DisableNetworkLoading == false)
  {
    auto ws_file = LoadFullFileWebsocket(file_path, file_open_error, websocket);
    if (ws_file)
    {
      return ws_file;
    }

    if (file_open_error != 0)
    {
      return{};
    }
  }
#endif

  auto raw_data = LoadFullFileRaw(file_path, file_open_error);

  return std::move(raw_data);
}

Optional<Buffer> AssetLoader::LoadFullDocumentWebsocket(czstr file_path, int & file_open_error, WebSocket & websocket)
{
  file_open_error = 0;
  if (websocket.IsConnected() == false)
  {
    return{};
  }

  websocket.SendString(file_path);

  auto resp = websocket.RecvPacket();
  if (!resp)
  {
    return{};
  }

  if (resp->m_Type == WebSocketPacketType::kText)
  {
    std::string error_str = BufferToString(resp->m_Buffer);
    file_open_error = 1;
    return{};
  }

  return std::move(resp->m_Buffer);
}

Optional<Buffer> AssetLoader::LoadFullDocumentRaw(czstr file_path, int & file_open_error)
{
  std::unique_lock<std::mutex> lock(m_DocumentCompilerMutex);
  auto document = m_DocumentCompiler.GetDocument(file_path);
  document->AddRef();

  if (document->GetState() == DocumentState::kLoaded)
  {
    return StringToBuffer(document->GetDocumentJson());
  }

  file_open_error = 1;
  return{};
}

Optional<Buffer> AssetLoader::LoadFullDocumentInternal(czstr file_path, int & file_open_error, WebSocket & websocket)
{
#ifdef USE_WEBSOCKET_LOADING
  if (s_DisableNetworkLoading == false)
  {
    auto ws_file = LoadFullDocumentWebsocket(file_path, file_open_error, websocket);
    if (ws_file)
    {
      return ws_file;
    }

    if (file_open_error != 0)
    {
      return{};
    }
  }
#endif

  return LoadFullDocumentRaw(file_path, file_open_error);
}

void AssetLoader::LoadDocument(czstr path, uint64_t file_hash, DocumentLoadCallback callback)
{
  auto default_time_point = std::chrono::system_clock::time_point();

  auto full_path = GetFullPath(path, m_RootPath);

  File file = FileOpen(full_path.data(), FileOpenMode::kRead);
  if (file.GetFileOpenError() != 0)
  {
    callback(file_hash, Optional<Buffer>{}, default_time_point);
    return;
  }

  auto buffer = file.ReadFileFull();
  FileClose(file);

  std::error_code ec;

#ifdef _WEB
  auto last_write = default_time_point;
#else
  auto last_write = std::experimental::filesystem::last_write_time(path, ec);
#endif

  callback(file_hash, Optional<Buffer>(std::move(buffer)), last_write);
}

void AssetLoader::ReloadFile(czstr file_path)
{
  AssetReloadInfo * reload_info = s_AssetReloadList;
  while (reload_info)
  {
    reload_info->m_Callback->ReloadFile(file_path);
    reload_info = reload_info->m_Next;
  }
}

void AssetLoader::DisableNetworkLoading()
{
  s_DisableNetworkLoading = true;
}

void AssetLoader::LoadThread()
{
#ifndef _WEB

  bool delay_requests = true;

  WebSocket loader_websocket;
  WebSocket compiler_websocket;

#ifdef USE_WEBSOCKET_LOADING
  if (s_DisableNetworkLoading == false)
  {
    ConnectLoaderWebsocket(loader_websocket);
    ConnectCompilerWebsocket(compiler_websocket);
  }
#endif

  while (m_Running)
  {
    m_LoadSemaphore.WaitOne();

#ifdef USE_WEBSOCKET_LOADING
    if (s_DisableNetworkLoading == false)
    {
      if (loader_websocket.IsConnected() && compiler_websocket.IsConnected())
      {
        delay_requests = false;
      }

      if (loader_websocket.IsConnecting() == false || compiler_websocket.IsConnecting() == false)
      {
        delay_requests = false;
      }

      if (loader_websocket.IsConnected() == false && loader_websocket.IsConnecting() == false)
      {
        ConnectLoaderWebsocket(loader_websocket);
      }

      if (compiler_websocket.IsConnected() == false && compiler_websocket.IsConnecting() == false)
      {
        ConnectCompilerWebsocket(compiler_websocket);
      }

      if (delay_requests)
      {
        std::this_thread::yield();
        continue;
      }
    }
#endif

    while (true)
    {
      auto req = m_LoadRequests.TryDequeue();
      if (!req)
      {
        break;
      }

      auto & req_data = req.Value();
      auto asset = req_data.m_Asset;

      Optional<Buffer> buffer;
      if (req_data.m_AsDocument)
      {
        buffer = LoadFullDocumentInternal(req_data.m_FilePath.data(), req_data.m_Asset->m_LoadError, compiler_websocket);
      }
      else
      {
        buffer = LoadFullFileInternal(req_data.m_FilePath.data(), req_data.m_Asset->m_LoadError, loader_websocket);
      }

      if (!buffer)
      {
        while (m_LoadResponses.Enqueue(AssetLoadResponse{ asset, req_data.m_AsDocument, req_data.m_AsReload }) == false)
        {
          std::this_thread::yield();
        }

        return;
      }

      asset->m_LoadError = asset->PreProcessLoadedData(*buffer);

      while (m_LoadResponses.Enqueue(AssetLoadResponse{ asset, req_data.m_AsDocument, req_data.m_AsReload, std::move(*buffer) }) == false)
      {
        std::this_thread::yield();
      }
    }
  }
#endif
}


void AssetLoader::ReloadThread()
{
#ifndef _WEB
  while (m_Running)
  {
    if (m_ReloadServerSocket->IsConnected())
    {
      if (m_ReloadServerSocket->IsConnecting() == false)
      {
        m_ReloadServerSocket->StartConnect(s_AssetServerHost.data(), 27802, "/", "localhost");
      }
      else
      {
        std::this_thread::yield();
      }
    }
    else
    {
      while (m_Running)
      {
        auto packet = m_ReloadServerSocket->RecvPacket();
        if (!packet)
        {
          break;
        }

        m_ModifiedFiles.Enqueue(BufferToString(packet->m_Buffer));
      }
    }
  }
#endif
}

void AssetLoader::ConnectLoaderWebsocket(WebSocket & websocket)
{
  websocket.StartConnect(s_AssetServerHost.data(), 27801, "/", "localhost");
}

void AssetLoader::ConnectCompilerWebsocket(WebSocket & websocket)
{
  websocket.StartConnect(s_AssetServerHost.data(), 27803, "/", "localhost");
}

void AssetLoader::FinalizeAssetResponse(AssetLoadResponse & resp)
{
  //printf("Finalizing asset %s (%d)\n", resp.m_Asset->GetFileName().data(), resp.m_Asset->m_LoadError);

  if (resp.m_Asset->m_LoadError == 0)
  {
    resp.m_Asset->m_State = AssetState::kFinalizing;
    resp.m_Asset->OnDataLoadComplete(resp.m_FileData);

    if (resp.m_AsReload && resp.m_Asset->m_State == AssetState::kFinalizing)
    {
      // The asset went back into a loading state after a reload.  This can happen if the asset got reloaded
      // from disk with additional dependencies, but those new dependencies were not already loaded.  In this
      // case, the assets that depend on this asset need to be notified that the data is no longer in a
      // complete state.
      resp.m_Asset->m_State = AssetState::kLoadError;
      resp.m_Asset->CallAssetLoadCallbacks();
    }
  }
  else
  {
    resp.m_Asset->CallAssetLoadCallbacksWithFailure();
  }

  resp.m_Asset->DecRef();
}

void AssetLoader::RegisterAssetLoadCallback(AssetReloadInfo * reload_cb)
{
  reload_cb->m_Next = s_AssetReloadList;
  s_AssetReloadList = reload_cb;
}

