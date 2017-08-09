#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementContainer.refl.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementContainerInitData>
{
  using MyBase = UIElementDataBase;
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
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementContainerData"; }
  static constexpr auto GetNameHash() { return 0x29015F17; }
  static UIElementContainerData & GetDefault() { static UIElementContainerData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementContainerData::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementContainerData>::field_data<0, Self> : public StormReflTypeInfo<UIElementContainerData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementContainerData>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementContainerData::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementContainerData>::field_data<1, Self> : public StormReflTypeInfo<UIElementContainerData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementContainerData>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementContainerData::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementContainerData>::field_data<2, Self> : public StormReflTypeInfo<UIElementContainerData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementContainerData>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementContainerData::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementContainerData>::field_data<3, Self> : public StormReflTypeInfo<UIElementContainerData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementContainerData>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<UIElementContainerData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementContainerData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementContainerData>::field_data<4, Self> : public StormReflTypeInfo<UIElementContainerData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementContainerData>::GetDefault().m_Active; }
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

