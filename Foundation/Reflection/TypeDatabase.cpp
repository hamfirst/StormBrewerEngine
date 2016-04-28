
#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabase.h"

Singleton<TypeDatabase> g_TypeDatabase;
PreMainCallList g_TypeDatabaseRegistrationCallList;


void TypeDatabase::Init()
{
  g_TypeDatabaseRegistrationCallList.CallAll();
}