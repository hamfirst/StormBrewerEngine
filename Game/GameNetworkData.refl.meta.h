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
  using member_type = NetRangedNumber<int, 0, kMaxPlayers>; // NetRangedNumber<int, 0, 4>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 4>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xE5BFFC88; }
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
struct StormReflTypeInfo<PackageInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PackageInfo"; }
  static constexpr auto GetNameHash() { return 0xE66EC3F1; }
  static PackageInfo & GetDefault() { static PackageInfo def; return def; }
};

template <>
struct StormReflTypeInfo<PackageInfo>::field_data_static<0>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_Town"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x727B52BB; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PackageInfo::m_Town; }
};

template <typename Self>
struct StormReflTypeInfo<PackageInfo>::field_data<0, Self> : public StormReflTypeInfo<PackageInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_Town; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_Town; }
  void SetDefault() { self.m_Town = StormReflTypeInfo<PackageInfo>::GetDefault().m_Town; }
};

template <>
struct StormReflTypeInfo<PackageInfo>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_PickedUp"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x951D14A9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PackageInfo::m_PickedUp; }
};

template <typename Self>
struct StormReflTypeInfo<PackageInfo>::field_data<1, Self> : public StormReflTypeInfo<PackageInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_PickedUp; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_PickedUp; }
  void SetDefault() { self.m_PickedUp = StormReflTypeInfo<PackageInfo>::GetDefault().m_PickedUp; }
};

template <>
struct StormReflTypeInfo<DeliveryInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DeliveryInfo"; }
  static constexpr auto GetNameHash() { return 0x194E37CF; }
  static DeliveryInfo & GetDefault() { static DeliveryInfo def; return def; }
};

template <>
struct StormReflTypeInfo<DeliveryInfo>::field_data_static<0>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_Town"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x727B52BB; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DeliveryInfo::m_Town; }
};

template <typename Self>
struct StormReflTypeInfo<DeliveryInfo>::field_data<0, Self> : public StormReflTypeInfo<DeliveryInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_Town; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_Town; }
  void SetDefault() { self.m_Town = StormReflTypeInfo<DeliveryInfo>::GetDefault().m_Town; }
};

template <>
struct StormReflTypeInfo<DeliveryInfo>::field_data_static<1>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_Reward"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x03EE259B; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DeliveryInfo::m_Reward; }
};

template <typename Self>
struct StormReflTypeInfo<DeliveryInfo>::field_data<1, Self> : public StormReflTypeInfo<DeliveryInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_Reward; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_Reward; }
  void SetDefault() { self.m_Reward = StormReflTypeInfo<DeliveryInfo>::GetDefault().m_Reward; }
};

template <>
struct StormReflTypeInfo<AIPlayerInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AIPlayerInfo"; }
  static constexpr auto GetNameHash() { return 0x8A30B78C; }
  static AIPlayerInfo & GetDefault() { static AIPlayerInfo def; return def; }
};

template <>
struct StormReflTypeInfo<GamePlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
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
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayer>::field_data<0, Self> : public StormReflTypeInfo<GamePlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GamePlayer>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GamePlayer>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, 0, kMaxTeams - 1>; // NetRangedNumber<int, 0, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0xAAFE6A4F; }
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
struct StormReflTypeInfo<GamePlayer>::field_data_static<2>
{
  using member_type = NetOptional<AIPlayerInfo>; // NetOptional<AIPlayerInfo>
  static constexpr auto GetName() { return "m_AIPlayerInfo"; }
  static constexpr auto GetType() { return "NetOptional<AIPlayerInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35831512; }
  static constexpr unsigned GetTypeNameHash() { return 0xE3C4FC55; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_AIPlayerInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayer>::field_data<2, Self> : public StormReflTypeInfo<GamePlayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<AIPlayerInfo>> & Get() { return self.m_AIPlayerInfo; }
  std::add_const_t<std::remove_reference_t<NetOptional<AIPlayerInfo>>> & Get() const { return self.m_AIPlayerInfo; }
  void SetDefault() { self.m_AIPlayerInfo = StormReflTypeInfo<GamePlayer>::GetDefault().m_AIPlayerInfo; }
};

template <>
struct StormReflTypeInfo<GamePlayer>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5A315CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_Ready; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayer>::field_data<3, Self> : public StormReflTypeInfo<GamePlayer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Ready; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Ready; }
  void SetDefault() { self.m_Ready = StormReflTypeInfo<GamePlayer>::GetDefault().m_Ready; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInstanceData"; }
  static constexpr auto GetNameHash() { return 0xC7A440E6; }
  static GameInstanceData & GetDefault() { static GameInstanceData def; return def; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  using member_type = NetSparseList<GamePlayer, kMaxPlayers>; // NetSparseList<GamePlayer, 4>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GamePlayer, 4>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0x32E536AA; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<0, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GamePlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GamePlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Players; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<1, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams>; // NetRangedNumber<int, -1, 4>
  static constexpr auto GetName() { return "m_WiningTeam"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 4>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0A538050; }
  static constexpr unsigned GetTypeNameHash() { return 0x7CCB5820; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_WiningTeam; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<2, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams>> & Get() { return self.m_WiningTeam; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams>>> & Get() const { return self.m_WiningTeam; }
  void SetDefault() { self.m_WiningTeam = StormReflTypeInfo<GameInstanceData>::GetDefault().m_WiningTeam; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  using member_type = NetRangedNumber<int, 0, kMaxCountdown>; // NetRangedNumber<int, 0, 180>
  static constexpr auto GetName() { return "m_Countdown"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 180>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB4BA24D; }
  static constexpr unsigned GetTypeNameHash() { return 0x2BFCFCEC; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Countdown; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<3, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxCountdown>> & Get() { return self.m_Countdown; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxCountdown>>> & Get() const { return self.m_Countdown; }
  void SetDefault() { self.m_Countdown = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Countdown; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  using member_type = NetRangedNumber<int, 0, kMaxRoundTimer>; // NetRangedNumber<int, 0, 5400>
  static constexpr auto GetName() { return "m_RoundTimer"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 5400>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD93A7968; }
  static constexpr unsigned GetTypeNameHash() { return 0x9B21947F; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_RoundTimer; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<4, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxRoundTimer>> & Get() { return self.m_RoundTimer; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxRoundTimer>>> & Get() const { return self.m_RoundTimer; }
  void SetDefault() { self.m_RoundTimer = StormReflTypeInfo<GameInstanceData>::GetDefault().m_RoundTimer; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<5>
{
  using member_type = NetRandom; // NetRandom
  static constexpr auto GetName() { return "m_Random"; }
  static constexpr auto GetType() { return "NetRandom"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B048D1D; }
  static constexpr unsigned GetTypeNameHash() { return 0xD020E89C; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Random; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<5, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRandom> & Get() { return self.m_Random; }
  std::add_const_t<std::remove_reference_t<NetRandom>> & Get() const { return self.m_Random; }
  void SetDefault() { self.m_Random = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Random; }
};

namespace StormReflFileInfo
{
  struct GameNetworkData
  {
    static const int types_n = 9;
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
    using type = ::PackageInfo;
  };

  template <>
  struct GameNetworkData::type_info<5>
  {
    using type = ::DeliveryInfo;
  };

  template <>
  struct GameNetworkData::type_info<6>
  {
    using type = ::AIPlayerInfo;
  };

  template <>
  struct GameNetworkData::type_info<7>
  {
    using type = ::GamePlayer;
  };

  template <>
  struct GameNetworkData::type_info<8>
  {
    using type = ::GameInstanceData;
  };

}

