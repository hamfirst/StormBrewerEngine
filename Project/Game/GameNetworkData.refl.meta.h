#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkData.refl.h"


template <>
struct StormReflEnumInfo<RoundState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "RoundState"; }
  static constexpr auto GetNameHash() { return 0xD59D9F94; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<RoundState>::elems<0>
{
  static constexpr auto GetName() { return "kPreRound"; }
  static constexpr auto GetNameHash() { return 0x8CDA95D7; }
  static constexpr auto GetValue() { return RoundState::kPreRound; }
};

template <>
struct StormReflEnumInfo<RoundState>::elems<1>
{
  static constexpr auto GetName() { return "kRound"; }
  static constexpr auto GetNameHash() { return 0x11FC6C17; }
  static constexpr auto GetValue() { return RoundState::kRound; }
};

template <>
struct StormReflEnumInfo<RoundState>::elems<2>
{
  static constexpr auto GetName() { return "kPostRound"; }
  static constexpr auto GetNameHash() { return 0x3E2AD3DC; }
  static constexpr auto GetValue() { return RoundState::kPostRound; }
};

template <>
struct StormReflTypeInfo<GameInitSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInitSettings"; }
  static constexpr auto GetNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static GameInitSettings & GetDefault() { static GameInitSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInitSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInitSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInitSettings *>(ptr);
    if(typeid(GameInitSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInitSettings *>(ptr);
    if(typeid(GameInitSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameInitSettings>::field_data_static<0>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_StageIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54FBDE46; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInitSettings::m_StageIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInitSettings *>(obj); return &ptr->m_StageIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInitSettings *>(obj); return &ptr->m_StageIndex; }
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
struct StormReflTypeInfo<GameInitSettings>::field_data_static<1>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerCount"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E784CAA; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInitSettings::m_PlayerCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInitSettings *>(obj); return &ptr->m_PlayerCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInitSettings *>(obj); return &ptr->m_PlayerCount; }
};

template <typename Self>
struct StormReflTypeInfo<GameInitSettings>::field_data<1, Self> : public StormReflTypeInfo<GameInitSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerCount; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerCount; }
  void SetDefault() { self.m_PlayerCount = StormReflTypeInfo<GameInitSettings>::GetDefault().m_PlayerCount; }
};

template <>
struct StormReflTypeInfo<GameInitSettings>::field_data_static<2>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_ScoreLimit"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43D3DFC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInitSettings::m_ScoreLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInitSettings *>(obj); return &ptr->m_ScoreLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInitSettings *>(obj); return &ptr->m_ScoreLimit; }
};

template <typename Self>
struct StormReflTypeInfo<GameInitSettings>::field_data<2, Self> : public StormReflTypeInfo<GameInitSettings>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_ScoreLimit; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_ScoreLimit; }
  void SetDefault() { self.m_ScoreLimit = StormReflTypeInfo<GameInitSettings>::GetDefault().m_ScoreLimit; }
};

template <>
struct StormReflTypeInfo<GameInitSettings>::field_data_static<3>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_TimeLimit"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92EF9F49; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInitSettings::m_TimeLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInitSettings *>(obj); return &ptr->m_TimeLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInitSettings *>(obj); return &ptr->m_TimeLimit; }
};

template <typename Self>
struct StormReflTypeInfo<GameInitSettings>::field_data<3, Self> : public StormReflTypeInfo<GameInitSettings>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_TimeLimit; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_TimeLimit; }
  void SetDefault() { self.m_TimeLimit = StormReflTypeInfo<GameInitSettings>::GetDefault().m_TimeLimit; }
};

template <>
struct StormReflTypeInfo<ClientLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientLocalData"; }
  static constexpr auto GetNameHash() { return 0x56368E1B; }
  static constexpr bool HasDefault() { return true; }
  static ClientLocalData & GetDefault() { static ClientLocalData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ClientLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ClientLocalData *>(ptr);
    if(typeid(ClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ClientLocalData *>(ptr);
    if(typeid(ClientLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ClientLocalData>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, -1, kMaxPlayers>; // NetRangedNumber<int, -1, 16>
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xE6635155; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientLocalData::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientLocalData *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientLocalData *>(obj); return &ptr->m_PlayerIndex; }
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
struct StormReflTypeInfo<ClientLocalData>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, -1, kMaxPlayers>; // NetRangedNumber<int, -1, 16>
  static constexpr auto GetName() { return "m_ObserverIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA780578; }
  static constexpr unsigned GetTypeNameHash() { return 0xE6635155; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientLocalData::m_ObserverIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientLocalData *>(obj); return &ptr->m_ObserverIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientLocalData *>(obj); return &ptr->m_ObserverIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ClientLocalData>::field_data<1, Self> : public StormReflTypeInfo<ClientLocalData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxPlayers>> & Get() { return self.m_ObserverIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxPlayers>>> & Get() const { return self.m_ObserverIndex; }
  void SetDefault() { self.m_ObserverIndex = StormReflTypeInfo<ClientLocalData>::GetDefault().m_ObserverIndex; }
};

template <>
struct StormReflTypeInfo<ClientInput>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ClientInput"; }
  static constexpr auto GetNameHash() { return 0x13CC217D; }
  static constexpr bool HasDefault() { return true; }
  static ClientInput & GetDefault() { static ClientInput def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ClientInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ClientInput *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ClientInput *>(ptr);
    if(typeid(ClientInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ClientInput *>(ptr);
    if(typeid(ClientInput).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ClientInput>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_JumpHeld"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB2E64C00; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientInput::m_JumpHeld; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientInput *>(obj); return &ptr->m_JumpHeld; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientInput *>(obj); return &ptr->m_JumpHeld; }
};

template <typename Self>
struct StormReflTypeInfo<ClientInput>::field_data<0, Self> : public StormReflTypeInfo<ClientInput>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_JumpHeld; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_JumpHeld; }
  void SetDefault() { self.m_JumpHeld = StormReflTypeInfo<ClientInput>::GetDefault().m_JumpHeld; }
};

template <>
struct StormReflTypeInfo<ClientInput>::field_data_static<1>
{
  using member_type = GameNetVal; // NetFixedPoint<long, 32, 16>
  static constexpr auto GetName() { return "m_XInput"; }
  static constexpr auto GetType() { return "NetFixedPoint<long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC4479309; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D893FA0; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientInput::m_XInput; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientInput *>(obj); return &ptr->m_XInput; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientInput *>(obj); return &ptr->m_XInput; }
};

template <typename Self>
struct StormReflTypeInfo<ClientInput>::field_data<1, Self> : public StormReflTypeInfo<ClientInput>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_XInput; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_XInput; }
  void SetDefault() { self.m_XInput = StormReflTypeInfo<ClientInput>::GetDefault().m_XInput; }
};

template <>
struct StormReflTypeInfo<ClientInput>::field_data_static<2>
{
  using member_type = GameNetVal; // NetFixedPoint<long, 32, 16>
  static constexpr auto GetName() { return "m_YInput"; }
  static constexpr auto GetType() { return "NetFixedPoint<long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F1B40AC; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D893FA0; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ClientInput::m_YInput; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientInput *>(obj); return &ptr->m_YInput; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientInput *>(obj); return &ptr->m_YInput; }
};

template <typename Self>
struct StormReflTypeInfo<ClientInput>::field_data<2, Self> : public StormReflTypeInfo<ClientInput>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_YInput; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_YInput; }
  void SetDefault() { self.m_YInput = StormReflTypeInfo<ClientInput>::GetDefault().m_YInput; }
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
  static constexpr bool HasDefault() { return true; }
  static ClientAuthData & GetDefault() { static ClientAuthData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ClientAuthData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ClientAuthData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ClientAuthData *>(ptr);
    if(typeid(ClientAuthData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ClientAuthData *>(ptr);
    if(typeid(ClientAuthData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ClientAuthData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Frame"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38CEACAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ClientAuthData::m_Frame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientAuthData *>(obj); return &ptr->m_Frame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientAuthData *>(obj); return &ptr->m_Frame; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ClientAuthData::m_Input; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ClientAuthData *>(obj); return &ptr->m_Input; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ClientAuthData *>(obj); return &ptr->m_Input; }
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
  static constexpr bool HasDefault() { return true; }
  static AIPlayerInfo & GetDefault() { static AIPlayerInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AIPlayerInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AIPlayerInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AIPlayerInfo *>(ptr);
    if(typeid(AIPlayerInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AIPlayerInfo *>(ptr);
    if(typeid(AIPlayerInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static GamePlayer & GetDefault() { static GamePlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GamePlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GamePlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GamePlayer *>(ptr);
    if(typeid(GamePlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GamePlayer *>(ptr);
    if(typeid(GamePlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GamePlayer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayer *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayer *>(obj); return &ptr->m_UserName; }
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
  using member_type = NetRangedNumber<int, 0, kMaxTeams - 1>; // NetRangedNumber<int, 0, 1>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 1>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x98C808CD; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GamePlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayer *>(obj); return &ptr->m_Team; }
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
struct StormReflTypeInfo<GameObserver>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameObserver"; }
  static constexpr auto GetNameHash() { return 0x9BA2631B; }
  static constexpr bool HasDefault() { return true; }
  static GameObserver & GetDefault() { static GameObserver def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameObserver *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameObserver *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameObserver *>(ptr);
    if(typeid(GameObserver).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameObserver *>(ptr);
    if(typeid(GameObserver).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameObserver>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameObserver::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameObserver *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameObserver *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GameObserver>::field_data<0, Self> : public StormReflTypeInfo<GameObserver>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GameObserver>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInstanceLowFrequencyData"; }
  static constexpr auto GetNameHash() { return 0x05C4FAAF; }
  static constexpr bool HasDefault() { return true; }
  static GameInstanceLowFrequencyData & GetDefault() { static GameInstanceLowFrequencyData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceLowFrequencyData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceLowFrequencyData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceLowFrequencyData *>(ptr);
    if(typeid(GameInstanceLowFrequencyData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceLowFrequencyData *>(ptr);
    if(typeid(GameInstanceLowFrequencyData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<0>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceLowFrequencyData::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceLowFrequencyData *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceLowFrequencyData *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data<0, Self> : public StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<GameInstanceLowFrequencyData>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<1>
{
  using member_type = NetSparseList<GamePlayer, kMaxPlayers>; // NetSparseList<GamePlayer, 16>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "NetSparseList<GamePlayer, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB401505; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceLowFrequencyData::m_Players; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceLowFrequencyData *>(obj); return &ptr->m_Players; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceLowFrequencyData *>(obj); return &ptr->m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data<1, Self> : public StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GamePlayer, kMaxPlayers>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GamePlayer, kMaxPlayers>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameInstanceLowFrequencyData>::GetDefault().m_Players; }
};

template <>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<2>
{
  using member_type = NetSparseList<GameObserver, 128>; // NetSparseList<GameObserver, 128>
  static constexpr auto GetName() { return "m_Observers"; }
  static constexpr auto GetType() { return "NetSparseList<GameObserver, 128>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF9DBF68F; }
  static constexpr unsigned GetTypeNameHash() { return 0xD5700489; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceLowFrequencyData::m_Observers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceLowFrequencyData *>(obj); return &ptr->m_Observers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceLowFrequencyData *>(obj); return &ptr->m_Observers; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data<2, Self> : public StormReflTypeInfo<GameInstanceLowFrequencyData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<GameObserver, 128>> & Get() { return self.m_Observers; }
  std::add_const_t<std::remove_reference_t<NetSparseList<GameObserver, 128>>> & Get() const { return self.m_Observers; }
  void SetDefault() { self.m_Observers = StormReflTypeInfo<GameInstanceLowFrequencyData>::GetDefault().m_Observers; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInstanceData"; }
  static constexpr auto GetNameHash() { return 0xC7A440E6; }
  static constexpr bool HasDefault() { return true; }
  static GameInstanceData & GetDefault() { static GameInstanceData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceData *>(ptr);
    if(typeid(GameInstanceData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceData *>(ptr);
    if(typeid(GameInstanceData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  using member_type = NetSparseList<AIPlayerInfo, kMaxPlayers>; // NetSparseList<AIPlayerInfo, 16>
  static constexpr auto GetName() { return "m_AIPlayerInfo"; }
  static constexpr auto GetType() { return "NetSparseList<AIPlayerInfo, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35831512; }
  static constexpr unsigned GetTypeNameHash() { return 0xF57EE74B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_AIPlayerInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_AIPlayerInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_AIPlayerInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<0, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetSparseList<AIPlayerInfo, kMaxPlayers>> & Get() { return self.m_AIPlayerInfo; }
  std::add_const_t<std::remove_reference_t<NetSparseList<AIPlayerInfo, kMaxPlayers>>> & Get() const { return self.m_AIPlayerInfo; }
  void SetDefault() { self.m_AIPlayerInfo = StormReflTypeInfo<GameInstanceData>::GetDefault().m_AIPlayerInfo; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  using member_type = NetRangedNumber<int, 0, kMaxScore>[2]; // NetRangedNumber<int, 0, 5>[2]
  static constexpr auto GetName() { return "m_Score"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 5>[2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBFAFA731; }
  static constexpr unsigned GetTypeNameHash() { return 0x569302BA; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Score; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_Score; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_Score; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<1, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxScore>[2]> & Get() { return self.m_Score; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxScore>[2]>> & Get() const { return self.m_Score; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  using member_type = NetOptional<NetRangedNumber<int, -1, kMaxTeams> >; // NetOptional<NetRangedNumber<int, -1, 2> >
  static constexpr auto GetName() { return "m_WiningTeam"; }
  static constexpr auto GetType() { return "NetOptional<NetRangedNumber<int, -1, 2> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0A538050; }
  static constexpr unsigned GetTypeNameHash() { return 0x0891E901; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_WiningTeam; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_WiningTeam; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_WiningTeam; }
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
  using member_type = NetEnum<RoundState>; // NetEnum<RoundState>
  static constexpr auto GetName() { return "m_RoundState"; }
  static constexpr auto GetType() { return "NetEnum<RoundState>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10797589; }
  static constexpr unsigned GetTypeNameHash() { return 0x55F99025; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_RoundState; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_RoundState; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_RoundState; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<3, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<RoundState>> & Get() { return self.m_RoundState; }
  std::add_const_t<std::remove_reference_t<NetEnum<RoundState>>> & Get() const { return self.m_RoundState; }
  void SetDefault() { self.m_RoundState = StormReflTypeInfo<GameInstanceData>::GetDefault().m_RoundState; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  using member_type = NetRangedNumber<int, 0, kMaxRoundTimer>; // NetRangedNumber<int, 0, 18000>
  static constexpr auto GetName() { return "m_RoundTimer"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 18000>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD93A7968; }
  static constexpr unsigned GetTypeNameHash() { return 0x13A03D86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_RoundTimer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_RoundTimer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_RoundTimer; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Random; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_Random; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_Random; }
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

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_FrameCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BC914D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_FrameCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_FrameCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_FrameCount; }
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<6, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<6>
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
    using type = ::GameObserver;
  };

  template <>
  struct GameNetworkData::type_info<7>
  {
    using type = ::GameInstanceLowFrequencyData;
  };

  template <>
  struct GameNetworkData::type_info<8>
  {
    using type = ::GameInstanceData;
  };

}

