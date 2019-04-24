#pragma once

#include "StormRefl/StormReflMetaFuncs.h"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptFuncs.h"

template <typename T>
struct CreateScriptDataObjectStruct;

template <typename T>
void SetScriptDataObjectValue(NotNullPtr<ScriptState> state, std::size_t index, const T & t)
{
  ScriptFuncs::PushValue(state->m_LuaState, (int)index + 1);

  if constexpr ((std::is_class_v<T> && !std::is_same_v<T, std::string>) || std::is_array_v<T>)
  {
    auto obj = CreateScriptDataObjectStruct<T>::CreateScriptDataObject(state, t);
    ScriptFuncs::PushValue(state->m_LuaState, obj);
  }
  else
  {
    ScriptFuncs::PushValue(state->m_LuaState, t);
  }

  ScriptFuncs::SetTableValue(state->m_LuaState);
}

template <typename T>
void SetScriptDataObjectValue(NotNullPtr<ScriptState> state, czstr name, const T & t)
{
  ScriptFuncs::PushValue(state->m_LuaState, name);

  if constexpr ((std::is_class_v<T> && !std::is_same_v<T, std::string>) || std::is_array_v<T>)
  {
    auto obj = CreateScriptDataObjectStruct<T>::CreateScriptDataObject(state, t);
    ScriptFuncs::PushValue(state->m_LuaState, obj);
  }
  else
  {
    ScriptFuncs::PushValue(state->m_LuaState, t);
  }

  ScriptFuncs::SetTableValue(state->m_LuaState);
}

template <typename T>
struct CreateScriptDataObjectStruct
{
  static ScriptObject CreateScriptDataObject(NotNullPtr<ScriptState> state, const T & t)
  {
    auto obj = state->CreateScriptObject();
    ScriptFuncs::PushValue(state->m_LuaState, obj);

    StormReflVisitEach(t, [&](auto & f)
    {
      SetScriptDataObjectValue(state, f.GetName(), f.Get());
    });

    ScriptFuncs::Discard(state->m_LuaState, 1);
    return obj;
  }
};

template <typename T>
struct CreateScriptDataObjectStruct<std::vector<T>>
{
  static ScriptObject CreateScriptDataObject(NotNullPtr<ScriptState> state, const std::vector<T> & t)
  {
    auto obj = state->CreateScriptObject();
    ScriptFuncs::PushValue(state->m_LuaState, obj);

    for(std::size_t index = 0, end = t.size(); index < end; ++index)
    {
      SetScriptDataObjectValue(state, index, t[index]);
    }

    ScriptFuncs::Discard(state->m_LuaState, 1);
    return obj;
  }
};

template <typename T, int i>
struct CreateScriptDataObjectStruct<T[i]>
{
  static ScriptObject CreateScriptDataObject(NotNullPtr<ScriptState> state, const T(&t)[i])
  {
    auto obj = state->CreateScriptObject();
    ScriptFuncs::PushValue(state->m_LuaState, obj);

    for(std::size_t index = 0; index < i; ++index)
    {
      SetScriptDataObjectValue(state, index, t[index]);
    }

    ScriptFuncs::Discard(state->m_LuaState, 1);
    return obj;
  }
};

template <typename T>
ScriptObject CreateScriptDataObject(NotNullPtr<ScriptState> state, const T & t)
{
  return CreateScriptDataObjectStruct<T>::CreateScriptDataObject(state, t);
}

template <typename T>
ScriptObject CreateScriptDataObject(NotNullPtr<ScriptState> state, const T * t)
{
  return CreateScriptDataObjectStruct<T>::CreateScriptDataObject(state, *t);
}

