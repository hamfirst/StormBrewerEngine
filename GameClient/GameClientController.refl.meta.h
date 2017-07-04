#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameClientController.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"


template <>
struct StormReflTypeInfo<GameClientController>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GameClientController"; }
  static constexpr auto GetNameHash() { return 0xAABB1F25; }
};

template <>
struct StormReflFuncInfo<GameClientController>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 1 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>
{
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "HandlePlaceholderEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB51A771F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n; }
  static constexpr auto GetFunctionPtr() { return &GameClientController::HandlePlaceholderEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameClientController>::func_data_static<0 + StormReflFuncInfo<StormRelfEmptyBase>::funcs_n>::param_info<0>
{
  using param_type = const PlaceholderGlobalEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderGlobalEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xED8E2F25; }
};

namespace StormReflFileInfo
{
  struct GameClientController
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameClientController::type_info<0>
  {
    using type = ::GameClientController;
  };

}

