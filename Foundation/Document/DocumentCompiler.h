#pragma once

#include "Foundation/Document/DocumentLoader.h"
#include "Foundation/Json/Json.h"

class Document;

class DocumentCompiler
{
public:

  DocumentCompiler(NotNullPtr<DocumentLoader> loader);
  DocumentCompiler(const DocumentCompiler & rhs) = delete;
  DocumentCompiler(DocumentCompiler && rhs) = delete;

  ~DocumentCompiler();

  DocumentCompiler & operator = (const DocumentCompiler & rhs) = delete;
  DocumentCompiler & operator = (DocumentCompiler && rhs) = delete;

  void SetFileTypeSchema(czstr file_extension, NotNullPtr<JsonSchema> schema, czstr default_data);

  void LoadDocument(czstr path);
  void AddDependency(NotNullPtr<Document> document, czstr path);
  void RemoveDependency(NotNullPtr<Document> document, czstr path);

  NullOptPtr<Document> GetDocument(czstr path);
  NullOptPtr<Document> GetDocument(uint64_t file_hash);

private:

  void HandleDocumentLoaded(uint64_t file_id, DocumentLoadRequest req, Optional<Buffer> & buffer);

private:

  NotNullPtr<DocumentLoader> m_Loader;

  std::unordered_map<uint64_t, std::pair<std::string, DocumentLoadRequest>> m_DocumentLoadRequests;
  std::unordered_map<uint64_t, std::unique_ptr<Document>> m_Documents;
  std::unordered_map<uint64_t, std::vector<NotNullPtr<Document>>> m_Dependencies;

  std::unordered_map<uint64_t, Json> m_FileTypes;

};


