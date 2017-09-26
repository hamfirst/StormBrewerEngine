#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementTextureSlice.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 11 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextureSliceInitData"; }
  static constexpr auto GetNameHash() { return 0xD7A2154A; }
  static UIElementTextureSliceInitData & GetDefault() { static UIElementTextureSliceInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SpriteFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB83D12F6; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SpriteFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SpriteFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SpriteFile; }
  void SetDefault() { self.m_SpriteFile = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SpriteFile; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SliceHorizontally"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1F0734C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SliceHorizontally; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<1 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SliceHorizontally; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SliceHorizontally; }
  void SetDefault() { self.m_SliceHorizontally = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SliceHorizontally; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<2 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SliceVertically"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7E122AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_SliceVertically; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<2 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<2 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SliceVertically; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SliceVertically; }
  void SetDefault() { self.m_SliceVertically = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_SliceVertically; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<3 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<3 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<3 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<4 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<4 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<4 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<5 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<5 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<5 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<6 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<6 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<6 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<7 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartCutX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x491CC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartCutX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<7 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<7 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartCutX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartCutX; }
  void SetDefault() { self.m_StartCutX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartCutX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<8 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_StartCutY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E1BF091; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 8 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_StartCutY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<8 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<8 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_StartCutY; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_StartCutY; }
  void SetDefault() { self.m_StartCutY = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_StartCutY; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<9 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndCutX"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A244E12; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 9 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndCutX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<9 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<9 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_EndCutX; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_EndCutX; }
  void SetDefault() { self.m_EndCutX = StormReflTypeInfo<UIElementTextureSliceInitData>::GetDefault().m_EndCutX; }
};

template <>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<10 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_EndCutY"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D237E84; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 10 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementTextureSliceInitData::m_EndCutY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementTextureSliceInitData>::field_data<10 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementTextureSliceInitData>::field_data_static<10 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
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
  using MyBase = UIElementDataStartEnd;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementTextureSliceData"; }
  static constexpr auto GetNameHash() { return 0x11A3711C; }
  static UIElementTextureSliceData & GetDefault() { static UIElementTextureSliceData def; return def; }
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

