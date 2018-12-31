
#include "Foundation/Common.h"
#include "Foundation/Script/ScriptClass.h"
#include "Foundation/Script/ScriptObject.h"
#include "Foundation/Script/ScriptState.h"
#include "Foundation/Script/ScriptInternal.h"
#include "Foundation/Script/ScriptFuncs.h"
#include "Foundation/Script/ScriptRegister.h"

class ScriptClassInternal
{
public:
  static int ScriptClassNew(lua_State * state)
  {
    if(lua_gettop(state) != 1)
    {
      ScriptFuncs::ReportError(state, "Not passing self to the new function.  Use the colon operator (eg Clickable:new())");
      return 0;
    }

    lua_pushstring(state, "ptr");
    lua_gettable(state, -2);

    auto ptr = static_cast<ScriptClassBase *>(lua_touserdata(state, -1));
    if(ptr == nullptr)
    {
      ScriptFuncs::ReportError(state, "Couldn't load class pointer");
      return 0;
    }

    auto obj = ptr->CreateNewObject();
    auto info = static_cast<ScriptClassInstanceInfo *>(lua_newuserdata(state, sizeof(ScriptClassInstanceInfo)));

    lua_getglobal(state, ptr->m_Name.c_str());
    lua_setmetatable(state, -2);

    info->m_RefData = new ScriptClassRefData;
    info->m_RefData->m_Class = ptr;
    info->m_RefData->m_Instance = obj;
    info->m_RefData->m_RefCount = 1;
    info->m_TypeNameHash = ptr->GetTypeNameHash();

    ptr->BootstrapObject(info->m_RefData);
    return 1;
  }

  static int ScriptClassDelete(lua_State * state)
  {
    if(lua_gettop(state) != 1)
    {
      ScriptFuncs::ReportError(state, "Invalid arguments to the delete function");
      return 0;
    }

    auto info = static_cast<ScriptClassInstanceInfo *>(lua_touserdata(state, -1));
    if(info == nullptr)
    {
      ScriptFuncs::ReportError(state, "Couldn't load object pointer");
      return 0;
    }

    if(info->m_RefData == nullptr)
    {
      ScriptFuncs::ReportError(state, "Inconsistent userdata");
      return 0;
    }

    info->m_RefData->DeleteInst();
    return 0;
  }

  static int ScriptClassRelease(lua_State * state)
  {
    if(lua_gettop(state) != 1)
    {
      ScriptFuncs::ReportError(state, "Invalid arguments to the release function");
      return 0;
    }

    auto info = static_cast<ScriptClassInstanceInfo *>(lua_touserdata(state, -1));
    if(info == nullptr)
    {
      ScriptFuncs::ReportError(state, "Couldn't load object pointer");
      return 0;
    }

    if(info->m_RefData == nullptr)
    {
      ScriptFuncs::ReportError(state, "Inconsistent userdata");
      return 0;
    }

    info->m_RefData->DecRef();
    return 0;
  }

  static int ScriptClassRead(lua_State *state)
  {
    if (lua_gettop(state) != 2)
    {
      ScriptFuncs::ReportError(state, "Invalid number of arguments to the read function");
      return 0;
    }

    auto user_data_ptr = lua_touserdata(state, 1);
    auto field_name = lua_tostring(state, 2);

    if (user_data_ptr == nullptr || field_name == nullptr)
    {
      ScriptFuncs::ReportError(state, "Improper arguments passed to read function");
      return 0;
    }

    auto inst_info = static_cast<ScriptClassInstanceInfo *>(user_data_ptr);
    if(inst_info->m_RefData == nullptr)
    {
      ScriptFuncs::ReportError(state, "Inconsistent userdata");
      return 0;
    }

    if(inst_info->m_RefData->m_Instance == nullptr)
    {
      ScriptFuncs::ReportError(state, "Class instance has already been deleted");
      return 0;
    }

    auto name_hash = crc32(field_name);

    auto member_itr = inst_info->m_RefData->m_Class->m_ReadMethods.find(name_hash);
    if (member_itr != inst_info->m_RefData->m_Class->m_ReadMethods.end())
    {
      auto func = member_itr->second;
      func(inst_info->m_RefData->m_Instance, state);
      return 1;
    }

    auto func_itr = inst_info->m_RefData->m_Class->m_CallMethods.find(name_hash);
    if(func_itr != inst_info->m_RefData->m_Class->m_CallMethods.end())
    {
      lua_pushcfunction(state, func_itr->second);
      return 1;
    }

    static const uint32_t kDeleteHash = COMPILE_TIME_CRC32_STR("delete");
    if(name_hash == kDeleteHash)
    {
      lua_pushcfunction(state, ScriptClassDelete);
      return 1;
    }

    auto error_msg = std::string("Invalid member variable ") + field_name;
    ScriptFuncs::ReportError(state, error_msg.c_str());
    return 0;
  }

  static int ScriptClassWrite(lua_State *state)
  {
    if (lua_gettop(state) != 3)
    {
      ScriptFuncs::ReportError(state, "Invalid number of arguments to the write function");
      return 0;
    }

    auto user_data_ptr = lua_touserdata(state, 1);
    auto field_name = lua_tostring(state, 2);

    if (user_data_ptr == nullptr || field_name == nullptr)
    {
      ScriptFuncs::ReportError(state, "Improper arguments to the write function");
      return 0;
    }

    auto inst_info = static_cast<ScriptClassInstanceInfo *>(user_data_ptr);
    if(inst_info->m_RefData->m_Instance == nullptr)
    {
      ScriptFuncs::ReportError(state, "Instance has already been freed");
      return 0;
    }

    auto name_hash = crc32(field_name);

    auto member_itr = inst_info->m_RefData->m_Class->m_WriteMethods.find(name_hash);
    if (member_itr != inst_info->m_RefData->m_Class->m_WriteMethods.end())
    {
      auto func = member_itr->second;
      func(inst_info->m_RefData->m_Instance, state);
      return 0;
    }

    auto error_msg = std::string("Invalid member variable ") + field_name;
    ScriptFuncs::ReportError(state, error_msg.c_str());
    return 0;
  }
};

ScriptClassBase::ScriptClassBase(czstr name)
{
  m_Name = name;
}

void ScriptClassBase::RegisterBase(NotNullPtr<ScriptState> script_state)
{
  ScriptInternal::CreateGlobalTable(m_Name.c_str(), script_state);
  ScriptInternal::WriteGlobalTablePointer("ptr", m_Name.c_str(), this, script_state);

  ScriptInternal::WriteGlobalTableFunction("__index", m_Name.c_str(), ScriptClassInternal::ScriptClassRead, script_state);
  ScriptInternal::WriteGlobalTableFunction("__newindex", m_Name.c_str(), ScriptClassInternal::ScriptClassWrite, script_state);
  ScriptInternal::WriteGlobalTableFunction("__gc", m_Name.c_str(), ScriptClassInternal::ScriptClassRelease, script_state);
  ScriptInternal::WriteGlobalTableFunction("new", m_Name.c_str(), ScriptClassInternal::ScriptClassNew, script_state);
}

void * ScriptClassBase::ReadObjPointer(void * state)
{
  auto lua_state = static_cast<lua_State *>(state);
  auto user_data_ptr = lua_touserdata(lua_state, 1);
  if(user_data_ptr == nullptr)
  {
    return nullptr;
  }

  auto inst_info = static_cast<ScriptClassInstanceInfo *>(user_data_ptr);
  return inst_info->m_RefData->m_Instance;
}

ScriptClassBase * ScriptClassBase::ReadClassPointer(void * state)
{
  auto lua_state = static_cast<lua_State *>(state);
  if(lua_type(lua_state, 1) != LUA_TLIGHTUSERDATA)
  {
    return nullptr;
  }

  auto user_data_ptr = lua_touserdata(lua_state, 1);
  if(user_data_ptr == nullptr)
  {
    return nullptr;
  }

  auto inst_info = static_cast<ScriptClassInstanceInfo *>(user_data_ptr);
  return inst_info->m_RefData->m_Class;
}
