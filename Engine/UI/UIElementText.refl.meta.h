#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementText.refl.h"


template <>
struct StormReflTypeInfo<UIElementTextInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementTextInitData"; }
  static constexpr auto GetNameHash() { return 0x797CBA08; }
  static UIElementTextInitData & GetDefault() { static UIElementTextInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>
{
  using MyBase = void;
  static constexpr int fields_n = 20;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementTextData"; }
  static constexpr auto GetNameHash() { return 0xF2808E39; }
  static UIElementTextData & GetDefault() { static UIElementTextData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Text"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x051632D8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Text; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<0, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Text; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Text; }
  void SetDefault() { self.m_Text = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Text; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<1, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<2, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextMode"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9F050945; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextMode; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<3, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextMode; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextMode; }
  void SetDefault() { self.m_TextMode = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextMode; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_FontId"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA57EB01; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_FontId; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<4, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_FontId; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_FontId; }
  void SetDefault() { self.m_FontId = StormReflTypeInfo<UIElementTextData>::GetDefault().m_FontId; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Centered"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x239066D4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Centered; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<5, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Centered; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Centered; }
  void SetDefault() { self.m_Centered = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Centered; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EnableTextBounds"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x397C84F7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_EnableTextBounds; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<6, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EnableTextBounds; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EnableTextBounds; }
  void SetDefault() { self.m_EnableTextBounds = StormReflTypeInfo<UIElementTextData>::GetDefault().m_EnableTextBounds; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F948DF6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsStartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<7, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartX; }
  void SetDefault() { self.m_TextBoundsStartX = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsStartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsStartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2893BD60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsStartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<8, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsStartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsStartY; }
  void SetDefault() { self.m_TextBoundsStartY = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsStartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC67E8723; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsEndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<9, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndX; }
  void SetDefault() { self.m_TextBoundsEndX = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsEndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TextBoundsEndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB179B7B5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_TextBoundsEndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<10, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TextBoundsEndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TextBoundsEndY; }
  void SetDefault() { self.m_TextBoundsEndY = StormReflTypeInfo<UIElementTextData>::GetDefault().m_TextBoundsEndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<11>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrimaryColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3223A5A2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PrimaryColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<11, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrimaryColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrimaryColorR; }
  void SetDefault() { self.m_PrimaryColorR = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PrimaryColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<12>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrimaryColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5FFE4149; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PrimaryColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<12, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrimaryColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrimaryColorG; }
  void SetDefault() { self.m_PrimaryColorG = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PrimaryColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<13>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrimaryColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2F94B5C6; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PrimaryColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<13, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrimaryColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrimaryColorB; }
  void SetDefault() { self.m_PrimaryColorB = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PrimaryColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<14>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrimaryColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB69DE47C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_PrimaryColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<14, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<14>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrimaryColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrimaryColorA; }
  void SetDefault() { self.m_PrimaryColorA = StormReflTypeInfo<UIElementTextData>::GetDefault().m_PrimaryColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<15>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAEE8788B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 15; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<15, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<15>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorR; }
  void SetDefault() { self.m_SecondaryColorR = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<16>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3359C60; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 16; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<16, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<16>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorG; }
  void SetDefault() { self.m_SecondaryColorG = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<17>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB35F68EF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 17; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<17, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<17>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorB; }
  void SetDefault() { self.m_SecondaryColorB = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<18>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SecondaryColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2A563955; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 18; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_SecondaryColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<18, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<18>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SecondaryColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SecondaryColorA; }
  void SetDefault() { self.m_SecondaryColorA = StormReflTypeInfo<UIElementTextData>::GetDefault().m_SecondaryColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextData>::field_data_static<19>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 19; }
  static constexpr auto GetMemberPtr() { return &UIElementTextData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextData>::field_data<19, Self> : public StormReflTypeInfo<UIElementTextData>::field_data_static<19>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementTextData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementText
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementText::type_info<0>
  {
    using type = ::UIElementTextInitData;
  };

  template <>
  struct UIElementText::type_info<1>
  {
    using type = ::UIElementTextData;
  };

}

