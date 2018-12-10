
#pragma once

#include "StormRefl/StormRefl.h"
#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflMetaCall.h"

#include "Foundation/Script/ScriptClass.h"

template <typename T>
class ScriptClass;

template <typename ReturnTypeT, typename ClassT, typename ... ArgsT>
struct ScriptFuncRegisterInfo
{
  using ReturnType = ReturnTypeT;
  using Class = ClassT;
  using ArgsTuple = std::tuple<ArgsT...>;

  template <ReturnTypeT (ClassT::*Func)(ArgsT...)>
  void Register(czstr name, ScriptClass<ClassT> & c)
  {
    c.template AddFunction<ReturnTypeT, ArgsT..., Func>(name);
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

    constexpr auto field_ptr = FieldInfo::GetMemberPtr();
    //c.template AddMember<MemberType, field_ptr>(f.GetName());
  });

  StormReflFuncVisitor<ClassT>::VisitFuncs([&](auto f)
  {
//    auto reg_info = ScriptFuncRegisterClassInfo(f.GetFunctionPtr());
//    reg_info.Register(f.GetName());
  });
}

template <typename T>
void ScriptClass<T>::Register()
{
  ScriptClassRegister(*this);
}
