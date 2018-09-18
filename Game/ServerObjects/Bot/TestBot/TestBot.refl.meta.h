#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "TestBot.refl.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<TestBotInitData>
{
  using MyBase = BotServerObjectInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "TestBotInitData"; }
  static constexpr auto GetNameHash() { return 0x1ACAD19B; }
  static TestBotInitData & GetDefault() { static TestBotInitData def; return def; }
};

template <>
struct StormReflTypeInfo<TestBot>
{
  using MyBase = BotServerObject;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "TestBot"; }
  static constexpr auto GetNameHash() { return 0x8EF3BA04; }
  static TestBot & GetDefault() { static TestBot def; return def; }
};

template <>
struct StormReflTypeInfo<TestBot>::field_data_static<0 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  using member_type = BotBehaviorTree; // StormBehaviorTree<BotServerObject, GameLogicContainer>
  static constexpr auto GetName() { return "m_Tree"; }
  static constexpr auto GetType() { return "StormBehaviorTree<BotServerObject, GameLogicContainer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x89A3CBC3; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4BF05A2; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<BotServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &TestBot::m_Tree; }
};

template <typename Self>
struct StormReflTypeInfo<TestBot>::field_data<0 + StormReflTypeInfo<BotServerObject>::fields_n, Self> : public StormReflTypeInfo<TestBot>::field_data_static<0 + StormReflTypeInfo<BotServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, BotBehaviorTree> & Get() { return self.m_Tree; }
  std::add_const_t<std::remove_reference_t<BotBehaviorTree>> & Get() const { return self.m_Tree; }
  void SetDefault() { self.m_Tree = StormReflTypeInfo<TestBot>::GetDefault().m_Tree; }
};

template <>
struct StormReflFuncInfo<TestBot>
{
  using MyBase = BotServerObject;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct TestBot
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct TestBot::type_info<0>
  {
    using type = ::TestBotInitData;
  };

  template <>
  struct TestBot::type_info<1>
  {
    using type = ::TestBot;
  };

}

