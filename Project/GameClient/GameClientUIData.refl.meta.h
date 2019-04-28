#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameClientUIData.refl.h"


template <>
struct StormReflTypeInfo<GameClientUIData>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameClientUIData"; }
  static constexpr auto GetNameHash() { return 0x3254A1CC; }
  static constexpr bool HasDefault() { return true; }
  static GameClientUIData & GetDefault() { static GameClientUIData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameClientUIData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientUIData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameClientUIData *>(ptr);
    if(typeid(GameClientUIData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameClientUIData *>(ptr);
    if(typeid(GameClientUIData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "timer_pre_round"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x574BCAFF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer_pre_round; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer_pre_round; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer_pre_round; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<0, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.timer_pre_round; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.timer_pre_round; }
  void SetDefault() { self.timer_pre_round = StormReflTypeInfo<GameClientUIData>::GetDefault().timer_pre_round; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "timer_scale"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x91E2DEB2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer_scale; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer_scale; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer_scale; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<1, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.timer_scale; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.timer_scale; }
  void SetDefault() { self.timer_scale = StormReflTypeInfo<GameClientUIData>::GetDefault().timer_scale; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "timer"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6AD0DE1A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::timer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->timer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->timer; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<2, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.timer; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.timer; }
  void SetDefault() { self.timer = StormReflTypeInfo<GameClientUIData>::GetDefault().timer; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "tutorial_hint"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4B00841E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<3, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.tutorial_hint; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.tutorial_hint; }
  void SetDefault() { self.tutorial_hint = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "tutorial_hint_x"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1CB0998C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint_x; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint_x; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint_x; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<4, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.tutorial_hint_x; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.tutorial_hint_x; }
  void SetDefault() { self.tutorial_hint_x = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint_x; }
};

template <>
struct StormReflTypeInfo<GameClientUIData>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "tutorial_hint_y"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6BB7A91A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameClientUIData::tutorial_hint_y; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameClientUIData *>(obj); return &ptr->tutorial_hint_y; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameClientUIData *>(obj); return &ptr->tutorial_hint_y; }
};

template <typename Self>
struct StormReflTypeInfo<GameClientUIData>::field_data<5, Self> : public StormReflTypeInfo<GameClientUIData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.tutorial_hint_y; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.tutorial_hint_y; }
  void SetDefault() { self.tutorial_hint_y = StormReflTypeInfo<GameClientUIData>::GetDefault().tutorial_hint_y; }
};

namespace StormReflFileInfo
{
  struct GameClientUIData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameClientUIData::type_info<0>
  {
    using type = ::GameClientUIData;
  };

}

