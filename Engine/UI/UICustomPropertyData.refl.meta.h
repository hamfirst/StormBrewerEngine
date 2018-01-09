#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UICustomPropertyData.refl.h"


template <>
struct StormReflEnumInfo<UICustomPropertyDataType>
{
  static constexpr int elems_n = 2;
  static constexpr auto GetName() { return "UICustomPropertyDataType"; }
  static constexpr auto GetNameHash() { return 0x51D3AC54; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<UICustomPropertyDataType>::elems<0>
{
  static constexpr auto GetName() { return "kNumber"; }
  static constexpr auto GetNameHash() { return 0x34237CA0; }
  static constexpr auto GetValue() { return UICustomPropertyDataType::kNumber; }
};

template <>
struct StormReflEnumInfo<UICustomPropertyDataType>::elems<1>
{
  static constexpr auto GetName() { return "kString"; }
  static constexpr auto GetNameHash() { return 0x3C0DD15D; }
  static constexpr auto GetValue() { return UICustomPropertyDataType::kString; }
};

template <>
struct StormReflTypeInfo<UICustomProperty>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UICustomProperty"; }
  static constexpr auto GetNameHash() { return 0xFF78C512; }
  static UICustomProperty & GetDefault() { static UICustomProperty def; return def; }
};

template <>
struct StormReflTypeInfo<UICustomProperty>::field_data_static<0>
{
  using member_type = UICustomPropertyDataType; // UICustomPropertyDataType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "UICustomPropertyDataType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x51D3AC54; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UICustomProperty::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<UICustomProperty>::field_data<0, Self> : public StormReflTypeInfo<UICustomProperty>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UICustomPropertyDataType> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<UICustomPropertyDataType>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<UICustomProperty>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<UICustomProperty>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UICustomProperty::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<UICustomProperty>::field_data<1, Self> : public StormReflTypeInfo<UICustomProperty>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<UICustomProperty>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementDataBase"; }
  static constexpr auto GetNameHash() { return 0xC8F14E8A; }
  static UIElementDataBase & GetDefault() { static UIElementDataBase def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Enabled"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC50BCE51; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<0, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Enabled; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Enabled; }
  void SetDefault() { self.m_Enabled = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_Enabled; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<1, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_Active; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<2, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<3, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<4, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<5, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<UIElementDataBase>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Layer"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x69EDB17A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementDataBase::m_Layer; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataBase>::field_data<6, Self> : public StormReflTypeInfo<UIElementDataBase>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Layer; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Layer; }
  void SetDefault() { self.m_Layer = StormReflTypeInfo<UIElementDataBase>::GetDefault().m_Layer; }
};

template <>
struct StormReflTypeInfo<UIElementDataFrameCenter>
{
  using MyBase = UIElementDataBase;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementDataFrameCenter"; }
  static constexpr auto GetNameHash() { return 0x4076AA02; }
  static UIElementDataFrameCenter & GetDefault() { static UIElementDataFrameCenter def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementDataFrameCenter>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataFrameCenter::m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataFrameCenter>::field_data<0 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataFrameCenter>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<UIElementDataFrameCenter>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<UIElementDataFrameCenter>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataFrameCenter::m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataFrameCenter>::field_data<1 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataFrameCenter>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<UIElementDataFrameCenter>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<UIElementDataStartEnd>
{
  using MyBase = UIElementDataBase;
  static constexpr int fields_n = 4 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementDataStartEnd"; }
  static constexpr auto GetNameHash() { return 0x7B3842A1; }
  static UIElementDataStartEnd & GetDefault() { static UIElementDataStartEnd def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataStartEnd::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data<0 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementDataStartEnd>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataStartEnd::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data<1 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementDataStartEnd>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<2 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataStartEnd::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data<2 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<2 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementDataStartEnd>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<3 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementDataStartEnd::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementDataStartEnd>::field_data<3 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementDataStartEnd>::field_data_static<3 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementDataStartEnd>::GetDefault().m_EndY; }
};

namespace StormReflFileInfo
{
  struct UICustomPropertyData
  {
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UICustomPropertyData::type_info<0>
  {
    using type = ::UICustomProperty;
  };

  template <>
  struct UICustomPropertyData::type_info<1>
  {
    using type = ::UIElementDataBase;
  };

  template <>
  struct UICustomPropertyData::type_info<2>
  {
    using type = ::UIElementDataFrameCenter;
  };

  template <>
  struct UICustomPropertyData::type_info<3>
  {
    using type = ::UIElementDataStartEnd;
  };

}

