#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementSpriteFrame.refl.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>
{
  using MyBase = UIElementDataBase;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementSpriteFrameInitData"; }
  static constexpr auto GetNameHash() { return 0xCE39C546; }
  static UIElementSpriteFrameInitData & GetDefault() { static UIElementSpriteFrameInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SpriteFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB83D12F6; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameInitData::m_SpriteFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data<0 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SpriteFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SpriteFile; }
  void SetDefault() { self.m_SpriteFile = StormReflTypeInfo<UIElementSpriteFrameInitData>::GetDefault().m_SpriteFile; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::annotations<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::annotations<0 + StormReflTypeInfo<UIElementDataBase>::fields_n>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: tilesheet"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x03667DA4; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Animation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5172A5C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameInitData::m_Animation; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data<1 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<1 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Animation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Animation; }
  void SetDefault() { self.m_Animation = StormReflTypeInfo<UIElementSpriteFrameInitData>::GetDefault().m_Animation; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<2 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AnimationFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16C1E1E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameInitData::m_AnimationFrame; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data<2 + StormReflTypeInfo<UIElementDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<2 + StormReflTypeInfo<UIElementDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AnimationFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AnimationFrame; }
  void SetDefault() { self.m_AnimationFrame = StormReflTypeInfo<UIElementSpriteFrameInitData>::GetDefault().m_AnimationFrame; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>
{
  using MyBase = void;
  static constexpr int fields_n = 13;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementSpriteFrameData"; }
  static constexpr auto GetNameHash() { return 0xFFD2E695; }
  static UIElementSpriteFrameData & GetDefault() { static UIElementSpriteFrameData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_CenterX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1E0357A4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_CenterX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<0, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_CenterX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_CenterX; }
  void SetDefault() { self.m_CenterX = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_CenterX; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_CenterY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x69046732; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_CenterY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<1, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_CenterY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_CenterY; }
  void SetDefault() { self.m_CenterY = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_CenterY; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_WidthScale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCEE20276; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_WidthScale; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<2, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_WidthScale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_WidthScale; }
  void SetDefault() { self.m_WidthScale = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_WidthScale; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_HeightScale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAA020D4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_HeightScale; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<3, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_HeightScale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_HeightScale; }
  void SetDefault() { self.m_HeightScale = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_HeightScale; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DB7D569; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Angle; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<4, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Angle; }
  void SetDefault() { self.m_Angle = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Angle; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Enabled"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC50BCE51; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<5, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Enabled; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Enabled; }
  void SetDefault() { self.m_Enabled = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Enabled; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Animation"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5172A5C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Animation; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<6, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Animation; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Animation; }
  void SetDefault() { self.m_Animation = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Animation; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_FrameAdvance"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0324C7A0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_FrameAdvance; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<7, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_FrameAdvance; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_FrameAdvance; }
  void SetDefault() { self.m_FrameAdvance = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_FrameAdvance; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<8, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<9, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<10, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<11>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<11, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<12>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<12, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementSpriteFrame
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementSpriteFrame::type_info<0>
  {
    using type = ::UIElementSpriteFrameInitData;
  };

  template <>
  struct UIElementSpriteFrame::type_info<1>
  {
    using type = ::UIElementSpriteFrameData;
  };

}

