
#include "Engine/EngineCommon.h"

#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "Engine/Asset/AssetLoader.h"
#include "Engine/Settings/EngineSettings.refl.h"

#define USE_WEBSOCKET_LOADING

AssetLoader g_AssetLoader;
static AssetReloadInfo * s_AssetReloadList = nullptr;
static bool s_DisableNetworkLoading = false;

static std::string s_AssetServerHost = "localhost";

AssetLoader::AssetLoader() :
  m_LoadRequests(1024),
  m_LoadResponses(1024),
  m_ModifiedFiles(2048)
{

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
  m_Running = false;
  m_LoadSemaphore.Release(g_EngineSettings.m_AssetLoadThreads);

  for (int index = 0; index < g_EngineSettings.m_AssetLoadThreads; index++)
  {
    m_LoaderThreads[index].join();
  }

  m_ReloadServerSocket->Close();
  m_ReloadThread.join();
}

void AssetLoader::RequestFileLoad(Asset * asset, czstr file_path)
{
  asset->IncRef();

  AssetLoadRequest req{ asset, file_path };
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
      if (resp->m_Asset->OnDataLoadComplete(resp->m_FileData) == false)
      {
        resp->m_Asset->m_State = AssetState::kLoadError;
      }
    }
    else
    {
      resp->m_Asset->m_State = AssetState::kLoadError;
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

      auto buffer = LoadFullFileInternal(req->m_FilePath.data(), req->m_Asset->m_LoadError, loader_websocket);

      if(!buffer)
      {
        while (m_LoadResponses.Enqueue(AssetLoadResponse{ req->m_Asset }) == false)
        {
          std::this_thread::yield();
        }

        continue;
      }

      req->m_Asset->PreProcessLoadedData(*buffer);
      
      while (m_LoadResponses.Enqueue(AssetLoadResponse{ req->m_Asset, std::move(*buffer) }) == false)
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

