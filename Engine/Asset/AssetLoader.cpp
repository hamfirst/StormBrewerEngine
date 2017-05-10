
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"
#include "Foundation/Document/Document.h"

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Settings/EngineSettings.refl.h"

#include <experimental/filesystem>

#define USE_WEBSOCKET_LOADING

AssetLoader g_AssetLoader;
static AssetReloadInfo * s_AssetReloadList = nullptr;
static bool s_DisableNetworkLoading = false;

static std::string s_AssetServerHost = "localhost";

AssetLoader::AssetLoader() :
  m_LoadRequests(1024),
  m_LoadResponses(1024),
  m_ModifiedFiles(2048),
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

  m_LoaderThreads = std::make_unique<std::thread[]>(g_EngineSettings.m_AssetLoadThreads);
  for (int index = 0; index < g_EngineSettings.m_AssetLoadThreads; index++)
  {
    m_LoaderThreads[index] = std::thread(&AssetLoader::LoadThread, this);
  }

#ifdef USE_WEBSOCKET_LOADING
  m_ReloadServerSocket = std::make_unique<WebSocket>();
  m_ReloadThread = std::thread(&AssetLoader::ReloadThread, this);
#endif
}

void AssetLoader::ShutDown()
{
  if (m_Running == false)
  {
    return;
  }

  m_Running = false;
  m_LoadSemaphore.Release(g_EngineSettings.m_AssetLoadThreads);

  for (int index = 0; index < g_EngineSettings.m_AssetLoadThreads; index++)
  {
    m_LoaderThreads[index].join();
  }

  m_ReloadServerSocket->Close();
  m_ReloadThread.join();
}

void AssetLoader::RequestFileLoad(Asset * asset, czstr file_path, bool as_document, bool as_reload)
{
  asset->IncRef();

  AssetLoadRequest req{ asset, file_path, as_document, as_reload };
  while (m_LoadRequests.Enqueue(std::move(req)) == false)
  {
    std::this_thread::yield();
  }

  m_LoadSemaphore.Release();
}

void AssetLoader::ProcessResponses()
{
  while (true)
  {
    auto resp = m_LoadResponses.TryDequeue();
    if (!resp)
    {
      break;
    }

    if (resp->m_Asset->m_LoadError == 0)
    {
      resp->m_Asset->m_State = AssetState::kFinalizing;
      resp->m_Asset->OnDataLoadComplete(resp->m_FileData);

      if(resp->m_AsReload && resp->m_Asset->m_State == AssetState::kFinalizing)
      {
        // The asset went back into a loading state after a reload.  This can happen if the asset got reloaded
        // from disk with additional dependencies, but those new dependencies were not already loaded.  In this
        // case, the assets that depend on this asset need to be notified that the data is no longer in a
        // complete state.
        resp->m_Asset->m_State = AssetState::kLoadError;
        resp->m_Asset->CallAssetLoadCallbacks();
      }
    }
    else
    {
      resp->m_Asset->CallAssetLoadCallbacksWithFailure();
    }

    resp->m_Asset->DecRef();
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
    if (websocket.Connect(s_AssetServerHost.data(), 27801, "/", "localhost") == false)
    {
      return{};
    }
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
  auto file = FileOpen(file_path, FileOpenMode::kRead);
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

  return LoadFullFileRaw(file_path, file_open_error);
}

Optional<Buffer> AssetLoader::LoadFullDocumentWebsocket(czstr file_path, int & file_open_error, WebSocket & websocket)
{
  file_open_error = 0;
  if (websocket.IsConnected() == false)
  {
    if (websocket.Connect(s_AssetServerHost.data(), 27803, "/", "localhost") == false)
    {
      return{};
    }
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
  File file = FileOpen(path, FileOpenMode::kRead);
  if (file.GetFileOpenError() != 0)
  {
    callback(file_hash, Optional<Buffer>{}, std::chrono::system_clock::time_point{});
    return;
  }

  auto buffer = file.ReadFileFull();
  FileClose(file);

  std::error_code ec;
  callback(file_hash, Optional<Buffer>(std::move(buffer)), std::experimental::filesystem::last_write_time(path, ec));
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
  WebSocket loader_websocket;
  WebSocket compiler_websocket;
  while (m_Running)
  {
    m_LoadSemaphore.WaitOne();

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

        continue;
      }

      asset->m_LoadError = asset->PreProcessLoadedData(*buffer);

      while (m_LoadResponses.Enqueue(AssetLoadResponse{ asset, req_data.m_AsDocument, req_data.m_AsReload, std::move(*buffer) }) == false)
      {
        std::this_thread::yield();
      }
    }
  }
}


void AssetLoader::ReloadThread()
{
  while (m_Running)
  {
    if (m_ReloadServerSocket->Connect(s_AssetServerHost.data(), 27802, "/", "localhost"))
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
}

void AssetLoader::RegisterAssetLoadCallback(AssetReloadInfo * reload_cb)
{
  reload_cb->m_Next = s_AssetReloadList;
  s_AssetReloadList = reload_cb;
}

