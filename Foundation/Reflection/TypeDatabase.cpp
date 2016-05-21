
#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabase.h"

Singleton<TypeDatabase> g_TypeDatabase;
PreMainCallList g_TypeDatabaseRegistrationCallList;

void TypeDatabase::Init()
{
  g_TypeDatabaseRegistrationCallList.CallAll();
}

Optional<TypeInfo> TypeDatabase::GetTypeInfo(uint32_t type_name_hash)
{
  auto val = m_Types.find(type_name_hash);
  if (val == m_Types.end())
  {
    return Optional<TypeInfo>();
  }

  return val->second;
}

void TypeDatabase::RegisterType(const TypeInfo & type_info)
{
  m_Types[type_info.m_TypeNameHash] = type_info;
}
