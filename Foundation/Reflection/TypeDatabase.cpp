
#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabase.h"

Singleton<TypeDatabase> g_TypeDatabase;
TypeRegisterInfo * g_TypeRegistrationList;


void TypeDatabase::FinalizeTypes()
{
  TypeRegisterInfo * type_info = g_TypeRegistrationList;
  while (type_info)
  {
    type_info->m_RegisterClass();
    type_info = type_info->m_Next;
  }
}