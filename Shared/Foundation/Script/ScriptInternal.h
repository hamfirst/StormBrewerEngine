
#pragma once

#include "lua/lua.hpp"

#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Script/ScriptClass.h"
#include "Foundation/Script/ScriptFuncPtr.h"
#include "Foundation/Script/ScriptClassInstance.h"
#include "Foundation/Script/ScriptClassRef.h"

struct ScriptClassInstanceInfo
{
  ScriptClassRefData * m_RefData;
  std::size_t m_TypeNameHash;
};

class ScriptInternal
{
public:
  static lua_State * InitState(NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = lua_newstate(nullptr, nullptr, script_state);

    luaL_requiref(lua_state, "base", luaopen_base, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "package", luaopen_package, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "coroutine", luaopen_coroutine, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "string", luaopen_string, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "table", luaopen_table, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "math", luaopen_math, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "io", luaopen_io, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "debug", luaopen_debug, 1);
    lua_pop(lua_state, 1);

    luaL_requiref(lua_state, "utf8", luaopen_utf8, 1);
    lua_pop(lua_state, 1);

    lua_pushglobaltable(lua_state);
    lua_pushstring(lua_state, "global_objs");
    lua_newtable(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);

    return lua_state;
  }

  static void CloseState(void * state)
  {
    auto lua_state = static_cast<lua_State *>(state);
    lua_close(lua_state);
  }

  static lua_State * GetState(NotNullPtr<ScriptState> script_state)
  {
    return static_cast<lua_State *>(script_state->m_LuaState);
  }

  static bool LoadScriptBlock(NotNullPtr<ScriptState> script_state, const void * data, std::size_t length, czstr module_name)
  {
    auto lua_state = GetState(script_state);
    auto result = luaL_loadbuffer(lua_state, static_cast<const char *>(data), length, module_name);

    if(result == LUA_OK)
    {
      result = lua_pcall(lua_state, 0, 0, 0);
      if(result == LUA_OK)
      {
        return true;
      }
    }

    script_state->m_ErrorOutput(lua_tostring(lua_state, -1));
    lua_pop(lua_state, 1);
    return false;
  }

  static ScriptObject CreateScriptObject(NotNullPtr<ScriptState> script_state)
  {
    auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
    auto lua_state = GetState(script_state);

    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, global_id);
    lua_newtable(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);

    return ScriptObject(script_state, static_cast<int>(global_id));
  }

  static int CreateGlobalObjectFromStack(int pos, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_pushvalue(lua_state, pos);

    auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, global_id);
    lua_pushvalue(lua_state, -3);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 2);
    return global_id;
  }

  static void DeleteGlobalObject(NotNullPtr<ScriptState> script_state, int global_id)
  {
    auto lua_state = GetState(script_state);

    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, global_id);
    lua_pushnil(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);

    script_state->m_GlobalIdAllocator.Release(static_cast<std::size_t>(global_id) - 1);
  }

  static void LoadGlobalValue(czstr name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, name);
  }

  static void CreateGlobalTable(czstr name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_pushglobaltable(lua_state);
    lua_pushstring(lua_state, name);
    lua_newtable(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);
  }

  static void LoadGlobalObject(int global_id, lua_State * lua_state)
  {
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, global_id);
    lua_gettable(lua_state, -2);
    lua_replace(lua_state, -2);
  }

  static void LoadGlobalObject(int global_id, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    LoadGlobalObject(global_id, lua_state);
  }

  static void LoadTableValue(czstr name, const ScriptObject & object, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    lua_gettable(lua_state, -2);
    lua_replace(lua_state, -3);
    lua_pop(lua_state, 1);
  }

  static void * ReadTablePointer(czstr pointer_name, const ScriptObject & object, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, pointer_name);
    lua_gettable(lua_state, -2);
    auto ptr = lua_touserdata(lua_state, -1);
    lua_pop(lua_state, 3);
    return ptr;
  }

  static void * ReadGlobalTablePointer(czstr pointer_name, czstr table_name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, table_name);
    lua_pushstring(lua_state, pointer_name);
    lua_gettable(lua_state, -2);
    auto ptr = lua_touserdata(lua_state, -1);
    lua_pop(lua_state, 2);
    return ptr;
  }

  static NullOptPtr<ScriptClassInstanceInfo> ReadInstanceInfo(const ScriptClassInstance & instance, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, instance.m_GlobalId);
    lua_gettable(lua_state, -2);
    auto ptr = lua_touserdata(lua_state, -1);
    lua_pop(lua_state, 2);
    return static_cast<ScriptClassInstanceInfo *>(ptr);
  }

  static void WriteTableValue(czstr name, const ScriptObject & object, const ScriptValue & value, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    PushScriptValue(lua_state, value);
    lua_settable(lua_state, -2);
    lua_pop(lua_state, 2);
  }

  static void WriteTablePointer(czstr name, const ScriptObject & object, void * ptr, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    lua_pushlightuserdata(lua_state, ptr);
    lua_settable(lua_state, -2);
    lua_pop(lua_state, 2);
  }

  static void WriteTableFunction(czstr name, const ScriptObject & object, int (*Func)(lua_State *), NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    lua_pushcfunction(lua_state, Func);
    lua_settable(lua_state, -2);
    lua_pop(lua_state, 2);
  }

  static void WriteGlobalTableFunction(czstr func_name, czstr table_name, int (*Func)(lua_State *), NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, table_name);
    lua_pushstring(lua_state, func_name);
    lua_pushcfunction(lua_state, Func);
    lua_settable(lua_state, -2);
    lua_pop(lua_state, 1);
  }

  static void WriteGlobalTablePointer(czstr ptr_name, czstr table_name, void * ptr, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    lua_getglobal(lua_state, table_name);
    lua_pushstring(lua_state, ptr_name);
    lua_pushlightuserdata(lua_state, ptr);
    lua_settable(lua_state, -2);
    lua_pop(lua_state, 1);
  }

  static bool CallScriptFunc(NotNullPtr<ScriptState> script_state,
          const std::initializer_list<ScriptValue> & initializer_list, int num_results)
  {
    auto lua_state = GetState(script_state);

    if(lua_type(lua_state, -1) != LUA_TFUNCTION)
    {
      lua_pop(lua_state, 1);
      return false;
    }

    int args = 0;
    for(auto & elem : initializer_list)
    {
      PushScriptValue(lua_state, elem);
      args++;
    }

    auto result = lua_pcall(lua_state, args, num_results, 0);
    if(result == LUA_OK)
    {
       return true;
    }

    script_state->m_ErrorOutput(lua_tostring(lua_state, -1));
    lua_pop(lua_state, 1);
    return false;
  }

  static ScriptValue SaveScriptValueFromStack(NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);

    switch(lua_type(lua_state, -1))
    {
      case LUA_TBOOLEAN:
      {
        auto val = lua_toboolean(lua_state, -1);
        lua_pop(lua_state, 1);
        return ScriptValue(val);
      }
      case LUA_TNUMBER:
      {
        if(lua_isinteger(lua_state, -1))
        {
          auto val = lua_tointeger(lua_state, -1);
          lua_pop(lua_state, 1);
          return ScriptValue((int)val);
        }
        else
        {
          auto val = lua_tonumber(lua_state, -1);
          lua_pop(lua_state, 1);
          return ScriptValue((float)val);
        }
      }
      case LUA_TSTRING:
      {
        std::string str = lua_tostring(lua_state, -1);
        lua_pop(lua_state, 1);
        return ScriptValue(std::move(str));
      }
      case LUA_TTABLE:
      {
        auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
        lua_getglobal(lua_state, "global_objs");
        lua_pushnumber(lua_state, global_id);
        lua_pushvalue(lua_state, -3);
        lua_settable(lua_state, -3);
        lua_pop(lua_state, 2);
        return ScriptValue(ScriptObject(script_state, static_cast<int>(global_id)));
      }
      case LUA_TFUNCTION:
      {
        auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
        lua_getglobal(lua_state, "global_objs");
        lua_pushnumber(lua_state, global_id);
        lua_pushvalue(lua_state, -3);
        lua_settable(lua_state, -3);
        lua_pop(lua_state, 2);
        return ScriptValue(ScriptFuncPtr(script_state, static_cast<int>(global_id)));
      }
      case LUA_TUSERDATA:
      {
        auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
        lua_getglobal(lua_state, "global_objs");
        lua_pushnumber(lua_state, global_id);
        lua_pushvalue(lua_state, -3);
        lua_settable(lua_state, -3);
        lua_pop(lua_state, 2);
        return ScriptValue(ScriptClassInstance(script_state, static_cast<int>(global_id)));
      }
    }

    lua_pop(lua_state, 1);
    return ScriptValue();
  }

  static void PushValue(lua_State * state, int t)
  {
    lua_pushnumber(state, t);
  }

  static void PushValue(lua_State * state, float t)
  {
    lua_pushnumber(state, t);
  }

  static void PushValue(lua_State * state, bool t)
  {
    lua_pushboolean(state, t);
  }

  static void PushValue(lua_State * state, czstr t)
  {
    lua_pushstring(state, t);
  }

  static void PushValue(lua_State * state, const std::string & t)
  {
    lua_pushstring(state, t.data());
  }

  static void PushValue(lua_State * state, const ScriptObject & t)
  {
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushValue(lua_State * state, const ScriptClassInstance & t)
  {
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushValue(lua_State * state, const ScriptFuncPtr & t)
  {
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushScriptValue(lua_State * state, const ScriptValue & val)
  {
    switch(val.GetCurrentTypeIndex())
    {
      case -1:
        lua_pushnil(state);
        break;
      case 0:
        PushValue(state, val.GetAs<int>());
        break;
      case 1:
        PushValue(state, val.GetAs<float>());
        break;
      case 2:
        PushValue(state, val.GetAs<bool>());
        break;
      case 3:
        PushValue(state, val.GetAs<czstr>());
        break;
      case 4:
        PushValue(state, val.GetAs<std::string>());
        break;
      case 5:
        PushValue(state, val.GetAs<ScriptObject>());
        break;
      case 6:
        PushValue(state, *val.GetAs<std::shared_ptr<ScriptObject>>());
        break;
      case 7:
        PushValue(state, val.GetAs<ScriptClassInstance>());
        break;
      case 8:
        PushValue(state, *val.GetAs<std::shared_ptr<ScriptClassInstance>>());
        break;
      case 9:
        PushValue(state, val.GetAs<ScriptFuncPtr>());
        break;
      case 10:
        PushValue(state, *val.GetAs<std::shared_ptr<ScriptFuncPtr>>());
        break;
    }

    static_assert(ScriptValue::kNumTypes == 11);
  }
};


