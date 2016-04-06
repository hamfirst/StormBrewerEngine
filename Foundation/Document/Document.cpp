
#include "Foundation\Common.h"

#include <cstdlib>

#include "Document.h"


Document::Document(const char * json_data)
{
  m_Root = Json(json_data);
}

DocumentModification Document::ApplyModification(const DocumentModification & mod)
{
  DocumentPath reverse_path = mod.m_Path;

  Json & cur_val = m_Root;

  int size = mod.m_Path.GetSize();
  for (int index = 0; index < size - 1; index++)
  {
    cur_val = cur_val.at(mod.m_Path[index].m_Data.data());
  }

  return DocumentModification {reverse_path, "", DocumentModificationType::kDelete };
}
