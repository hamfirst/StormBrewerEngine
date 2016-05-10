
#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabaseThin.h"
#include "Foundation\Reflection\TypeDatabase.h"

Optional<void *> CreateTypeInstance(uint32_t type_name_hash)
{
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);

  if (type_info)
  {
    return type_info->m_HeapCreateDefault();
  }
  else
  {
    return Optional<void *>();
  }
}
