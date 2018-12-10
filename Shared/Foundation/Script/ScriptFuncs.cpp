
#include "Foundation/Common.h"
#include "Foundation/Script/ScriptInternal.h"
#include "Foundation/Script/ScriptFuncs.h"

void ScriptFuncs::PushValue(void * state, const int & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  lua_pushnumber(lua_state, val);
}

void ScriptFuncs::PushValue(void * state, const float & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  lua_pushnumber(lua_state, val);
}

void ScriptFuncs::PushValue(void * state, const bool & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  lua_pushboolean(lua_state, val);
}

void ScriptFuncs::PushValue(void * state, const std::string & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  lua_pushstring(lua_state, val.data());
}

void ScriptFuncs::PushValue(void * state, const ScriptObject & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  ScriptInternal::LoadGlobalObject(val.m_GlobalId, lua_state);
}

void ScriptFuncs::PushValue(void * state, const ScriptClassInstance & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  ScriptInternal::LoadGlobalObject(val.m_GlobalId, lua_state);
}

void ScriptFuncs::PushValue(void * state, const ScriptFuncPtr & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  ScriptInternal::LoadGlobalObject(val.m_GlobalId, lua_state);
}

void ScriptFuncs::PushInstance(void * state, ScriptClassRefData * ref_data, std::size_t type_id_hash)
{
  auto lua_state = static_cast<lua_State *>(state);
  auto ptr = static_cast<ScriptClassInstanceInfo *>(lua_newuserdata(lua_state, sizeof(ScriptClassInstanceInfo)));

  ptr->m_RefData = ref_data;
  ptr->m_TypeNameHash = type_id_hash;

  ref_data->IncRef();
}

void ScriptFuncs::PullValue(void * state, int & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<int>(lua_tonumber(lua_state, -1));
}

void ScriptFuncs::PullValue(void * state, float & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<float>(lua_tonumber(lua_state, -1));
}

void ScriptFuncs::PullValue(void * state, bool & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<bool>(lua_toboolean(lua_state, -1));
}

void ScriptFuncs::PullValue(void * state, std::string & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = lua_tostring(lua_state, -1);
}

void ScriptFuncs::PullValue(void * state, ScriptObject & val)
{
  FetchValue(state, -1, val);
}

void ScriptFuncs::PullValue(void * state, ScriptClassInstance & val)
{
  FetchValue(state, -1, val);
}

void ScriptFuncs::PullValue(void * state, ScriptFuncPtr & val)
{
  FetchValue(state, -1, val);
}

bool ScriptFuncs::FetchValue(void * state, int pos, int & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<int>(lua_tonumber(lua_state, pos));
  return true;
}

bool ScriptFuncs::FetchValue(void * state, int pos, float & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<float>(lua_tonumber(lua_state, pos));
  return true;
}

bool ScriptFuncs::FetchValue(void * state, int pos, bool & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = static_cast<bool>(lua_toboolean(lua_state, pos));
  return true;
}

bool ScriptFuncs::FetchValue(void * state, int pos, std::string & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  val = lua_tostring(lua_state, pos);
  return true;
}
;
bool ScriptFuncs::FetchValue(void * state, int pos, ScriptObject & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  if (lua_istable(lua_state, pos) == false)
  {
    val = {};
    return false;
  }


  auto script_state = static_cast<ScriptState *>(lua_getmanager(lua_state));
  auto global_id = ScriptInternal::CreateGlobalObjectFromStack(pos, script_state);

  val = ScriptObject(script_state, global_id);
  return true;
}

bool ScriptFuncs::FetchValue(void * state, int pos, ScriptClassInstance & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  if (lua_type(lua_state, pos) != LUA_TUSERDATA)
  {
    val = {};
    return false;
  }

  auto script_state = static_cast<ScriptState *>(lua_getmanager(lua_state));
  auto global_id = ScriptInternal::CreateGlobalObjectFromStack(pos, script_state);

  val = ScriptClassInstance(script_state, global_id);
  return true;
}

bool ScriptFuncs::FetchValue(void * state, int pos, ScriptFuncPtr & val)
{
  auto lua_state = static_cast<lua_State *>(state);
  if (lua_isfunction(lua_state, pos) == false)
  {
    val = {};
    return false;
  }

  auto script_state = static_cast<ScriptState *>(lua_getmanager(lua_state));
  auto global_id = ScriptInternal::CreateGlobalObjectFromStack(pos, script_state);

  val = ScriptFuncPtr(script_state, global_id);
  return true;
}

std::pair<NullOptPtr<ScriptClassRefData>, std::size_t> ScriptFuncs::FetchInstanceInfo(void * state, int pos)
{
  auto lua_state = static_cast<lua_State *>(state);
  if(lua_type(lua_state, pos) != LUA_TUSERDATA)
  {
    return std::make_pair(nullptr, 0);
  }

  auto val = lua_touserdata(lua_state, pos);
  auto inst_info = static_cast<ScriptClassInstanceInfo *>(val);
  return std::make_pair(inst_info->m_RefData, inst_info->m_TypeNameHash);
}

bool ScriptFuncs::CheckArgCount(void * state, int args)
{
  auto lua_state = static_cast<lua_State *>(state);
  return lua_gettop(lua_state) == args + 1; // One extra for self
}

bool ScriptFuncs::CallFunc(void * state, int num_args, int num_results)
{
  auto lua_state = static_cast<lua_State *>(state);
  auto result = lua_pcall(lua_state, num_args, num_results, 0);
  if(result != LUA_OK)
  {
    auto error = lua_tostring(lua_state, -1);
    ReportError(state, error);
    lua_pop(lua_state, 1);
    return false;
  }

  return true;
}

void ScriptFuncs::Discard(void * state, int num_stack_vals)
{
  auto lua_state = static_cast<lua_State *>(state);
  lua_pop(lua_state, num_stack_vals);
}

void ScriptFuncs::ReportError(void * state, czstr message)
{
  auto lua_state = static_cast<lua_State *>(state);
  auto script_state = static_cast<ScriptState *>(lua_getmanager(lua_state));

  script_state->m_ErrorOutput(message);
}

