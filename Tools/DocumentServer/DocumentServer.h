#pragma once

#include <memory>
#include <map>
#include <chrono>

#include "FileNameDatabase.h"
#include "DocumentServerMessages.refl.h"

#include <StormSockets/StormSocketConnectionId.h>
#include <StormSockets/StormSemaphore.h>

#include "Foundation/Buffer/Buffer.h"
#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/FileSystem/FileSystemWatcher.h"

namespace StormSockets
{
  class StormSocketBackend;
  class StormSocketServerFrontendWebsocket;
}

struct DocumentServerDocumentClient
{
  StormSockets::StormSocketConnectionId m_ConnectionId;
  uint32_t m_DocumentId;
};

struct DocumentServerDocumentInfo
{
  Document * m_Document;
  int m_DataGen;
  std::chrono::system_clock::time_point m_LastModifiedTime;
  std::vector<DocumentServerDocumentClient> m_Connections;
  std::vector<ReflectionChangeNotification> m_PendingChanges;
};

struct DocumentServerClientDocument
{
  uint32_t m_FileId;
  uint32_t m_DocumentId;
};

struct DocumentServerClientInfo
{
  StormSockets::StormSocketConnectionId m_ClientId;
  std::vector<DocumentServerClientDocument> m_DocumentList;
};

struct CompilerServerClientInfo
{
  StormSockets::StormSocketConnectionId m_ClientId;
  std::vector<std::pair<Document *, uint32_t>> m_FileIds;
};

class DocumentServer : public DocumentLoader
{
public:
  DocumentServer();
  ~DocumentServer();

  void Run();

private:
  virtual void LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback) override;
  std::string GetFullPath(const std::string & path);

  void HandleDocumentChange(uint32_t file_hash, Document * document, const ReflectionChangeNotification & change);
  void HandleDocumentStateChange(uint32_t file_hash, Document * document, DocumentState state, DocumentState prev_state);
  void HandleDocumentLinksModified(uint32_t file_hash, Document * document);

  void HandleDocumentModified(czstr path, std::chrono::system_clock::time_point last_modified);
  void HandleDocumentRemoved(czstr path);
  void OpenDocumentForClient(czstr path, uint32_t document_id, StormSockets::StormSocketConnectionId client_id);
  void SendPendingChanges();
  NullOptPtr<DocumentServerDocumentInfo> GetDocumentForClient(uint32_t document_id, StormSockets::StormSocketConnectionId client_id);

  bool ProcessMessage(StormSockets::StormSocketConnectionId client_id, char * msg, std::size_t length);

  void SendMessageToClient(DocumentClientMessageType type, StormSockets::StormSocketConnectionId client_id, uint32_t document_id, const std::string & packet);


private:

  std::string m_RootPath;

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_DocServerFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_AssetServerFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_ReloadServerFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_CompilerServerFrontend;

  std::unique_ptr<FileSystemWatcher> m_FilesystemWatcher;
  std::vector<StormSockets::StormSocketConnectionId> m_ReloadConnections;

  std::unordered_map<uint32_t, DocumentServerDocumentInfo> m_OpenDocuments;
  std::unordered_map<uint32_t, DocumentServerClientInfo> m_DocServerClients;

  std::unordered_map<uint32_t, CompilerServerClientInfo> m_CompileServerClients;

  std::unordered_map<Hash, Buffer> m_CachedAssets;
  std::unordered_map<uint32_t, DocumentServerDocumentInfo *> m_PendingChangedDocuments;

  FileNameDatabase m_FileNameDatabase;
  bool m_Quit = false;

  DocumentCompiler m_DocumentCompiler;

  std::unique_ptr<char[]> m_RecvBuffer;
  int m_RecvBufferSize = 0;

  int m_NextDocumentId = 0;
  StormSockets::StormSemaphore m_Semaphore;
};