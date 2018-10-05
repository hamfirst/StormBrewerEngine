#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileServerObject.refl.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.meta.h"
#include "Game/Configs/ProjectileConfig.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ProjectileServerObjectInitData>
{
  using MyBase = GameServerObjectBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x5A391BFB; }
  static ProjectileServerObjectInitData & GetDefault() { static ProjectileServerObjectInitData def; return def; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerObject"; }
  static constexpr auto GetNameHash() { return 0x0D66E014; }
  static ProjectileServerObject & GetDefault() { static ProjectileServerObject def; return def; }
};

template <>
struct StormReflFuncInfo<ProjectileServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct ProjectileServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileServerObject::type_info<0>
  {
    using type = ::ProjectileServerObjectInitData;
  };

  template <>
  struct ProjectileServerObject::type_info<1>
  {
    using type = ::ProjectileServerObject;
  };

}

