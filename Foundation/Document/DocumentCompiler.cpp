
#include "Foundation/Common.h"
#include "Foundation/Document/DocumentCompiler.h"
#include "Foundation/Document/Document.h"

#include <sb/vector.h>


DocumentCompiler::DocumentCompiler(NotNullPtr<DocumentLoader> loader) :
  m_Loader(loader)
{

}

DocumentCompiler::~DocumentCompiler()
{

}

void DocumentCompiler::SetFileTypeSchema(czstr file_extension, NotNullPtr<JsonSchema> schema, czstr default_data)
{
  auto result = m_FileTypes.emplace(std::make_pair(crc32(file_extension), Json(schema)));
  if (result.second == false)
  {
    throw false;
  }

  std::vector<std::pair<std::string, std::string>> schema_errors;
  result.first->second.Parse(default_data, schema_errors);
}

void DocumentCompiler::LoadDocument(czstr path)
{
  uint64_t file_hash = crc64lowercase(path);
  
  if (m_Documents.find(file_hash) != m_Documents.end())
  {
    return;
  }

  if (m_DocumentLoadRequests.find(file_hash) != m_DocumentLoadRequests.end())
  {
    return;
  }

  auto handle = m_Loader->LoadDocument(path, file_hash, DocumentLoadCallback(&DocumentCompiler::HandleDocumentLoaded, this));
  m_DocumentLoadRequests.emplace(file_hash, std::make_pair(std::string(path), handle));
}

void DocumentCompiler::AddDependency(NotNullPtr<Document> document, czstr path)
{
  LoadDocument(path);

  uint64_t file_hash = crc64lowercase(path);
  auto itr = m_Dependencies.find(file_hash);

  if (itr == m_Dependencies.end())
  {
    auto result = m_Dependencies.emplace(std::make_pair(file_hash, std::vector<NotNullPtr<Document>>()));
    itr = result.first;
  }

  itr->second.emplace_back(document);
}

void DocumentCompiler::RemoveDependency(NotNullPtr<Document> document, czstr path)
{
  uint64_t file_hash = crc64lowercase(path);
  auto itr = m_Dependencies.find(file_hash);

  vremove_quick(itr->second, document);
}

NullOptPtr<Document> DocumentCompiler::GetDocument(czstr path)
{
  return GetDocument(crc64lowercase(path));
}

NullOptPtr<Document> DocumentCompiler::GetDocument(uint64_t file_hash)
{
  auto itr = m_Documents.find(file_hash);
  if (itr == m_Documents.end())
  {
    return nullptr;
  }

  return itr->second.get();
}

void DocumentCompiler::HandleDocumentLoaded(uint64_t file_id, DocumentLoadRequest req, Optional<Buffer> & buffer)
{
  auto itr = m_DocumentLoadRequests.find(file_id);
  if (itr == m_DocumentLoadRequests.end())
  {
    throw false;
  }
 
  auto & file_name = itr->second.first;
  std::size_t file_ext_index = file_name.find_last_of('.');
  if (file_ext_index == std::string::npos)
  {
    throw false;
  }

  const char * ext = file_name.data() + file_ext_index + 1;
  Hash ext_hash = crc32(ext);

  m_DocumentLoadRequests.erase(itr);

  auto file_type_info = m_FileTypes.find(ext_hash);
  if (file_type_info == m_FileTypes.end())
  {
    throw false;
  }

  auto & init_json = file_type_info->second;
  const char * file_data = buffer ? (const char *)buffer->Get() : nullptr;

  m_Documents.emplace(std::make_pair(file_id, std::make_unique<Document>(init_json, this, file_data)));

  auto deps = m_Dependencies.find(file_id);
  if (deps != m_Dependencies.end())
  {
    for (auto doc_ptr : deps->second)
    {
      doc_ptr->DependencyLoaded(file_id);
    }
  }
}
