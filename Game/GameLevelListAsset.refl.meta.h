#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameLevelListAsset.refl.h"


template <>
struct StormReflTypeInfo<GameLevelListAsset>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLevelListAsset"; }
  static constexpr auto GetNameHash() { return 0x6F8BA414; }
  static GameLevelListAsset & GetDefault() { static GameLevelListAsset def; return def; }
};

template <>
struct StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_Levels"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD21533D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLevelListAsset::m_Levels; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelListAsset>::field_data<0, Self> : public StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_Levels; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_Levels; }
  void SetDefault() { self.m_Levels = StormReflTypeInfo<GameLevelListAsset>::GetDefault().m_Levels; }
};

namespace StormReflFileInfo
{
  struct GameLevelListAsset
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameLevelListAsset::type_info<0>
  {
    using type = ::GameLevelListAsset;
  };

}

