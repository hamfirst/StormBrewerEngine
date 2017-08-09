
#include "StormExprFunctionList.h"
#include "StormExprHash.h"

void StormExprFunctionList::RegisterFunction(const char * name, StormExprFunctionCallback callback, ptrdiff_t user_data)
{
  m_Funcs.insert_or_assign((uint32_t)StormExprHashString(name), std::make_pair(callback, user_data));
}

bool StormExprFunctionList::LookupFunction(uint32_t name_hash, StormExprFunctionCallback & out_callback, ptrdiff_t & out_user_data) const
{
  auto itr = m_Funcs.find(name_hash);

  if (itr == m_Funcs.end())
  {
    return false;
  }

  out_callback = itr->second.first;
  out_user_data = itr->second.second;
  return true;
}
