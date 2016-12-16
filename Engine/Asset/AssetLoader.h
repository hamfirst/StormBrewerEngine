#pragma once

#include <memory>
#include <thread>

#include "Foundation/Thread/MessageQueue.h"
#include "Foundation/Thread/Semaphore.h"
#include "Foundation/Network/WebSocket.h"

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetReloadCallback.h"

class AssetLoader
{
public:
  AssetLoader();

  void Init();
  void ShutDown();

  void RequestFileLoad(Asset * asset, czstr file_path);
  void ProcessResponses();

  Optional<Buffer> LoadFullFile(czstr file_path);
  Optional<Buffer> LoadFullFile(czstr file_path, int & file_open_error);
  void ReloadFile(czstr file_path);

  static void DisableNetworkLoading();

private:

  void LoadThread();
  void ReloadThread();

  Optional<Buffer> LoadFullFileWebsocket(czstr file_path, int & file_open_error, WebSocket & websocket);
  Optional<Buffer> LoadFullFileRaw(czstr file_path, int & file_open_error);
  Optional<Buffer> LoadFullFileInternal(czstr file_path, int & file_open_error, WebSocket & websocket);

  template <typename AssetType>
  friend class AssetManager;

  void RegisterAssetLoadCallback(AssetReloadInfo * reload_cb);

private:

  struct AssetLoadRequest
  {
    Asset * m_Asset;
    std::string m_FilePath;
  };

  struct AssetLoadResponse
  {
    Asset * m_Asset;
    Buffer m_FileData;
  };

  volatile bool m_Running = false;
  int m_FileLoading = 0;

  MessageQueue<AssetLoadRequest> m_LoadRequests;
  MessageQueue<AssetLoadResponse> m_LoadResponses;
  MessageQueue<std::string> m_ModifiedFiles;
  Semaphore m_LoadSemaphore;

  std::unique_ptr<std::thread[]> m_LoaderThreads;

  std::unique_ptr<WebSocket> m_ReloadServerSocket;
  std::thread m_ReloadThread;

};

extern AssetLoader g_AssetLoader;