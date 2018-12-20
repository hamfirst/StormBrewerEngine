
#pragma once


#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptValue.h"
#include "Foundation/Script/ScriptClass.h"
#include "Foundation/Script/ScriptFuncs.h"
#include "Foundation/Script/ScriptFuncPtr.h"
#include "Foundation/Script/ScriptClassInstance.h"
#include "Foundation/Script/ScriptClassRef.h"

#include "lua/lua.hpp"


struct ScriptClassInstanceInfo
{
  ScriptClassRefData * m_RefData;
  std::size_t m_TypeNameHash;
};

struct ScriptStackCheck
{
  ScriptStackCheck(lua_State * lua_state, int expected_change = 0)
  {
    state = lua_state;
    top = lua_gettop(state);
    change = expected_change;
    ASSERT(top >= 0, "Stack is messed up");
  }

  ~ScriptStackCheck()
  {
    auto new_top = lua_gettop(state);    
    ASSERT(new_top >= 0, "Stack is messed up");
    ASSERT(top + change == new_top, "Stack size is incorrect");
  }

  lua_State * state;
  int top;
  int change;
};

class ScriptInternal
{
public:

  static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
  {
    (void)ud; (void)osize;  /* not used */
    if (nsize == 0)
    {
      //printf("Freeing %p\n",  ptr);
      free(ptr);
      return NULL;
    }
    else
    {
      auto new_ptr = realloc(ptr, nsize);
      //printf("Allocating %p, (%p)\n", new_ptr, ptr);
      return new_ptr;
    }
  }

  static int StackDump(lua_State * lua_state)
  {
    int i;
    int top = lua_gettop(lua_state);
    for (i = 1; i <= top; i++)
    {
      int t = lua_type(lua_state, i);
      printf("%d. ", i);
      switch (t)
      {
      case LUA_TSTRING:  /* strings */
        printf("`%s'", lua_tostring(lua_state, i));
        break;

      case LUA_TBOOLEAN:  /* booleans */
        printf(lua_toboolean(lua_state, i) ? "true" : "false");
        break;

      case LUA_TNUMBER:  /* numbers */
        printf("%g", lua_tonumber(lua_state, i));
        break;

      default:  /* other values */
        printf("%s", lua_typename(lua_state, t));
        break;
      }
      printf("\n");  /* put a separator */
    }

    printf("\n");  /* end the listing */
    return 0;
  }

  static int Print(lua_State *L)
  {
    std::string output;

    int n = lua_gettop(L);  /* number of arguments */
    int i;
    lua_getglobal(L, "tostring");
    for (i=1; i<=n; i++) {
      const char *s;
      size_t l;
      lua_pushvalue(L, -1);  /* function to be called */
      lua_pushvalue(L, i);   /* value to print */
      lua_call(L, 1, 1);
      s = lua_tolstring(L, -1, &l);  /* get result */
      if (s == NULL)
        return luaL_error(L, "'tostring' must return a string to 'print'");
      if (i>1) output += "\t";
      output += s;
      lua_pop(L, 1);  /* pop result */
    }

    ScriptFuncs::ReportMessage(L, output.c_str());
    return 0;
  }

  static lua_State * InitState(NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = lua_newstate(l_alloc, script_state);
    lua_atpanic(lua_state, StackDump);
    
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

    lua_pushstring(lua_state, "print");
    lua_pushcfunction(lua_state, Print);
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
    ScriptStackCheck check(lua_state);
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
    ScriptStackCheck check(lua_state);

    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, static_cast<lua_Number>(global_id));
    lua_newtable(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);

    return ScriptObject(script_state, static_cast<int>(global_id));
  }

  static void CreateGlobalFromScriptObject(czstr name, const ScriptValue & value, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);

    PushScriptValue(lua_state, value);
    lua_setglobal(lua_state, name);
  }

  static int CreateGlobalObjectFromStack(int pos, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_pushvalue(lua_state, pos);

    auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, static_cast<lua_Number>(global_id));
    lua_pushvalue(lua_state, -3);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 2);
    return static_cast<int>(global_id);
  }

  static void DeleteGlobalObject(NotNullPtr<ScriptState> script_state, int global_id)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);

    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, global_id);
    lua_pushnil(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);

    script_state->m_GlobalIdAllocator.Release(static_cast<std::size_t>(global_id) - 1);
  }

  static void CreateGlobalTable(czstr name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_pushglobaltable(lua_state);
    lua_pushstring(lua_state, name);
    lua_newtable(lua_state);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);
  }

  static void LoadGlobalValue(czstr name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state, 1);
    lua_getglobal(lua_state, name);
  }

  static void LoadGlobalObject(int global_id, lua_State * lua_state)
  {
    ScriptStackCheck check(lua_state, 1);
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
    ScriptStackCheck check(lua_state, 1);
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
    ScriptStackCheck check(lua_state);
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
    ScriptStackCheck check(lua_state);
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
    ScriptStackCheck check(lua_state);
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
    ScriptStackCheck check(lua_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    PushScriptValue(lua_state, value);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 2);
  }

  static void WriteTablePointer(czstr name, const ScriptObject & object, void * ptr, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    lua_pushlightuserdata(lua_state, ptr);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 2);
  }

  static void WriteTableFunction(czstr name, const ScriptObject & object, int (*Func)(lua_State *), NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_getglobal(lua_state, "global_objs");
    lua_pushnumber(lua_state, object.m_GlobalId);
    lua_gettable(lua_state, -2);
    lua_pushstring(lua_state, name);
    lua_pushcfunction(lua_state, Func);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 2);
  }

  static void WriteGlobalTableFunction(czstr func_name, czstr table_name, int (*Func)(lua_State *), NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_getglobal(lua_state, table_name);
    lua_pushstring(lua_state, func_name);
    lua_pushcfunction(lua_state, Func);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);
  }

  static void WriteGlobalTablePointer(czstr ptr_name, czstr table_name, void * ptr, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_getglobal(lua_state, table_name);
    lua_pushstring(lua_state, ptr_name);
    lua_pushlightuserdata(lua_state, ptr);
    lua_settable(lua_state, -3);
    lua_pop(lua_state, 1);
  }

  static void DeleteGlobal(czstr name, NotNullPtr<ScriptState> script_state)
  {
    auto lua_state = GetState(script_state);
    ScriptStackCheck check(lua_state);
    lua_pushglobaltable(lua_state);
    lua_pushstring(lua_state, name);
    lua_pushnil(lua_state);
    lua_settable(lua_state, -3);
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
    ScriptStackCheck check(lua_state, -1);

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
        lua_pushnumber(lua_state, static_cast<lua_Number>(global_id));
        lua_pushvalue(lua_state, -3);
        lua_settable(lua_state, -3);
        lua_pop(lua_state, 2);
        return ScriptValue(ScriptObject(script_state, static_cast<int>(global_id)));
      }
      case LUA_TFUNCTION:
      {
        auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
        lua_getglobal(lua_state, "global_objs");
        lua_pushnumber(lua_state, static_cast<lua_Number>(global_id));
        lua_pushvalue(lua_state, -3);
        lua_settable(lua_state, -3);
        lua_pop(lua_state, 2);
        return ScriptValue(ScriptFuncPtr(script_state, static_cast<int>(global_id)));
      }
      case LUA_TUSERDATA:
      {
        auto global_id = script_state->m_GlobalIdAllocator.Allocate() + 1;
        lua_getglobal(lua_state, "global_objs");
        lua_pushnumber(lua_state, static_cast<lua_Number>(global_id));
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
    ScriptStackCheck check(state, 1);
    lua_pushnumber(state, t);
  }

  static void PushValue(lua_State * state, float t)
  {
    ScriptStackCheck check(state, 1);
    lua_pushnumber(state, t);
  }

  static void PushValue(lua_State * state, bool t)
  {
    ScriptStackCheck check(state, 1);
    lua_pushboolean(state, t);
  }

  static void PushValue(lua_State * state, czstr t)
  {
    ScriptStackCheck check(state, 1);
    lua_pushstring(state, t);
  }

  static void PushValue(lua_State * state, const std::string & t)
  {
    ScriptStackCheck check(state, 1);
    lua_pushstring(state, t.data());
  }

  static void PushValue(lua_State * state, const ScriptObject & t)
  {
    ScriptStackCheck check(state, 1);
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushValue(lua_State * state, const ScriptClassInstance & t)
  {
    ScriptStackCheck check(state, 1);
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushValue(lua_State * state, const ScriptFuncPtr & t)
  {
    ScriptStackCheck check(state, 1);
    lua_getglobal(state, "global_objs");
    lua_pushnumber(state, t.m_GlobalId);
    lua_gettable(state, -2);
    lua_replace(state, -2);
  }

  static void PushScriptValue(lua_State * state, const ScriptValue & val)
  {
    ScriptStackCheck check(state, 1);
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


