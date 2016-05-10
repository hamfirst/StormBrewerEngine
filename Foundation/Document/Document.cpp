
#include "Foundation\Common.h"

#include <cstdlib>

#include "Document.h"


Document::Document(const char * json_data)
{
  m_Root = Json(json_data);
}
