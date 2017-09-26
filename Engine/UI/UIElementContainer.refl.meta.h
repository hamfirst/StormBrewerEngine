#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementContainer.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementContainerInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementContainerInitData"; }
  static constexpr auto GetNameHash() { return 0x86439F54; }
  static UIElementContainerInitData & GetDefault() { static UIElementContainerInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>
{
  using MyBase = UIElementDataStartEnd;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementContainerData"; }
  static constexpr auto GetNameHash() { return 0x29015F17; }
  static UIElementContainerData & GetDefault() { static UIElementContainerData def; return def; }
};

namespace StormReflFileInfo
{
  struct UIElementContainer
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementContainer::type_info<0>
  {
    using type = ::UIElementContainerInitData;
  };

  template <>
  struct UIElementContainer::type_info<1>
  {
    using type = ::UIElementContainerData;
  };

}

