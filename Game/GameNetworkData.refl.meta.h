#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkData.refl.h"


template <>
struct StormReflTypeInfo<GameInitSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInitSettings"; }
  static constexpr auto GetNameHash() { return 0xBAC6DD28; }
  static GameInitSettings & GetDefault() { static GameInitSettings def; return def; }
};

template <>
struct StormReflTypeInfo<GameInitSettings>::field_data_static<0>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_StageIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54FBDE46; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInitSettings::m_StageIndex; }
};

template <typename Self>
struct StormReflTypeInfo<GameInitSettings>::field_data<0, Self> : public StormReflTypeInfo<GameInitSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_StageIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_StageIndex; }
  void SetDefault() { self.m_StageIndex = StormReflTypeInfo<GameInitSettings>::GetDefault().m_StageIndex; }
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
  static constexpr int fields_n = 1;
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
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientAuthData::m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<ClientAuthData>::field_data<0, Self> : public StormReflTypeInfo<ClientAuthData>::field_data_static<0>
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
struct StormReflTypeInfo<GameGlobalData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameGlobalData"; }
  static constexpr auto GetNameHash() { return 0xD1E834F1; }
  static GameGlobalData & GetDefault() { static GameGlobalData def; return def; }
};

template <>
struct StormReflTypeInfo<GameGlobalData>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameGlobalData::m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<GameGlobalData>::field_data<0, Self> : public StormReflTypeInfo<GameGlobalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<GameGlobalData>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<GameGlobalData>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 1>
  static constexpr auto GetName() { return "m_ActiveTurn"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 1>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2933B64C; }
  static constexpr unsigned GetTypeNameHash() { return 0x01BCAC65; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameGlobalData::m_ActiveTurn; }
};

template <typename Self>
struct StormReflTypeInfo<GameGlobalData>::field_data<1, Self> : public StormReflTypeInfo<GameGlobalData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_ActiveTurn; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_ActiveTurn; }
  void SetDefault() { self.m_ActiveTurn = StormReflTypeInfo<GameGlobalData>::GetDefault().m_ActiveTurn; }
};

template <>
struct StormReflTypeInfo<GameGlobalData>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Running"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAD3FCBA; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameGlobalData::m_Running; }
};

template <typename Self>
struct StormReflTypeInfo<GameGlobalData>::field_data<2, Self> : public StormReflTypeInfo<GameGlobalData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Running; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Running; }
  void SetDefault() { self.m_Running = StormReflTypeInfo<GameGlobalData>::GetDefault().m_Running; }
};

template <>
struct StormReflTypeInfo<GameGlobalData>::field_data_static<3>
{
  using member_type = NetRangedNumber<int, 0, kTurnMaxTime>; // NetRangedNumber<int, 0, 3000>
  static constexpr auto GetName() { return "m_TimeExpiration"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 3000>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE045B63; }
  static constexpr unsigned GetTypeNameHash() { return 0x9B03F688; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameGlobalData::m_TimeExpiration; }
};

template <typename Self>
struct StormReflTypeInfo<GameGlobalData>::field_data<3, Self> : public StormReflTypeInfo<GameGlobalData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kTurnMaxTime>> & Get() { return self.m_TimeExpiration; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kTurnMaxTime>>> & Get() const { return self.m_TimeExpiration; }
  void SetDefault() { self.m_TimeExpiration = StormReflTypeInfo<GameGlobalData>::GetDefault().m_TimeExpiration; }
};

template <>
struct StormReflTypeInfo<GameGlobalData>::field_data_static<4>
{
  using member_type = NetSparseList<GamePlayer, kMaxPlayers>; // NetSparseList<GamePlayer, 10>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GamePlayer, 10>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0xBD1AB283; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameGlobalData::m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameGlobalData>::field_data<4, Self> : public StormReflTypeInfo<GameGlobalData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GamePlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GamePlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameGlobalData>::GetDefault().m_Players; }
};

namespace StormReflFileInfo
{
  struct GameNetworkData
  {
    static const int types_n = 6;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameNetworkData::type_info<0>
  {
    using type = ::GameInitSettings;
  };

  template <>
  struct GameNetworkData::type_info<1>
  {
    using type = ::ClientLocalData;
  };

  template <>
  struct GameNetworkData::type_info<2>
  {
    using type = ::ClientInput;
  };

  template <>
  struct GameNetworkData::type_info<3>
  {
    using type = ::ClientAuthData;
  };

  template <>
  struct GameNetworkData::type_info<4>
  {
    using type = ::GamePlayer;
  };

  template <>
  struct GameNetworkData::type_info<5>
  {
    using type = ::GameGlobalData;
  };

}

