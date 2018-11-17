#pragma once

#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"

class Blackboard
{
public:

  void Clear();

  template <typename T>
  void SetVar(uint32_t var_name_hash, const T & val)
  {
    for (auto & elem : m_Vars)
    {
      if (elem.m_VarName == var_name_hash)
      {
        elem.m_Data = val;
        return;
      }
    }

    m_Vars.emplace_back(BlackboardVar{ var_name_hash, val });
  }

  template <typename T>
  Optional<T> GetVar(uint32_t var_name_hash)
  {
    for (auto & elem : m_Vars)
    {
      if (elem.m_VarName == var_name_hash)
      {
        auto val = elem.m_Data.Get<T>();
        if (val)
        {
          return *val;
        }

        return {};
      }
    }

    return {};
  }

private:

  struct BlackboardVar
  {
    uint32_t m_VarName;
    StaticAny<40> m_Data;
  };

  std::vector<BlackboardVar> m_Vars;
};

