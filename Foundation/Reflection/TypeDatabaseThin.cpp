
#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabaseThin.h"
#include "Foundation\Reflection\TypeDatabase.h"

Optional<void *> CreateTypeInstance(Hash type_name_hash)
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

bool CompareTypeInstance(void * ptr1, void * ptr2, Hash type_name_hash)
{
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);

  if (type_info)
  {
    return type_info->m_Compare(ptr1, ptr2);
  }
  else
  {
    return false;
  }
}

#ifdef REFLECTION_CHANGE_NOTIFIER
void SetParentInfo(void * ptr, Hash type_name_hash, const ReflectionParentInfo & info)
{
  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);

  if (type_info)
  {
    type_info->m_SetParentInfo(ptr, info);
  }
}
#endif
