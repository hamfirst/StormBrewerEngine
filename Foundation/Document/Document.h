#pragma once

#include "Foundation/Json/Json.h"
#include "Foundation/Document/DocumentTypes.refl.h"

enum class DocumentState
{
  kWaitingForDeps,
  kCompiled,
  kParseFailed,
  kDependencyFailed,
};

class DocumentCompiler;

class Document
{
public:

  Document(Json & initial_data, NotNullPtr<DocumentCompiler>, NullOptPtr<const char> file_data);
  Document(const Document & rhs) = delete;
  Document(Document && rhs) = delete;

  ~Document();

  Document & operator = (const Document & rhs) = delete;
  Document & operator = (Document && rhs) = delete;

  void DependencyLoaded(uint64_t file_hash);

private:

  struct DocumentDependency
  {
    uint64_t m_FileHash;
    bool m_Loaded;
  };

  NotNullPtr<DocumentCompiler> m_Compiler;

  DocumentState m_State;
  std::vector<DocumentLink> m_Links;
  std::vector<DocumentDependency> m_Dependencies;
  std::vector<DocumentSchemaError> m_SchemaErrors;

  Json m_FileJson;
};


