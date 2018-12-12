
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
    auto adder = c.template GetFunctionAdder<ReturnTypeT, ArgsT...>();
    adder.template AddFunction<Func>(name);
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

    auto func_ptr = &ScriptClass<ClassT>::template AddMember<MemberType, FieldInfo::GetMemberPtr()>;
    (c.*func_ptr)(f.GetName());
  });

  StormReflFuncVisitor<ClassT>::VisitFuncs([&](auto f)
  {
    using FieldInfo = decltype(f);

    auto reg_info = ScriptFuncRegisterClassInfo(f.GetFunctionPtr());
    reg_info.template Register<FieldInfo::GetFunctionPtr()>(f.GetName(), c);
  });
}

template <typename T>
void ScriptClass<T>::Register()
{
  ScriptClassRegister(*this);
}
