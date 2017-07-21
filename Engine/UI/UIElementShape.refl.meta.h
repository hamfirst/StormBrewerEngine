#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementShape.refl.h"


template <>
struct StormReflTypeInfo<UIElementShapeInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementShapeInitData"; }
  static constexpr auto GetNameHash() { return 0x2F95427F; }
  static UIElementShapeInitData & GetDefault() { static UIElementShapeInitData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIElementShapeData"; }
  static constexpr auto GetNameHash() { return 0x67E68BE1; }
  static UIElementShapeData & GetDefault() { static UIElementShapeData def; return def; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87158667; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_StartX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<0, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartX; }
  void SetDefault() { self.m_StartX = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_StartX; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_StartY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF012B6F1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_StartY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<1, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_StartY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_StartY; }
  void SetDefault() { self.m_StartY = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_StartY; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3549DC7D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_EndX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<2, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndX; }
  void SetDefault() { self.m_EndX = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_EndX; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EndY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x424EECEB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_EndY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<3, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EndY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EndY; }
  void SetDefault() { self.m_EndY = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_EndY; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Enabled"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC50BCE51; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_Enabled; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<4, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Enabled; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Enabled; }
  void SetDefault() { self.m_Enabled = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_Enabled; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Shape"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50066FB8; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_Shape; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<5, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Shape; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Shape; }
  void SetDefault() { self.m_Shape = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_Shape; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EdgeWidth"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5AD2EAB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_EdgeWidth; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<6, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EdgeWidth; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EdgeWidth; }
  void SetDefault() { self.m_EdgeWidth = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_EdgeWidth; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<7, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<8, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<9, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<10, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<UIElementShapeData>::field_data_static<11>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Active"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0621ABCA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UIElementShapeData::m_Active; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementShapeData>::field_data<11, Self> : public StormReflTypeInfo<UIElementShapeData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Active; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Active; }
  void SetDefault() { self.m_Active = StormReflTypeInfo<UIElementShapeData>::GetDefault().m_Active; }
};

namespace StormReflFileInfo
{
  struct UIElementShape
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementShape::type_info<0>
  {
    using type = ::UIElementShapeInitData;
  };

  template <>
  struct UIElementShape::type_info<1>
  {
    using type = ::UIElementShapeData;
  };

}

