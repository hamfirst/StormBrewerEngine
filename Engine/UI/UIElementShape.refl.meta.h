#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementShape.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementShapeInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementShapeInitData"; }
  static constexpr auto GetNameHash() { return 0x2F95427F; }
  static UIElementShapeInitData & GetDefault() { static UIElementShapeInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>
{
  using MyBase = UIElementDataStartEnd;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementShapeData"; }
  static constexpr auto GetNameHash() { return 0x67E68BE1; }
  static UIElementShapeData & GetDefault() { static UIElementShapeData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Shape"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50066FB8; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_Shape; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Shape; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Shape; }
  void SetDefault() { self.m_Shape = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_Shape; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EdgeWidth"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5AD2EAB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_EdgeWidth; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EdgeWidth; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EdgeWidth; }
  void SetDefault() { self.m_EdgeWidth = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_EdgeWidth; }
};

namespace StormReflFileInfo
{
  struct UIElementShape
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementShape::type_info<0>
  {
    using type = ::UIElementShapeInitData;
  };

  template <>
  struct UIElementShape::type_info<1>
  {
    using type = ::UIElementShapeData;
  };

}

