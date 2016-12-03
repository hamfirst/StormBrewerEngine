#pragma once

#include <memory>
#include <map>

#include "FileSystemWatcher.h"

#include <StormSockets/StormSocketConnectionId.h>
#include <StormSockets/StormSemaphore.h>

#include <Foundation/Buffer/Buffer.h>

namespace StormSockets
{
  class StormSocketBackend;
  class StormSocketServerFrontendWebsocket;
}

class DocumentServer
{
public:
  DocumentServer();
  ~DocumentServer();

  void Run();

private:

  bool ProcessMessage(StormSockets::StormSocketConnectionId client_id, char * msg, std::size_t length);

  template <typename T>
  void SendMessageToClient(StormSockets::StormSocketConnectionId client_id, const T & packet);
  template <typename T>
  void SendMessageToAllClients(const T & packet);
  template <typename T>
  void SendMessageToAllClientsExcept(StormSockets::StormSocketConnectionId except_client_id, const T & packet);

private:

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_DocServerFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_AssetServerFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_ReloadServerFrontend;

  std::unique_ptr<FileSystemWatcher> m_FilesystemWatcher;

  std::vector<StormSockets::StormSocketConnectionId> m_ReloadConnections;

  std::unordered_map<Hash, Buffer> m_CachedAssets;

  bool m_Quit = false;

  std::unique_ptr<char[]> m_RecvBuffer;
  int m_RecvBufferSize = 0;

  int m_NextDocumentId = 0;
  StormSockets::StormSemaphore m_Semaphore;
};