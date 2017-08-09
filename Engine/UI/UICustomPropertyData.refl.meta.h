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

namespace StormReflFileInfo
{
  struct UICustomPropertyData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UICustomPropertyData::type_info<0>
  {
    using type = ::UICustomProperty;
  };

}

