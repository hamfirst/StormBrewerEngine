
#include "Foundation/Document/DocumentDefaultLoader.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"

DocumentDefaultLoader::DocumentDefaultLoader()
{
  m_RootPath = GetCanonicalRootPath();
}

void DocumentDefaultLoader::LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback)
{
  auto path_str = GetFullPath(path, m_RootPath);

  File file = FileOpen(path_str.data(), FileOpenMode::kRead);
  if (file.GetFileOpenError() != 0)
  {
    callback(file_hash, nullptr, 0, time_t{});
    return;
  }

  auto buffer = file.ReadFileFull();
  FileClose(file);

  callback(file_hash, buffer.Get(), buffer.GetSize(), GetLastWriteTime(path));
}

