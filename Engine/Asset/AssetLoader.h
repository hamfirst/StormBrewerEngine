#pragma once

#include <memory>
#include <thread>

#include "Foundation/Thread/MessageQueue.h"
#include "Foundation/Thread/Semaphore.h"
#include "Foundation/Network/WebSocket.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/Document/DocumentLoader.h"

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetReloadCallback.h"

class ENGINE_EXPORT AssetLoader : public DocumentLoader
{
public:
  AssetLoader();
  ~AssetLoader();

  void Init();
  void ShutDown();

  void RequestFileLoad(Asset * asset, czstr file_path, bool as_document, bool as_reload);
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

  Optional<Buffer> LoadFullDocumentWebsocket(czstr file_path, int & file_open_error, WebSocket & websocket);
  Optional<Buffer> LoadFullDocumentRaw(czstr file_path, int & file_open_error);
  Optional<Buffer> LoadFullDocumentInternal(czstr file_path, int & file_open_error, WebSocket & websocket);

  virtual void LoadDocument(czstr path, uint64_t file_hash, DocumentLoadCallback callback) override;

  template <typename AssetType>
  friend class AssetManager;

  void RegisterAssetLoadCallback(AssetReloadInfo * reload_cb);

private:

  struct AssetLoadRequest
  {
    Asset * m_Asset;
    std::string m_FilePath;
    bool m_AsDocument;
    bool m_AsReload;
  };

  struct AssetLoadResponse
  {
    Asset * m_Asset;
    bool m_AsDocument;
    bool m_AsReload;
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

  std::mutex m_DocumentCompilerMutex;
  DocumentCompiler m_DocumentCompiler;
};

extern AssetLoader g_AssetLoader;