
#pragma once

#include "StormRefl/StormRefl.h"
#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflMetaCall.h"
#include "StormRefl/StormReflMetaEnum.h"

#include "Foundation/Script/ScriptClass.h"

template <typename T>
class ScriptClass;

template <typename ReturnTypeT, typename ClassT, typename ... ArgsT>
struct ScriptFuncRegisterInfo
{
  using ReturnType = ReturnTypeT;
  using Class = ClassT;
  using ArgsTuple = std::tuple<ArgsT...>;

  template <typename FieldInfoType>
  void Register(czstr name, ScriptClass<ClassT> & c)
  {
    auto adder = c.template GetFunctionAdder<FieldInfoType, ReturnTypeT, ArgsT...>();
    adder.AddFunction(name);
  }
};

template <typename ReturnTypeT, typename ClassT, typename ... ArgsT>
auto ScriptFuncRegisterClassInfo(ReturnTypeT (ClassT::*Func)(ArgsT...))
{
  return ScriptFuncRegisterInfo<ReturnTypeT, ClassT, ArgsT...>{};
}

template <typename ClassT>
void ScriptClassRegister(ScriptClass<ClassT> & c)
{
  StormReflVisitStatic<ClassT>::VisitEach([&](auto f)
  {
    using FieldInfo = decltype(f);
    using MemberType = typename FieldInfo::member_type;
    using ScriptClassT = ScriptClass<ClassT>;

    auto hash = FieldInfo::GetFieldNameHash();

    auto read_method = [](const void * ptr, void * state)
    {
      auto obj = static_cast<const ClassT *>(ptr);
      auto mem_ptr = FieldInfo::GetMemberPtr();
      auto & val = obj->*mem_ptr;

      ScriptClassPushMember<MemberType>::Process(val, state);
    };

    c.m_ReadMethods.emplace(std::make_pair(hash, read_method));

    auto write_method = [](void * ptr, void * state)
    {
      auto obj = static_cast<ClassT *>(ptr);
      auto mem_ptr = FieldInfo::GetMemberPtr();
      auto & val = obj->*mem_ptr;

      ScriptClassAssignMember<MemberType>::Process(val, state);
    };

    c.m_WriteMethods.emplace(std::make_pair(hash, write_method));
  });

  StormReflFuncVisitor<ClassT>::VisitFuncs([&](auto f)
  {
    using FieldInfo = decltype(f);

    auto reg_info = ScriptFuncRegisterClassInfo(f.GetFunctionPtr());
    reg_info.template Register<FieldInfo>(f.GetName(), c);
  });
}

template <typename T>
void ScriptClass<T>::Register(NotNullPtr<ScriptState> state)
{
  ScriptClassRegister(*this);
  RegisterBase(state);
}

template <typename EnumType>
void ScriptAddEnumAsGlobals(NotNullPtr<ScriptState> state)
{
  StormReflVisitEnumValues<EnumType>::VisitEach([&](auto f){
    state->SetGlobal(f.GetName(), static_cast<int>(f.GetValue()));
  });
}
