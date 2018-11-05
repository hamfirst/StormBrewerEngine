#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameFullState.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkExternals.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"


template <>
struct StormReflTypeInfo<GameFullState>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameFullState"; }
  static constexpr auto GetNameHash() { return 0x0E9BE336; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameFullState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameFullState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameFullState *>(ptr);
    if(typeid(GameFullState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameFullState *>(ptr);
    if(typeid(GameFullState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameFullState>::field_data_static<0>
{
  using member_type = ServerObjectManager; // ServerObjectManager
  static constexpr auto GetName() { return "m_ServerObjectManager"; }
  static constexpr auto GetType() { return "ServerObjectManager"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA597FEC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x5CC26F4B; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameFullState::m_ServerObjectManager; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameFullState *>(obj); return &ptr->m_ServerObjectManager; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameFullState *>(obj); return &ptr->m_ServerObjectManager; }
};

template <typename Self>
struct StormReflTypeInfo<GameFullState>::field_data<0, Self> : public StormReflTypeInfo<GameFullState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectManager> & Get() { return self.m_ServerObjectManager; }
  std::add_const_t<std::remove_reference_t<ServerObjectManager>> & Get() const { return self.m_ServerObjectManager; }
};

template <>
struct StormReflTypeInfo<GameFullState>::field_data_static<1>
{
  using member_type = GameInstanceData; // GameInstanceData
  static constexpr auto GetName() { return "m_InstanceData"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEFC069F9; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameFullState::m_InstanceData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameFullState *>(obj); return &ptr->m_InstanceData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameFullState *>(obj); return &ptr->m_InstanceData; }
};

template <typename Self>
struct StormReflTypeInfo<GameFullState>::field_data<1, Self> : public StormReflTypeInfo<GameFullState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInstanceData> & Get() { return self.m_InstanceData; }
  std::add_const_t<std::remove_reference_t<GameInstanceData>> & Get() const { return self.m_InstanceData; }
};

template <>
struct StormReflTypeInfo<GameStateStagingPlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStateStagingPlayer"; }
  static constexpr auto GetNameHash() { return 0x29D762F5; }
  static GameStateStagingPlayer & GetDefault() { static GameStateStagingPlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameStateStagingPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateStagingPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameStateStagingPlayer *>(ptr);
    if(typeid(GameStateStagingPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateStagingPlayer *>(ptr);
    if(typeid(GameStateStagingPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameStateStagingPlayer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStateStagingPlayer::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStagingPlayer *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStagingPlayer *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStagingPlayer>::field_data<0, Self> : public StormReflTypeInfo<GameStateStagingPlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GameStateStagingPlayer>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GameStateStagingPlayer>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x338ACEE7; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStateStagingPlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStagingPlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStagingPlayer *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStagingPlayer>::field_data<1, Self> : public StormReflTypeInfo<GameStateStagingPlayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameStateStagingPlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameStateStaging>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStateStaging"; }
  static constexpr auto GetNameHash() { return 0x0DFED8EC; }
  static GameStateStaging & GetDefault() { static GameStateStaging def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameStateStaging *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateStaging *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameStateStaging *>(ptr);
    if(typeid(GameStateStaging).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateStaging *>(ptr);
    if(typeid(GameStateStaging).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameStateStaging>::field_data_static<0>
{
  using member_type = NetSparseList<GameStateStagingPlayer, kMaxPlayers>; // NetSparseList<GameStateStagingPlayer, 2>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GameStateStagingPlayer, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0x2DB30DD7; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStateStaging::m_Players; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStaging *>(obj); return &ptr->m_Players; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStaging *>(obj); return &ptr->m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStaging>::field_data<0, Self> : public StormReflTypeInfo<GameStateStaging>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GameStateStagingPlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GameStateStagingPlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameStateStaging>::GetDefault().m_Players; }
};

template <>
struct StormReflTypeInfo<GameStateStaging>::field_data_static<1>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStateStaging::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStaging *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStaging *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStaging>::field_data<1, Self> : public StormReflTypeInfo<GameStateStaging>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<GameStateStaging>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<GameStateStaging>::field_data_static<2>
{
  using member_type = NetRangedNumber<int, 0, 255>; // NetRangedNumber<int, 0, 255>
  static constexpr auto GetName() { return "m_Countdown"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 255>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB4BA24D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4CE63414; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameStateStaging::m_Countdown; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStaging *>(obj); return &ptr->m_Countdown; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStaging *>(obj); return &ptr->m_Countdown; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStaging>::field_data<2, Self> : public StormReflTypeInfo<GameStateStaging>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 255>> & Get() { return self.m_Countdown; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 255>>> & Get() const { return self.m_Countdown; }
  void SetDefault() { self.m_Countdown = StormReflTypeInfo<GameStateStaging>::GetDefault().m_Countdown; }
};

template <>
struct StormReflTypeInfo<GameStateStaging>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_WaitTimer"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51047B6E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameStateStaging::m_WaitTimer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateStaging *>(obj); return &ptr->m_WaitTimer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateStaging *>(obj); return &ptr->m_WaitTimer; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateStaging>::field_data<3, Self> : public StormReflTypeInfo<GameStateStaging>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_WaitTimer; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_WaitTimer; }
  void SetDefault() { self.m_WaitTimer = StormReflTypeInfo<GameStateStaging>::GetDefault().m_WaitTimer; }
};

template <>
struct StormReflTypeInfo<GameStateLoadingPlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStateLoadingPlayer"; }
  static constexpr auto GetNameHash() { return 0x2C1DE3EB; }
  static GameStateLoadingPlayer & GetDefault() { static GameStateLoadingPlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameStateLoadingPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateLoadingPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameStateLoadingPlayer *>(ptr);
    if(typeid(GameStateLoadingPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateLoadingPlayer *>(ptr);
    if(typeid(GameStateLoadingPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStateLoadingPlayer::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateLoadingPlayer *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateLoadingPlayer *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data<0, Self> : public StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GameStateLoadingPlayer>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Loaded"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B810EF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStateLoadingPlayer::m_Loaded; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateLoadingPlayer *>(obj); return &ptr->m_Loaded; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateLoadingPlayer *>(obj); return &ptr->m_Loaded; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data<1, Self> : public StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Loaded; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Loaded; }
  void SetDefault() { self.m_Loaded = StormReflTypeInfo<GameStateLoadingPlayer>::GetDefault().m_Loaded; }
};

template <>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<2>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x338ACEE7; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameStateLoadingPlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateLoadingPlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateLoadingPlayer *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateLoadingPlayer>::field_data<2, Self> : public StormReflTypeInfo<GameStateLoadingPlayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameStateLoadingPlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameStateLoading>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStateLoading"; }
  static constexpr auto GetNameHash() { return 0xE7CC697D; }
  static GameStateLoading & GetDefault() { static GameStateLoading def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameStateLoading *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateLoading *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameStateLoading *>(ptr);
    if(typeid(GameStateLoading).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameStateLoading *>(ptr);
    if(typeid(GameStateLoading).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameStateLoading>::field_data_static<0>
{
  using member_type = NetSparseList<GameStateLoadingPlayer, kMaxPlayers>; // NetSparseList<GameStateLoadingPlayer, 2>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GameStateLoadingPlayer, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0x3CFD9787; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStateLoading::m_Players; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStateLoading *>(obj); return &ptr->m_Players; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStateLoading *>(obj); return &ptr->m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameStateLoading>::field_data<0, Self> : public StormReflTypeInfo<GameStateLoading>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GameStateLoadingPlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GameStateLoadingPlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameStateLoading>::GetDefault().m_Players; }
};

template <>
struct StormReflTypeInfo<GameHistoryInput>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryInput"; }
  static constexpr auto GetNameHash() { return 0xC01F4DCD; }
  static GameHistoryInput & GetDefault() { static GameHistoryInput def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryInput *>(ptr);
    if(typeid(GameHistoryInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryInput *>(ptr);
    if(typeid(GameHistoryInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryInput>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 0, kMaxPlayers>; // NetRangedNumber<int, 0, 2>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3E55B0E; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryInput::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryInput *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryInput *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryInput>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryInput>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxPlayers>> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxPlayers>>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<GameHistoryInput>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<GameHistoryInput>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryInput::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryInput *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryInput *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryInput>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryInput>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryInput>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryInput>::field_data_static<2>
{
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameHistoryInput::m_Input; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryInput *>(obj); return &ptr->m_Input; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryInput *>(obj); return &ptr->m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryInput>::field_data<2, Self> : public StormReflTypeInfo<GameHistoryInput>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientInput> & Get() { return self.m_Input; }
  std::add_const_t<std::remove_reference_t<ClientInput>> & Get() const { return self.m_Input; }
  void SetDefault() { self.m_Input = StormReflTypeInfo<GameHistoryInput>::GetDefault().m_Input; }
};

template <>
struct StormReflTypeInfo<GameHistoryEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryEvent"; }
  static constexpr auto GetNameHash() { return 0x239975BD; }
  static GameHistoryEvent & GetDefault() { static GameHistoryEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryEvent *>(ptr);
    if(typeid(GameHistoryEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryEvent *>(ptr);
    if(typeid(GameHistoryEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryEvent>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 0, kMaxPlayers>; // NetRangedNumber<int, 0, 2>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 2>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3E55B0E; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryEvent::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryEvent *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryEvent>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxPlayers>> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxPlayers>>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<GameHistoryEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<GameHistoryEvent>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryEvent::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryEvent *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryEvent *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryEvent>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryEvent>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryEvent>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryEvent>::field_data_static<2>
{
  using member_type = NetPolymorphic<ClientNetworkEvent>; // NetPolymorphic<ClientNetworkEvent>
  static constexpr auto GetName() { return "m_Event"; }
  static constexpr auto GetType() { return "NetPolymorphic<ClientNetworkEvent>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6989AC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13BC7AA5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameHistoryEvent::m_Event; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryEvent *>(obj); return &ptr->m_Event; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryEvent *>(obj); return &ptr->m_Event; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryEvent>::field_data<2, Self> : public StormReflTypeInfo<GameHistoryEvent>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<ClientNetworkEvent>> & Get() { return self.m_Event; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<ClientNetworkEvent>>> & Get() const { return self.m_Event; }
  void SetDefault() { self.m_Event = StormReflTypeInfo<GameHistoryEvent>::GetDefault().m_Event; }
};

template <>
struct StormReflTypeInfo<GameHistoryClientEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryClientEvent"; }
  static constexpr auto GetNameHash() { return 0xD0D0F2E9; }
  static GameHistoryClientEvent & GetDefault() { static GameHistoryClientEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryClientEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryClientEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryClientEvent *>(ptr);
    if(typeid(GameHistoryClientEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryClientEvent *>(ptr);
    if(typeid(GameHistoryClientEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryClientEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryClientEvent::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryClientEvent *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryClientEvent *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryClientEvent>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryClientEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryClientEvent>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryClientEvent>::field_data_static<1>
{
  using member_type = NetPolymorphic<ClientNetworkEvent>; // NetPolymorphic<ClientNetworkEvent>
  static constexpr auto GetName() { return "m_Event"; }
  static constexpr auto GetType() { return "NetPolymorphic<ClientNetworkEvent>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6989AC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13BC7AA5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryClientEvent::m_Event; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryClientEvent *>(obj); return &ptr->m_Event; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryClientEvent *>(obj); return &ptr->m_Event; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryClientEvent>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryClientEvent>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<ClientNetworkEvent>> & Get() { return self.m_Event; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<ClientNetworkEvent>>> & Get() const { return self.m_Event; }
  void SetDefault() { self.m_Event = StormReflTypeInfo<GameHistoryClientEvent>::GetDefault().m_Event; }
};

template <>
struct StormReflTypeInfo<GameHistoryExternal>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryExternal"; }
  static constexpr auto GetNameHash() { return 0x59F94730; }
  static GameHistoryExternal & GetDefault() { static GameHistoryExternal def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryExternal *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryExternal *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryExternal *>(ptr);
    if(typeid(GameHistoryExternal).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryExternal *>(ptr);
    if(typeid(GameHistoryExternal).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryExternal>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryExternal::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryExternal *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryExternal *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryExternal>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryExternal>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryExternal>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryExternal>::field_data_static<1>
{
  using member_type = NetPolymorphic<GameNetworkExternalEvent>; // NetPolymorphic<GameNetworkExternalEvent>
  static constexpr auto GetName() { return "m_Event"; }
  static constexpr auto GetType() { return "NetPolymorphic<GameNetworkExternalEvent>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6989AC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x37E0971E; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryExternal::m_Event; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryExternal *>(obj); return &ptr->m_Event; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryExternal *>(obj); return &ptr->m_Event; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryExternal>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryExternal>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<GameNetworkExternalEvent>> & Get() { return self.m_Event; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<GameNetworkExternalEvent>>> & Get() const { return self.m_Event; }
  void SetDefault() { self.m_Event = StormReflTypeInfo<GameHistoryExternal>::GetDefault().m_Event; }
};

template <>
struct StormReflTypeInfo<GameHistoryAuthEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryAuthEvent"; }
  static constexpr auto GetNameHash() { return 0x6A0E15F8; }
  static GameHistoryAuthEvent & GetDefault() { static GameHistoryAuthEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryAuthEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryAuthEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryAuthEvent *>(ptr);
    if(typeid(GameHistoryAuthEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryAuthEvent *>(ptr);
    if(typeid(GameHistoryAuthEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryAuthEvent>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryAuthEvent::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryAuthEvent *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryAuthEvent *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryAuthEvent>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryAuthEvent>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryAuthEvent>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryAuthEvent>::field_data_static<1>
{
  using member_type = NetPolymorphic<ServerAuthNetworkEvent>; // NetPolymorphic<ServerAuthNetworkEvent>
  static constexpr auto GetName() { return "m_Event"; }
  static constexpr auto GetType() { return "NetPolymorphic<ServerAuthNetworkEvent>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6989AC7; }
  static constexpr unsigned GetTypeNameHash() { return 0x8F4CF2D3; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryAuthEvent::m_Event; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryAuthEvent *>(obj); return &ptr->m_Event; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryAuthEvent *>(obj); return &ptr->m_Event; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryAuthEvent>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryAuthEvent>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<ServerAuthNetworkEvent>> & Get() { return self.m_Event; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<ServerAuthNetworkEvent>>> & Get() const { return self.m_Event; }
  void SetDefault() { self.m_Event = StormReflTypeInfo<GameHistoryAuthEvent>::GetDefault().m_Event; }
};

template <>
struct StormReflTypeInfo<GameHistoryClientLocal>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameHistoryClientLocal"; }
  static constexpr auto GetNameHash() { return 0x60A870A6; }
  static GameHistoryClientLocal & GetDefault() { static GameHistoryClientLocal def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryClientLocal *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryClientLocal *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameHistoryClientLocal *>(ptr);
    if(typeid(GameHistoryClientLocal).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameHistoryClientLocal *>(ptr);
    if(typeid(GameHistoryClientLocal).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameHistoryClientLocal>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameHistoryClientLocal::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryClientLocal *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryClientLocal *>(obj); return &ptr->m_Frame; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryClientLocal>::field_data<0, Self> : public StormReflTypeInfo<GameHistoryClientLocal>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Frame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Frame; }
  void SetDefault() { self.m_Frame = StormReflTypeInfo<GameHistoryClientLocal>::GetDefault().m_Frame; }
};

template <>
struct StormReflTypeInfo<GameHistoryClientLocal>::field_data_static<1>
{
  using member_type = ClientLocalData; // ClientLocalData
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "ClientLocalData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x56368E1B; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameHistoryClientLocal::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameHistoryClientLocal *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameHistoryClientLocal *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<GameHistoryClientLocal>::field_data<1, Self> : public StormReflTypeInfo<GameHistoryClientLocal>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientLocalData> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<ClientLocalData>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<GameHistoryClientLocal>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameGGPOServerGameState"; }
  static constexpr auto GetNameHash() { return 0xC8AA5C86; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameGGPOServerGameState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameGGPOServerGameState *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameGGPOServerGameState *>(ptr);
    if(typeid(GameGGPOServerGameState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameGGPOServerGameState *>(ptr);
    if(typeid(GameGGPOServerGameState).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AckFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE539E657; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_AckFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_AckFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_AckFrame; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<0, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AckFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AckFrame; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ServerFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47C315D6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_ServerFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_ServerFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_ServerFrame; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<1, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ServerFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ServerFrame; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_EventStartFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x23E00566; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_EventStartFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_EventStartFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_EventStartFrame; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<2, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_EventStartFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_EventStartFrame; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<3>
{
  using member_type = std::shared_ptr<GameFullState>; // std::shared_ptr<GameFullState>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "std::shared_ptr<GameFullState>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xDC9D8687; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<3, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::shared_ptr<GameFullState>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<std::shared_ptr<GameFullState>>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<4>
{
  using member_type = NetOptional<NetArrayList<GameHistoryInput, 1023> >; // NetOptional<NetArrayList<GameHistoryInput, 1023> >
  static constexpr auto GetName() { return "m_Inputs"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryInput, 1023> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5EF786; }
  static constexpr unsigned GetTypeNameHash() { return 0x082117F0; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_Inputs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_Inputs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_Inputs; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<4, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryInput, 1023> >> & Get() { return self.m_Inputs; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryInput, 1023> >>> & Get() const { return self.m_Inputs; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<5>
{
  using member_type = NetOptional<NetArrayList<GameHistoryEvent, 1023> >; // NetOptional<NetArrayList<GameHistoryEvent, 1023> >
  static constexpr auto GetName() { return "m_Events"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryEvent, 1023> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1EB80082; }
  static constexpr unsigned GetTypeNameHash() { return 0xD5BC2A09; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_Events; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_Events; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_Events; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<5, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryEvent, 1023> >> & Get() { return self.m_Events; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryEvent, 1023> >>> & Get() const { return self.m_Events; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<6>
{
  using member_type = NetOptional<NetArrayList<GameHistoryExternal, 1023> >; // NetOptional<NetArrayList<GameHistoryExternal, 1023> >
  static constexpr auto GetName() { return "m_Externals"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryExternal, 1023> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x02CC870F; }
  static constexpr unsigned GetTypeNameHash() { return 0xA33B7F85; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_Externals; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_Externals; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_Externals; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<6, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryExternal, 1023> >> & Get() { return self.m_Externals; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryExternal, 1023> >>> & Get() const { return self.m_Externals; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<7>
{
  using member_type = NetOptional<NetArrayList<GameHistoryClientLocal, 1023> >; // NetOptional<NetArrayList<GameHistoryClientLocal, 1023> >
  static constexpr auto GetName() { return "m_LocalData"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryClientLocal, 1023> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x80046698; }
  static constexpr unsigned GetTypeNameHash() { return 0x555026DB; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_LocalData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_LocalData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_LocalData; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<7, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryClientLocal, 1023> >> & Get() { return self.m_LocalData; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryClientLocal, 1023> >>> & Get() const { return self.m_LocalData; }
};

template <>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<8>
{
  using member_type = NetOptional<NetArrayList<GameHistoryAuthEvent, 1023> >; // NetOptional<NetArrayList<GameHistoryAuthEvent, 1023> >
  static constexpr auto GetName() { return "m_ServerAuthEvents"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryAuthEvent, 1023> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD68F20FC; }
  static constexpr unsigned GetTypeNameHash() { return 0x0AD54FF9; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameGGPOServerGameState::m_ServerAuthEvents; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOServerGameState *>(obj); return &ptr->m_ServerAuthEvents; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOServerGameState *>(obj); return &ptr->m_ServerAuthEvents; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOServerGameState>::field_data<8, Self> : public StormReflTypeInfo<GameGGPOServerGameState>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryAuthEvent, 1023> >> & Get() { return self.m_ServerAuthEvents; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryAuthEvent, 1023> >>> & Get() const { return self.m_ServerAuthEvents; }
};

template <>
struct StormReflTypeInfo<GameGGPOClientUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameGGPOClientUpdate"; }
  static constexpr auto GetNameHash() { return 0x1E9F934C; }
  static GameGGPOClientUpdate & GetDefault() { static GameGGPOClientUpdate def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameGGPOClientUpdate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameGGPOClientUpdate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameGGPOClientUpdate *>(ptr);
    if(typeid(GameGGPOClientUpdate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameGGPOClientUpdate *>(ptr);
    if(typeid(GameGGPOClientUpdate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AckFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE539E657; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameGGPOClientUpdate::m_AckFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOClientUpdate *>(obj); return &ptr->m_AckFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOClientUpdate *>(obj); return &ptr->m_AckFrame; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data<0, Self> : public StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AckFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AckFrame; }
  void SetDefault() { self.m_AckFrame = StormReflTypeInfo<GameGGPOClientUpdate>::GetDefault().m_AckFrame; }
};

template <>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ClientFrame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DDFA754; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameGGPOClientUpdate::m_ClientFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOClientUpdate *>(obj); return &ptr->m_ClientFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOClientUpdate *>(obj); return &ptr->m_ClientFrame; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data<1, Self> : public StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ClientFrame; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ClientFrame; }
  void SetDefault() { self.m_ClientFrame = StormReflTypeInfo<GameGGPOClientUpdate>::GetDefault().m_ClientFrame; }
};

template <>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<2>
{
  using member_type = NetOptional<NetArrayList<ClientAuthData, 127> >; // NetOptional<NetArrayList<ClientAuthData, 127> >
  static constexpr auto GetName() { return "m_Inputs"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<ClientAuthData, 127> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E5EF786; }
  static constexpr unsigned GetTypeNameHash() { return 0x500996D0; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameGGPOClientUpdate::m_Inputs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOClientUpdate *>(obj); return &ptr->m_Inputs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOClientUpdate *>(obj); return &ptr->m_Inputs; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data<2, Self> : public StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<ClientAuthData, 127> >> & Get() { return self.m_Inputs; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<ClientAuthData, 127> >>> & Get() const { return self.m_Inputs; }
  void SetDefault() { self.m_Inputs = StormReflTypeInfo<GameGGPOClientUpdate>::GetDefault().m_Inputs; }
};

template <>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<3>
{
  using member_type = NetOptional<NetArrayList<GameHistoryClientEvent, 127> >; // NetOptional<NetArrayList<GameHistoryClientEvent, 127> >
  static constexpr auto GetName() { return "m_Events"; }
  static constexpr auto GetType() { return "NetOptional<NetArrayList<GameHistoryClientEvent, 127> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1EB80082; }
  static constexpr unsigned GetTypeNameHash() { return 0x29601A30; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameGGPOClientUpdate::m_Events; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameGGPOClientUpdate *>(obj); return &ptr->m_Events; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameGGPOClientUpdate *>(obj); return &ptr->m_Events; }
};

template <typename Self>
struct StormReflTypeInfo<GameGGPOClientUpdate>::field_data<3, Self> : public StormReflTypeInfo<GameGGPOClientUpdate>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<NetArrayList<GameHistoryClientEvent, 127> >> & Get() { return self.m_Events; }
  std::add_const_t<std::remove_reference_t<NetOptional<NetArrayList<GameHistoryClientEvent, 127> >>> & Get() const { return self.m_Events; }
  void SetDefault() { self.m_Events = StormReflTypeInfo<GameGGPOClientUpdate>::GetDefault().m_Events; }
};

namespace StormReflFileInfo
{
  struct GameFullState
  {
    static const int types_n = 13;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameFullState::type_info<0>
  {
    using type = ::GameFullState;
  };

  template <>
  struct GameFullState::type_info<1>
  {
    using type = ::GameStateStagingPlayer;
  };

  template <>
  struct GameFullState::type_info<2>
  {
    using type = ::GameStateStaging;
  };

  template <>
  struct GameFullState::type_info<3>
  {
    using type = ::GameStateLoadingPlayer;
  };

  template <>
  struct GameFullState::type_info<4>
  {
    using type = ::GameStateLoading;
  };

  template <>
  struct GameFullState::type_info<5>
  {
    using type = ::GameHistoryInput;
  };

  template <>
  struct GameFullState::type_info<6>
  {
    using type = ::GameHistoryEvent;
  };

  template <>
  struct GameFullState::type_info<7>
  {
    using type = ::GameHistoryClientEvent;
  };

  template <>
  struct GameFullState::type_info<8>
  {
    using type = ::GameHistoryExternal;
  };

  template <>
  struct GameFullState::type_info<9>
  {
    using type = ::GameHistoryAuthEvent;
  };

  template <>
  struct GameFullState::type_info<10>
  {
    using type = ::GameHistoryClientLocal;
  };

  template <>
  struct GameFullState::type_info<11>
  {
    using type = ::GameGGPOServerGameState;
  };

  template <>
  struct GameFullState::type_info<12>
  {
    using type = ::GameGGPOClientUpdate;
  };

}

