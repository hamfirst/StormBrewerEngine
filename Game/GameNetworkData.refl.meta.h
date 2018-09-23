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
  using member_type = NetRangedNumber<int, -1, kMaxPlayers>; // NetRangedNumber<int, -1, 2>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0x2A91FFA6; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientLocalData::m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ClientLocalData>::field_data<0, Self> : public StormReflTypeInfo<ClientLocalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxPlayers>> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxPlayers>>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ClientLocalData>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ClientInput>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientInput"; }
  static constexpr auto GetNameHash() { return 0x13CC217D; }
  static ClientInput & GetDefault() { static ClientInput def; return def; }
};

template <>
struct StormReflTypeInfo<ClientInput>::field_data_static<0>
{
  using member_type = GameNetVal; // NetFixedPoint<long long, 32, 16>
  static constexpr auto GetName() { return "m_InputAngle"; }
  static constexpr auto GetType() { return "NetFixedPoint<long long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x55B148EC; }
  static constexpr unsigned GetTypeNameHash() { return 0xDF428045; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientInput::m_InputAngle; }
};

template <typename Self>
struct StormReflTypeInfo<ClientInput>::field_data<0, Self> : public StormReflTypeInfo<ClientInput>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_InputAngle; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_InputAngle; }
  void SetDefault() { self.m_InputAngle = StormReflTypeInfo<ClientInput>::GetDefault().m_InputAngle; }
};

template <>
struct StormReflTypeInfo<ClientInput>::field_data_static<1>
{
  using member_type = GameNetVal; // NetFixedPoint<long long, 32, 16>
  static constexpr auto GetName() { return "m_InputStr"; }
  static constexpr auto GetType() { return "NetFixedPoint<long long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC2CCEED1; }
  static constexpr unsigned GetTypeNameHash() { return 0xDF428045; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientInput::m_InputStr; }
};

template <typename Self>
struct StormReflTypeInfo<ClientInput>::field_data<1, Self> : public StormReflTypeInfo<ClientInput>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_InputStr; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_InputStr; }
  void SetDefault() { self.m_InputStr = StormReflTypeInfo<ClientInput>::GetDefault().m_InputStr; }
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
  static constexpr int fields_n = 3;
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
struct StormReflTypeInfo<GameInstanceData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
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
  using member_type = NetSparseList<GamePlayer, kMaxPlayers>; // NetSparseList<GamePlayer, 2>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GamePlayer, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0x64BF912C; }
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
  using member_type = NetRangedNumber<int, 0, kMaxScore> [4]; // NetRangedNumber<int, 0, 5> [4]
  static constexpr auto GetName() { return "m_Score"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 5> [4]"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBFAFA731; }
  static constexpr unsigned GetTypeNameHash() { return 0xA33D0C88; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Score; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<1, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxScore> [4]> & Get() { return self.m_Score; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxScore> [4]>> & Get() const { return self.m_Score; }
  void SetDefault() { self.m_Score = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Score; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  using member_type = NetOptional<NetRangedNumber<int, -1, kMaxTeams> >; // NetOptional<NetRangedNumber<int, -1, 4> >
  static constexpr auto GetName() { return "m_WiningTeam"; }
  static constexpr auto GetType() { return "NetOptional<NetRangedNumber<int, -1, 4> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0A538050; }
  static constexpr unsigned GetTypeNameHash() { return 0x2DFAB6DD; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_WiningTeam; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<2, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetRangedNumber<int, -1, kMaxTeams> >> & Get() { return self.m_WiningTeam; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetRangedNumber<int, -1, kMaxTeams> >>> & Get() const { return self.m_WiningTeam; }
  void SetDefault() { self.m_WiningTeam = StormReflTypeInfo<GameInstanceData>::GetDefault().m_WiningTeam; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  using member_type = NetRandom; // NetRandom
  static constexpr auto GetName() { return "m_Random"; }
  static constexpr auto GetType() { return "NetRandom"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B048D1D; }
  static constexpr unsigned GetTypeNameHash() { return 0xD020E89C; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Random; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<3, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRandom> & Get() { return self.m_Random; }
  std::add_const_t<std::remove_reference_t<NetRandom>> & Get() const { return self.m_Random; }
  void SetDefault() { self.m_Random = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Random; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_FrameCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BC914D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_FrameCount; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<4, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_FrameCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_FrameCount; }
  void SetDefault() { self.m_FrameCount = StormReflTypeInfo<GameInstanceData>::GetDefault().m_FrameCount; }
};

namespace StormReflFileInfo
{
  struct GameNetworkData
  {
    static const int types_n = 7;
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
    using type = ::AIPlayerInfo;
  };

  template <>
  struct GameNetworkData::type_info<5>
  {
    using type = ::GamePlayer;
  };

  template <>
  struct GameNetworkData::type_info<6>
  {
    using type = ::GameInstanceData;
  };

}

