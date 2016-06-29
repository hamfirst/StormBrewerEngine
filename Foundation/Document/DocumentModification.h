#pragma once

#include "Foundation\Document\DocumentPath.h"

enum class DocumentModificationType
{
  kSet,
  kClearArray,
  kClearObject,
  kAppendArray,
  kCompress,
  kInsertArray,
  kInsertObject,
  kRemoveArray,
  kRemoveObject,
  kResetToDefault,
};

struct DocumentModification final
{
  std::string Encode() const;
  void Decode(const std::string & json_data);

  DocumentPath m_Path;
  std::string m_Data;
  DocumentModificationType m_Type;
  uint32_t m_Index;
};


