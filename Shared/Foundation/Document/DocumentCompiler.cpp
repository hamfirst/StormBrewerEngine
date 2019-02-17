
#include "Foundation/Common.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/Document/Document.h"
#include "Foundation/FileSystem/File.h"

#include <sb/vector.h>


DocumentCompiler::DocumentCompiler(NotNullPtr<DocumentLoader> loader) :
  m_Loader(loader)
{

}

DocumentCompiler::~DocumentCompiler()
{
  for (auto & doc : m_Documents)
  {
    doc.second->TearDown();
  }

  m_Documents.clear();
}

NullOptPtr<Document> DocumentCompiler::CreateNewDocument(czstr path)
{
  File file = FileOpen(path, FileOpenMode::kWrite);
  if (file.GetFileOpenError() > 0)
  {
    return nullptr;
  }

  file.Write(Document::CreateEmptyFile());
  FileClose(file);

  return GetDocument(path);
}

NotNullPtr<Document> DocumentCompiler::GetDocument(czstr path)
{
  uint32_t file_hash = crc32lowercase(path);

  auto itr = m_Documents.find(file_hash);
  if (itr != m_Documents.end())
  {
    return itr->second.get();
  }

  auto doc_ptr = std::make_unique<Document>(this, path);
  auto result = m_Documents.emplace(std::make_pair(file_hash, std::move(doc_ptr)));
  m_Loader->LoadDocument(path, file_hash, DocumentLoadCallback(&DocumentCompiler::HandleDocumentLoaded, this));

  return result.first->second.get();
}

NullOptPtr<Document> DocumentCompiler::GetDocument(uint32_t path_hash)
{
  auto itr = m_Documents.find(path_hash);
  if (itr != m_Documents.end())
  {
    return itr->second.get();
  }

  return itr->second.get();
}

void DocumentCompiler::ReloadDocument(czstr path)
{
  uint32_t file_hash = crc32lowercase(path);

  auto itr = m_Documents.find(file_hash);
  if (itr == m_Documents.end())
  {
    return;
  }

  m_Loader->LoadDocument(path, file_hash, DocumentLoadCallback(&DocumentCompiler::HandleDocumentLoaded, this));
}

void DocumentCompiler::HandleDocumentLoaded(uint32_t file_id, void * data, std::size_t length, std::filesystem::file_time_type last_modified_time)
{
  auto itr = m_Documents.find(file_id);
  if (itr == m_Documents.end())
  {
    return;
  }

  if (data)
  {
    itr->second->ParseFull((char *)data);
  }
  else
  {
    itr->second->FileError();
  }
}

void DocumentCompiler::UnloadDocument(uint32_t file_id)
{
  auto itr = m_Documents.find(file_id);
  if (itr == m_Documents.end())
  {
    return;
  }

  m_Documents.erase(itr);
}
