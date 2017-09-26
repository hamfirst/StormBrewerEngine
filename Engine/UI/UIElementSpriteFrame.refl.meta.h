#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementSpriteFrame.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
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
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SpriteFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB83D12F6; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameInitData::m_SpriteFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SpriteFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SpriteFile; }
  void SetDefault() { self.m_SpriteFile = StormReflTypeInfo<UIElementSpriteFrameInitData>::GetDefault().m_SpriteFile; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: sprite"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x1563DF3B; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AnimationFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16C1E1E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameInitData::m_AnimationFrame; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameInitData>::field_data_static<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
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
  using MyBase = UIElementDataFrameCenter;
  static constexpr int fields_n = 5 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementSpriteFrameData"; }
  static constexpr auto GetNameHash() { return 0xFFD2E695; }
  static UIElementSpriteFrameData & GetDefault() { static UIElementSpriteFrameData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10B4609F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ScaleX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleX; }
  void SetDefault() { self.m_ScaleX = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ScaleX; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x67B35009; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_ScaleY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleY; }
  void SetDefault() { self.m_ScaleY = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_ScaleY; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DB7D569; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Angle; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<2 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Angle; }
  void SetDefault() { self.m_Angle = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Angle; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Animation"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5172A5C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_Animation; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<3 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Animation; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Animation; }
  void SetDefault() { self.m_Animation = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_Animation; }
};

template <>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_FrameAdvance"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0324C7A0; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementSpriteFrameData::m_FrameAdvance; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementSpriteFrameData>::field_data<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementSpriteFrameData>::field_data_static<4 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_FrameAdvance; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_FrameAdvance; }
  void SetDefault() { self.m_FrameAdvance = StormReflTypeInfo<UIElementSpriteFrameData>::GetDefault().m_FrameAdvance; }
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

