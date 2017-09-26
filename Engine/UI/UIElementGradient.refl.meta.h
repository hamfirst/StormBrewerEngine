#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementGradient.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementGradientInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementGradientInitData"; }
  static constexpr auto GetNameHash() { return 0x6549A493; }
  static UIElementGradientInitData & GetDefault() { static UIElementGradientInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>
{
  using MyBase = UIElementDataStartEnd;
  static constexpr int fields_n = 17 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementGradientData"; }
  static constexpr auto GetNameHash() { return 0x1438BA0B; }
  static UIElementGradientData & GetDefault() { static UIElementGradientData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DB7D569; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_Angle; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<0 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Angle; }
  void SetDefault() { self.m_Angle = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_Angle; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BLColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAD2C4D8; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BLColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<1 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BLColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BLColorR; }
  void SetDefault() { self.m_BLColorR = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BLColorR; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<2 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BLColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD70F2033; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BLColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<2 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<2 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BLColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BLColorG; }
  void SetDefault() { self.m_BLColorG = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BLColorG; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<3 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BLColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA765D4BC; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BLColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<3 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<3 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BLColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BLColorB; }
  void SetDefault() { self.m_BLColorB = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BLColorB; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<4 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BLColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E6C8506; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BLColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<4 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<4 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BLColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BLColorA; }
  void SetDefault() { self.m_BLColorA = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BLColorA; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<5 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BRColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D33234B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BRColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<5 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<5 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BRColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BRColorR; }
  void SetDefault() { self.m_BRColorR = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BRColorR; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<6 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BRColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE0EEC7A0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BRColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<6 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<6 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BRColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BRColorG; }
  void SetDefault() { self.m_BRColorG = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BRColorG; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<7 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BRColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9084332F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BRColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<7 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<7 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BRColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BRColorB; }
  void SetDefault() { self.m_BRColorB = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BRColorB; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<8 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_BRColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x098D6295; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_BRColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<8 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<8 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_BRColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_BRColorA; }
  void SetDefault() { self.m_BRColorA = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_BRColorA; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<9 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TLColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0006FC74; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TLColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<9 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<9 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TLColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TLColorR; }
  void SetDefault() { self.m_TLColorR = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TLColorR; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<10 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TLColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6DDB189F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TLColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<10 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<10 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TLColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TLColorG; }
  void SetDefault() { self.m_TLColorG = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TLColorG; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<11 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TLColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB1EC10; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TLColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<11 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<11 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TLColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TLColorB; }
  void SetDefault() { self.m_TLColorB = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TLColorB; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<12 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TLColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x84B8BDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TLColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<12 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<12 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TLColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TLColorA; }
  void SetDefault() { self.m_TLColorA = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TLColorA; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<13 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TRColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x37E71BE7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 13 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TRColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<13 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<13 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TRColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TRColorR; }
  void SetDefault() { self.m_TRColorR = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TRColorR; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<14 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TRColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5A3AFF0C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 14 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TRColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<14 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<14 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TRColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TRColorG; }
  void SetDefault() { self.m_TRColorG = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TRColorG; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<15 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TRColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2A500B83; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 15 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TRColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<15 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<15 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TRColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TRColorB; }
  void SetDefault() { self.m_TRColorB = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TRColorB; }
};

template <>
struct StormReflTypeInfo<UIElementGradientData>::field_data_static<16 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TRColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3595A39; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 16 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementGradientData::m_TRColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementGradientData>::field_data<16 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n, Self> : public StormReflTypeInfo<UIElementGradientData>::field_data_static<16 + StormReflTypeInfo<UIElementDataStartEnd>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TRColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TRColorA; }
  void SetDefault() { self.m_TRColorA = StormReflTypeInfo<UIElementGradientData>::GetDefault().m_TRColorA; }
};

namespace StormReflFileInfo
{
  struct UIElementGradient
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementGradient::type_info<0>
  {
    using type = ::UIElementGradientInitData;
  };

  template <>
  struct UIElementGradient::type_info<1>
  {
    using type = ::UIElementGradientData;
  };

}

