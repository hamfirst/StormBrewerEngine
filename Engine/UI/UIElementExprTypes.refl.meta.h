#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementExprTypes.refl.h"


template <>
struct StormReflTypeInfo<UIGlobalBlock>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIGlobalBlock"; }
  static constexpr auto GetNameHash() { return 0x45A889EB; }
  static UIGlobalBlock & GetDefault() { static UIGlobalBlock def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIGlobalBlock *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIGlobalBlock *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIGlobalBlock *>(ptr);
    if(typeid(UIGlobalBlock).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIGlobalBlock *>(ptr);
    if(typeid(UIGlobalBlock).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIGlobalBlock>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Time"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51090D5A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIGlobalBlock::m_Time; }
};

template <typename Self>
struct StormReflTypeInfo<UIGlobalBlock>::field_data<0, Self> : public StormReflTypeInfo<UIGlobalBlock>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Time; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Time; }
  void SetDefault() { self.m_Time = StormReflTypeInfo<UIGlobalBlock>::GetDefault().m_Time; }
};

template <>
struct StormReflTypeInfo<UIGlobalBlock>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScreenWidth"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF51FE85B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIGlobalBlock::m_ScreenWidth; }
};

template <typename Self>
struct StormReflTypeInfo<UIGlobalBlock>::field_data<1, Self> : public StormReflTypeInfo<UIGlobalBlock>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScreenWidth; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScreenWidth; }
  void SetDefault() { self.m_ScreenWidth = StormReflTypeInfo<UIGlobalBlock>::GetDefault().m_ScreenWidth; }
};

template <>
struct StormReflTypeInfo<UIGlobalBlock>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScreenHeight"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA25C5587; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIGlobalBlock::m_ScreenHeight; }
};

template <typename Self>
struct StormReflTypeInfo<UIGlobalBlock>::field_data<2, Self> : public StormReflTypeInfo<UIGlobalBlock>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScreenHeight; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScreenHeight; }
  void SetDefault() { self.m_ScreenHeight = StormReflTypeInfo<UIGlobalBlock>::GetDefault().m_ScreenHeight; }
};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UIAutoCalculatedBlock"; }
  static constexpr auto GetNameHash() { return 0x4167197E; }
  static UIAutoCalculatedBlock & GetDefault() { static UIAutoCalculatedBlock def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIAutoCalculatedBlock *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIAutoCalculatedBlock *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIAutoCalculatedBlock *>(ptr);
    if(typeid(UIAutoCalculatedBlock).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIAutoCalculatedBlock *>(ptr);
    if(typeid(UIAutoCalculatedBlock).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TimeAlive"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFD422D7A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UIAutoCalculatedBlock::m_TimeAlive; }
};

template <typename Self>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data<0, Self> : public StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TimeAlive; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TimeAlive; }
  void SetDefault() { self.m_TimeAlive = StormReflTypeInfo<UIAutoCalculatedBlock>::GetDefault().m_TimeAlive; }
};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Width"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x012CD54F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UIAutoCalculatedBlock::m_Width; }
};

template <typename Self>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data<1, Self> : public StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Width; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Width; }
  void SetDefault() { self.m_Width = StormReflTypeInfo<UIAutoCalculatedBlock>::GetDefault().m_Width; }
};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Height"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB872B2C7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UIAutoCalculatedBlock::m_Height; }
};

template <typename Self>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data<2, Self> : public StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Height; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Height; }
  void SetDefault() { self.m_Height = StormReflTypeInfo<UIAutoCalculatedBlock>::GetDefault().m_Height; }
};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScreenX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x04463F53; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UIAutoCalculatedBlock::m_ScreenX; }
};

template <typename Self>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data<3, Self> : public StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScreenX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScreenX; }
  void SetDefault() { self.m_ScreenX = StormReflTypeInfo<UIAutoCalculatedBlock>::GetDefault().m_ScreenX; }
};

template <>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScreenY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x73410FC5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UIAutoCalculatedBlock::m_ScreenY; }
};

template <typename Self>
struct StormReflTypeInfo<UIAutoCalculatedBlock>::field_data<4, Self> : public StormReflTypeInfo<UIAutoCalculatedBlock>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScreenY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScreenY; }
  void SetDefault() { self.m_ScreenY = StormReflTypeInfo<UIAutoCalculatedBlock>::GetDefault().m_ScreenY; }
};

namespace StormReflFileInfo
{
  struct UIElementExprTypes
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementExprTypes::type_info<0>
  {
    using type = ::UIGlobalBlock;
  };

  template <>
  struct UIElementExprTypes::type_info<1>
  {
    using type = ::UIAutoCalculatedBlock;
  };

}

