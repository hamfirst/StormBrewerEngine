#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementTextureSlice.refl.h"


template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementTextureSliceInitData"; }
  static constexpr auto GetNameHash() { return 0xD7A2154A; }
  static UIElementTextureSliceInitData & GetDefault() { static UIElementTextureSliceInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SpriteFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB83D12F6; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SpriteFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<0, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SpriteFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SpriteFile; }
  void SetDefault() { self.m_SpriteFile = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SpriteFile; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<1>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SliceHorizontally"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1F0734C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SliceHorizontally; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<1, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SliceHorizontally; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SliceHorizontally; }
  void SetDefault() { self.m_SliceHorizontally = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SliceHorizontally; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<2>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SliceVertically"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7E122AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SliceVertically; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<2, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SliceVertically; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SliceVertically; }
  void SetDefault() { self.m_SliceVertically = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SliceVertically; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<3, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<4, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<5, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<6, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartCutX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x491CC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartCutX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<7, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartCutX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartCutX; }
  void SetDefault() { self.m_StartCutX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartCutX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<8>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartCutY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E1BF091; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartCutY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<8, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartCutY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartCutY; }
  void SetDefault() { self.m_StartCutY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartCutY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<9>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndCutX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A244E12; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndCutX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<9, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndCutX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndCutX; }
  void SetDefault() { self.m_EndCutX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndCutX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<10>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndCutY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D237E84; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndCutY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<10, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndCutY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndCutY; }
  void SetDefault() { self.m_EndCutY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndCutY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementTextureSliceData"; }
  static constexpr auto GetNameHash() { return 0x11A3711C; }
  static UIElementTextureSliceData & GetDefault() { static UIElementTextureSliceData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<0, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<1, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<2, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<3, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Angle"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DB7D569; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_Angle; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<4, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Angle; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Angle; }
  void SetDefault() { self.m_Angle = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_Angle; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Enabled"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC50BCE51; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<5, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Enabled; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Enabled; }
  void SetDefault() { self.m_Enabled = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_Enabled; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<6, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<7, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<8, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<9, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceData>::field_data<10, Self> : public StormReflTypeInfo<UIElementTextureSliceData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementTextureSliceData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementTextureSlice
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementTextureSlice::type_info<0>
  {
    using type = ::UIElementTextureSliceInitData;
  };

  template <>
  struct UIElementTextureSlice::type_info<1>
  {
    using type = ::UIElementTextureSliceData;
  };

}

