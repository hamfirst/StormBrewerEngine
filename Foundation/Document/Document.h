#pragma once

#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Json\Json.h"


enum class DocumentModificationType
{
  kSet,
  kDelete,
};

struct DocumentModification
{
  DocumentPath m_Path;
  std::string m_Data;
  DocumentModificationType m_Type;
};

class Document
{
  Document(const char * json_data);

  // Returns reverse modification
  DocumentModification ApplyModification(const DocumentModification & mod);
private:
  Json m_Root;
};
