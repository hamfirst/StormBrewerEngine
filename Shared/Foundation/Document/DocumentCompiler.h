#pragma once

#include <chrono>

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

  NullOptPtr<Document> CreateNewDocument(czstr path);
  NotNullPtr<Document> GetDocument(czstr path);
  NullOptPtr<Document> GetDocument(uint32_t path_hash);

  void ReloadDocument(czstr path);

private:

  friend class Document;

  void HandleDocumentLoaded(uint32_t file_id, void * data, std::size_t length, std::filesystem::file_time_type last_modified_time);
  void UnloadDocument(uint32_t file_id);

private:

  NotNullPtr<DocumentLoader> m_Loader;

  std::unordered_map<uint32_t, std::unique_ptr<Document>> m_Documents;
};


