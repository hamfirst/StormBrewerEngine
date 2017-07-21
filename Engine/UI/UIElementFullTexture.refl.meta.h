#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementFullTexture.refl.h"


template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementFullTextureInitData"; }
  static constexpr auto GetNameHash() { return 0x79CAB921; }
  static UIElementFullTextureInitData & GetDefault() { static UIElementFullTextureInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_TextureFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x300D4BA3; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureInitData::m_TextureFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureInitData>::field_data<0, Self> : public StormReflTypeInfo<UIElementFullTextureInitData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_TextureFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_TextureFile; }
  void SetDefault() { self.m_TextureFile = StormReflTypeInfo<UIElementFullTextureInitData>::GetDefault().m_TextureFile; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementFullTextureData"; }
  static constexpr auto GetNameHash() { return 0x1DC7E1C5; }
  static UIElementFullTextureData & GetDefault() { static UIElementFullTextureData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_CenterX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1E0357A4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_CenterX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<0, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_CenterX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_CenterX; }
  void SetDefault() { self.m_CenterX = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_CenterX; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_CenterY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x69046732; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_CenterY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<1, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_CenterY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_CenterY; }
  void SetDefault() { self.m_CenterY = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_CenterY; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10B4609F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ScaleX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<2, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleX; }
  void SetDefault() { self.m_ScaleX = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ScaleX; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x67B35009; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ScaleY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<3, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleY; }
  void SetDefault() { self.m_ScaleY = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ScaleY; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DB7D569; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_Angle; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<4, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Angle; }
  void SetDefault() { self.m_Angle = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_Angle; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Enabled"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC50BCE51; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<5, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Enabled; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Enabled; }
  void SetDefault() { self.m_Enabled = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_Enabled; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<6, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<7, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<8, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<9, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<10, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementFullTexture
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementFullTexture::type_info<0>
  {
    using type = ::UIElementFullTextureInitData;
  };

  template <>
  struct UIElementFullTexture::type_info<1>
  {
    using type = ::UIElementFullTextureData;
  };

}

