#pragma once

#include "Foundation/Document/Document.h"
#include "Foundation/Document/DocumentCompiler.h"

class DocumentDefaultLoader : public DocumentLoader
{
public:
  DocumentDefaultLoader();

  virtual void LoadDocument(czstr path, uint32_t file_hash, DocumentLoadCallback callback);

private:
  std::string m_RootPath;
};
