#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameSimulation.refl.h"


template <>
struct StormReflTypeInfo<GameInitSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInitSettings"; }
  static constexpr auto GetNameHash() { return 0xBAC6DD28; }
  static GameInitSettings & GetDefault() { static GameInitSettings def; return def; }
};

template <>
struct StormReflTypeInfo<ClientLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientLocalData"; }
  static constexpr auto GetNameHash() { return 0x56368E1B; }
  static ClientLocalData & GetDefault() { static ClientLocalData def; return def; }
};

template <>
struct StormReflTypeInfo<ClientLocalData>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 0, kMaxPlayers>; // NetRangedNumber<int, 0, 10>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 10>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0x68ADA9AD; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientLocalData::m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ClientLocalData>::field_data<0, Self> : public StormReflTypeInfo<ClientLocalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxPlayers>> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxPlayers>>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ClientLocalData>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ClientInput>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientInput"; }
  static constexpr auto GetNameHash() { return 0x13CC217D; }
  static ClientInput & GetDefault() { static ClientInput def; return def; }
};

template <>
struct StormReflTypeInfo<ClientAuthData>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientAuthData"; }
  static constexpr auto GetNameHash() { return 0xC020CF54; }
  static ClientAuthData & GetDefault() { static ClientAuthData def; return def; }
};

template <>
struct StormReflTypeInfo<ClientAuthData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientAuthData::m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<ClientAuthData>::field_data<0, Self> : public StormReflTypeInfo<ClientAuthData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<ClientAuthData>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<ClientAuthData>::field_data_static<1>
{
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientAuthData::m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<ClientAuthData>::field_data<1, Self> : public StormReflTypeInfo<ClientAuthData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientInput> & Get() { return self.m_Input; }
  std::add_const_t<std::remove_reference_t<ClientInput>> & Get() const { return self.m_Input; }
  void SetDefault() { self.m_Input = StormReflTypeInfo<ClientAuthData>::GetDefault().m_Input; }
};

template <>
struct StormReflTypeInfo<GamePlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GamePlayer"; }
  static constexpr auto GetNameHash() { return 0x68E3E990; }
  static GamePlayer & GetDefault() { static GamePlayer def; return def; }
};

template <>
struct StormReflTypeInfo<GamePlayer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayer>::field_data<0, Self> : public StormReflTypeInfo<GamePlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GamePlayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GamePlayer>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, 0, kMaxTeams - 1>; // NetRangedNumber<int, 0, 1>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 1>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x98C808CD; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayer>::field_data<1, Self> : public StormReflTypeInfo<GamePlayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GamePlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameSimulation>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameSimulation"; }
  static constexpr auto GetNameHash() { return 0xD6D95D6C; }
  static GameSimulation & GetDefault() { static GameSimulation def; return def; }
};

template <>
struct StormReflTypeInfo<GameSimulation>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_FrameCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BC914D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameSimulation::m_FrameCount; }
};

template <typename Self>
struct StormReflTypeInfo<GameSimulation>::field_data<0, Self> : public StormReflTypeInfo<GameSimulation>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_FrameCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_FrameCount; }
  void SetDefault() { self.m_FrameCount = StormReflTypeInfo<GameSimulation>::GetDefault().m_FrameCount; }
};

template <>
struct StormReflTypeInfo<GameSimulation>::field_data_static<1>
{
  using member_type = NetSparseList<GamePlayer, kMaxPlayers>; // NetSparseList<GamePlayer, 10>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GamePlayer, 10>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0xBD1AB283; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameSimulation::m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameSimulation>::field_data<1, Self> : public StormReflTypeInfo<GameSimulation>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GamePlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GamePlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameSimulation>::GetDefault().m_Players; }
};

namespace StormReflFileInfo
{
  struct GameSimulation
  {
    static const int types_n = 6;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameSimulation::type_info<0>
  {
    using type = ::GameInitSettings;
  };

  template <>
  struct GameSimulation::type_info<1>
  {
    using type = ::ClientLocalData;
  };

  template <>
  struct GameSimulation::type_info<2>
  {
    using type = ::ClientInput;
  };

  template <>
  struct GameSimulation::type_info<3>
  {
    using type = ::ClientAuthData;
  };

  template <>
  struct GameSimulation::type_info<4>
  {
    using type = ::GamePlayer;
  };

  template <>
  struct GameSimulation::type_info<5>
  {
    using type = ::GameSimulation;
  };

}

