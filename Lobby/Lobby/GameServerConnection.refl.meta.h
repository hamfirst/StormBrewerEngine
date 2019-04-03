#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameServerConnection.refl.h"
#include "SharedTypes.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflEnumInfo<GameServerConnectionState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "GameServerConnectionState"; }
  static constexpr auto GetNameHash() { return 0x227BBB92; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<0>
{
  static constexpr auto GetName() { return "kWaitingForConnection"; }
  static constexpr auto GetNameHash() { return 0x3A061D29; }
  static constexpr auto GetValue() { return GameServerConnectionState::kWaitingForConnection; }
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<1>
{
  static constexpr auto GetName() { return "kAuthenticating"; }
  static constexpr auto GetNameHash() { return 0xC9B5A1FD; }
  static constexpr auto GetValue() { return GameServerConnectionState::kAuthenticating; }
};

template <>
struct StormReflEnumInfo<GameServerConnectionState>::elems<2>
{
  static constexpr auto GetName() { return "kConnected"; }
  static constexpr auto GetNameHash() { return 0xB4C21949; }
  static constexpr auto GetValue() { return GameServerConnectionState::kConnected; }
};

template <>
struct StormReflTypeInfo<GameLobbySettings>
{
  using MyBase = GameInitSettings;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GameLobbySettings"; }
  static constexpr auto GetNameHash() { return 0x10166A56; }
  static constexpr bool HasDefault() { return true; }
  static GameLobbySettings & GetDefault() { static GameLobbySettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLobbySettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBAC6DD28 == type_name_hash) return static_cast<GameInitSettings *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbySettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBAC6DD28 == type_name_hash) return static_cast<const GameInitSettings *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLobbySettings *>(ptr);
    if(typeid(GameLobbySettings).hash_code() == type_id_hash) return c;
    if(typeid(GameInitSettings).hash_code() == type_id_hash) return static_cast<GameInitSettings *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbySettings *>(ptr);
    if(typeid(GameLobbySettings).hash_code() == type_id_hash) return c;
    if(typeid(GameInitSettings).hash_code() == type_id_hash) return static_cast<const GameInitSettings *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLobbyPlayer"; }
  static constexpr auto GetNameHash() { return 0x25B729DE; }
  static constexpr bool HasDefault() { return true; }
  static GameLobbyPlayer & GetDefault() { static GameLobbyPlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLobbyPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbyPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLobbyPlayer *>(ptr);
    if(typeid(GameLobbyPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbyPlayer *>(ptr);
    if(typeid(GameLobbyPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<0, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Squad"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x42E66F87; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_Squad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_Squad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_Squad; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<1, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Squad; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Squad; }
  void SetDefault() { self.m_Squad = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_Squad; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<2, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<3, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_NewPlayer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x313BF109; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_NewPlayer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_NewPlayer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_NewPlayer; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<4, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_NewPlayer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_NewPlayer; }
  void SetDefault() { self.m_NewPlayer = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_NewPlayer; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<5, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<6>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<6, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<7>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC245BB1E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_UserRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_UserRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_UserRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<7, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserRandomId; }
  void SetDefault() { self.m_UserRandomId = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_UserRandomId; }
};

template <>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data_static<8>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPlayer::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPlayer *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPlayer *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPlayer>::field_data<8, Self> : public StormReflTypeInfo<GameLobbyPlayer>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<GameLobbyPlayer>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<GameLobby>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLobby"; }
  static constexpr auto GetNameHash() { return 0x39E4E467; }
  static constexpr bool HasDefault() { return true; }
  static GameLobby & GetDefault() { static GameLobby def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLobby *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobby *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLobby *>(ptr);
    if(typeid(GameLobby).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobby *>(ptr);
    if(typeid(GameLobby).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameRandomKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5040A0C4; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_GameRandomKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_GameRandomKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_GameRandomKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<0, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameRandomKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameRandomKey; }
  void SetDefault() { self.m_GameRandomKey = StormReflTypeInfo<GameLobby>::GetDefault().m_GameRandomKey; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<1>
{
  using member_type = GameLobbySettings; // GameLobbySettings
  static constexpr auto GetName() { return "m_InstanceData"; }
  static constexpr auto GetType() { return "GameLobbySettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEFC069F9; }
  static constexpr unsigned GetTypeNameHash() { return 0x10166A56; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_InstanceData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_InstanceData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_InstanceData; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<1, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameLobbySettings> & Get() { return self.m_InstanceData; }
  std::add_const_t<std::remove_reference_t<GameLobbySettings>> & Get() const { return self.m_InstanceData; }
  void SetDefault() { self.m_InstanceData = StormReflTypeInfo<GameLobby>::GetDefault().m_InstanceData; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxTeams"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83718C91; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_MaxTeams; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_MaxTeams; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_MaxTeams; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<2, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxTeams; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxTeams; }
  void SetDefault() { self.m_MaxTeams = StormReflTypeInfo<GameLobby>::GetDefault().m_MaxTeams; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Creator; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Creator; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Creator; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<3, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Creator; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Creator; }
  void SetDefault() { self.m_Creator = StormReflTypeInfo<GameLobby>::GetDefault().m_Creator; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Server"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1752823E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Server; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Server; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Server; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<4, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Server; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Server; }
  void SetDefault() { self.m_Server = StormReflTypeInfo<GameLobby>::GetDefault().m_Server; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<5>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Started"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2164E30F; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Started; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Started; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Started; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<5, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Started; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Started; }
  void SetDefault() { self.m_Started = StormReflTypeInfo<GameLobby>::GetDefault().m_Started; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<6>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Competive"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x017B6ED9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Competive; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Competive; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Competive; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<6, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Competive; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Competive; }
  void SetDefault() { self.m_Competive = StormReflTypeInfo<GameLobby>::GetDefault().m_Competive; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<7>
{
  using member_type = RMergeList<GameLobbyPlayer>; // RMergeList<GameLobbyPlayer>
  static constexpr auto GetName() { return "m_Players"; }
  static constexpr auto GetType() { return "RMergeList<GameLobbyPlayer>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3BC3673; }
  static constexpr unsigned GetTypeNameHash() { return 0x0B186613; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Players; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Players; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Players; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<7, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<GameLobbyPlayer>> & Get() { return self.m_Players; }
  std::add_const_t<std::remove_reference_t<RMergeList<GameLobbyPlayer>>> & Get() const { return self.m_Players; }
  void SetDefault() { self.m_Players = StormReflTypeInfo<GameLobby>::GetDefault().m_Players; }
};

template <>
struct StormReflTypeInfo<GameLobby>::field_data_static<8>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Score"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBFAFA731; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameLobby::m_Score; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobby *>(obj); return &ptr->m_Score; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobby *>(obj); return &ptr->m_Score; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobby>::field_data<8, Self> : public StormReflTypeInfo<GameLobby>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Score; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Score; }
  void SetDefault() { self.m_Score = StormReflTypeInfo<GameLobby>::GetDefault().m_Score; }
};

template <>
struct StormReflTypeInfo<GameLobbyPrivateData>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLobbyPrivateData"; }
  static constexpr auto GetNameHash() { return 0x01E1537E; }
  static constexpr bool HasDefault() { return true; }
  static GameLobbyPrivateData & GetDefault() { static GameLobbyPrivateData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLobbyPrivateData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbyPrivateData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLobbyPrivateData *>(ptr);
    if(typeid(GameLobbyPrivateData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLobbyPrivateData *>(ptr);
    if(typeid(GameLobbyPrivateData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3EE92FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPrivateData::m_Password; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPrivateData *>(obj); return &ptr->m_Password; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPrivateData *>(obj); return &ptr->m_Password; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data<0, Self> : public StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Password; }
  void SetDefault() { self.m_Password = StormReflTypeInfo<GameLobbyPrivateData>::GetDefault().m_Password; }
};

template <>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<1>
{
  using member_type = std::vector<std::pair<DDSKey, int> >; // std::vector<std::pair<unsigned long, int>, std::allocator<std::pair<unsigned long, int> > >
  static constexpr auto GetName() { return "m_Reservations"; }
  static constexpr auto GetType() { return "std::vector<std::pair<unsigned long, int>, std::allocator<std::pair<unsigned long, int> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7CFDB5F; }
  static constexpr unsigned GetTypeNameHash() { return 0x40F1F69F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPrivateData::m_Reservations; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPrivateData *>(obj); return &ptr->m_Reservations; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPrivateData *>(obj); return &ptr->m_Reservations; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data<1, Self> : public StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<DDSKey, int> >> & Get() { return self.m_Reservations; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<DDSKey, int> >>> & Get() const { return self.m_Reservations; }
  void SetDefault() { self.m_Reservations = StormReflTypeInfo<GameLobbyPrivateData>::GetDefault().m_Reservations; }
};

template <>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_BotId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF33F3584; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPrivateData::m_BotId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPrivateData *>(obj); return &ptr->m_BotId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPrivateData *>(obj); return &ptr->m_BotId; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data<2, Self> : public StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_BotId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_BotId; }
  void SetDefault() { self.m_BotId = StormReflTypeInfo<GameLobbyPrivateData>::GetDefault().m_BotId; }
};

template <>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_BotGameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x036BC989; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameLobbyPrivateData::m_BotGameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLobbyPrivateData *>(obj); return &ptr->m_BotGameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLobbyPrivateData *>(obj); return &ptr->m_BotGameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameLobbyPrivateData>::field_data<3, Self> : public StormReflTypeInfo<GameLobbyPrivateData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_BotGameId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_BotGameId; }
  void SetDefault() { self.m_BotGameId = StormReflTypeInfo<GameLobbyPrivateData>::GetDefault().m_BotGameId; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerConnection"; }
  static constexpr auto GetNameHash() { return 0xE68B80F0; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerConnection *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerConnection *>(ptr);
    if(typeid(GameServerConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerConnection *>(ptr);
    if(typeid(GameServerConnection).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<0>
{
  using member_type = RMergeList<GameLobby>; // RMergeList<GameLobby>
  static constexpr auto GetName() { return "m_GameList"; }
  static constexpr auto GetType() { return "RMergeList<GameLobby>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x44E78937; }
  static constexpr unsigned GetTypeNameHash() { return 0x9C38F56C; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_GameList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_GameList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_GameList; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<0, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<GameLobby>> & Get() { return self.m_GameList; }
  std::add_const_t<std::remove_reference_t<RMergeList<GameLobby>>> & Get() const { return self.m_GameList; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<1>
{
  using member_type = RMergeList<GameLobbyPrivateData>; // RMergeList<GameLobbyPrivateData>
  static constexpr auto GetName() { return "m_GamePrivateData"; }
  static constexpr auto GetType() { return "RMergeList<GameLobbyPrivateData>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87D9456C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F45D3A1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_GamePrivateData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_GamePrivateData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_GamePrivateData; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<1, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<GameLobbyPrivateData>> & Get() { return self.m_GamePrivateData; }
  std::add_const_t<std::remove_reference_t<RMergeList<GameLobbyPrivateData>>> & Get() const { return self.m_GamePrivateData; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<2>
{
  using member_type = std::map<DDSKey, std::tuple<std::size_t, DDSKey, DDSKey, DDSKey> >; // std::map<unsigned long, std::tuple<unsigned long, unsigned long, unsigned long, unsigned long>, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, std::tuple<unsigned long, unsigned long, unsigned long, unsigned long> > > >
  static constexpr auto GetName() { return "m_Tokens"; }
  static constexpr auto GetType() { return "std::map<unsigned long, std::tuple<unsigned long, unsigned long, unsigned long, unsigned long>, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, std::tuple<unsigned long, unsigned long, unsigned long, unsigned long> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7654646; }
  static constexpr unsigned GetTypeNameHash() { return 0x69846018; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_Tokens; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_Tokens; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_Tokens; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<2, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, std::tuple<std::size_t, DDSKey, DDSKey, DDSKey> >> & Get() { return self.m_Tokens; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, std::tuple<std::size_t, DDSKey, DDSKey, DDSKey> >>> & Get() const { return self.m_Tokens; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  using member_type = GameServerConnectionState; // GameServerConnectionState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "GameServerConnectionState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x227BBB92; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<3, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameServerConnectionState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<GameServerConnectionState>> & Get() const { return self.m_State; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_ExpectedChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D8BE64A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ExpectedChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ExpectedChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<4, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ExpectedChallengeResponse; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ExpectedChallengeResponse; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<5, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_RemoteHost"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x345B4DA6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_RemoteHost; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_RemoteHost; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_RemoteHost; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<6, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_RemoteHost; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_RemoteHost; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<7>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_Error; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_Error; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<7, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Error; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x070A2B55; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerName; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<8, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerName; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<9>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerZone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF9C29554; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerZone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerZone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerZone; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<9, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerZone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerZone; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<10>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerResourceId"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x484BB3D8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerResourceId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerResourceId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerResourceId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<10, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerResourceId; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerResourceId; }
};

template <>
struct StormReflTypeInfo<GameServerConnection>::field_data_static<11>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerExternalIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7914B77A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &GameServerConnection::m_ServerExternalIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerConnection *>(obj); return &ptr->m_ServerExternalIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerConnection *>(obj); return &ptr->m_ServerExternalIp; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerConnection>::field_data<11, Self> : public StormReflTypeInfo<GameServerConnection>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerExternalIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerExternalIp; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>
{
  using MyBase = void;
  static constexpr int funcs_n = 18;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>
{
  using func_ptr_type = void (GameServerConnection::*)(std::string);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetRemoteHost"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x570BE899; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SetRemoteHost; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<0>::param_info<0>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "host"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xCF2713FD; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>
{
  using func_ptr_type = void (GameServerConnection::*)(GameServerMessageType, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "GotMessage"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD040732D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::GotMessage; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>::param_info<0>
{
  using param_type = GameServerMessageType;
  static constexpr auto GetName() { return "cmd"; }
  static constexpr auto GetType() { return "GameServerMessageType"; }
  static constexpr unsigned GetNameHash() { return 0x2F5C1CC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x51112183; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<1>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>
{
  using func_ptr_type = void (GameServerConnection::*)(GamePlayerData, std::string, GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "CreateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9EA4204C; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::CreateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>::param_info<0>
{
  using param_type = GamePlayerData;
  static constexpr auto GetName() { return "creator_data"; }
  static constexpr auto GetType() { return "GamePlayerData"; }
  static constexpr unsigned GetNameHash() { return 0xDB7BB2BF; }
  static constexpr unsigned GetTypeNameHash() { return 0x20881F93; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<2>::param_info<2>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "game_creation_data"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xDA61292C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>
{
  using func_ptr_type = void (GameServerConnection::*)(int, GamePlayerData, std::string, bool, bool);
  using return_type = void;
  static constexpr int params_n = 5;
  static constexpr auto GetName() { return "JoinUserToGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x87208673; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::JoinUserToGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<1>
{
  using param_type = GamePlayerData;
  static constexpr auto GetName() { return "user_data"; }
  static constexpr auto GetType() { return "GamePlayerData"; }
  static constexpr unsigned GetNameHash() { return 0xD772BFAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x20881F93; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "observer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x9B6F44E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<3>::param_info<4>
{
  using param_type = bool;
  static constexpr auto GetName() { return "force"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x97688328; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>
{
  using func_ptr_type = void (GameServerConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "DestroyGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x0F26CB52; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::DestroyGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<4>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UserSwitchTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xC5A515B9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::UserSwitchTeams; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<5>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey, int, bool);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "UserSetTeam"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x845151E6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::UserSetTeam; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC4E0A61F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<6>::param_info<3>
{
  using param_type = bool;
  static constexpr auto GetName() { return "force"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x97688328; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<7>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UserLeaveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x38A2B0E9; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::UserLeaveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<7>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<7>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<8>
{
  using func_ptr_type = void (GameServerConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RandomizeTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x26B146D3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::RandomizeTeams; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<8>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<9>
{
  using func_ptr_type = void (GameServerConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "KillGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8E521C27; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::KillGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<9>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<10>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey, DDSKey, GameInitSettings, std::vector<std::tuple<DDSKey, DDSKey, int> >);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "CreateBotGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x699913C0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::CreateBotGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<10>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "bot_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x92C1C487; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<10>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "bot_game_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1B79B420; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<10>::param_info<2>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "game_creation_data"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xDA61292C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<10>::param_info<3>
{
  using param_type = std::vector<std::tuple<DDSKey, DDSKey, int> >;
  static constexpr auto GetName() { return "player_info"; }
  static constexpr auto GetType() { return "std::vector<std::tuple<DDSKey, DDSKey, int> >"; }
  static constexpr unsigned GetNameHash() { return 0x69936164; }
  static constexpr unsigned GetTypeNameHash() { return 0x5534D666; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<11>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendChatToGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x001384B1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SendChatToGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<11>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<11>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<11>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "chat"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x659DF2AA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<12>
{
  using func_ptr_type = void (GameServerConnection::*)(int, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "SendMessageToGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFF300FF5; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SendMessageToGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<12>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<12>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "chat"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x659DF2AA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<13>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<13>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<13>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "game_random_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xF579374E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<13>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "creator_name"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x28AB3FDA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<14>
{
  using func_ptr_type = void (GameServerConnection::*)(int, DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendLaunchGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xCDBB7E33; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SendLaunchGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<14>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<14>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<14>::param_info<2>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<15>
{
  using func_ptr_type = void (GameServerConnection::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ExpireToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6D1B9FA1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::ExpireToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<15>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<16>
{
  using func_ptr_type = void (GameServerConnection::*)(int);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ExpireGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD77948A0; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::ExpireGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<16>::param_info<0>
{
  using param_type = int;
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<GameServerConnection>::func_data_static<17>
{
  using func_ptr_type = void (GameServerConnection::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "SendHangUp"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x5B3418ED; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 17; }
  static constexpr func_ptr_type GetFunctionPtr() { return &GameServerConnection::SendHangUp; }
  template <int i>
  struct param_info { };
};

namespace StormReflFileInfo
{
  struct GameServerConnection
  {
    static const int types_n = 5;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameServerConnection::type_info<0>
  {
    using type = ::GameLobbySettings;
  };

  template <>
  struct GameServerConnection::type_info<1>
  {
    using type = ::GameLobbyPlayer;
  };

  template <>
  struct GameServerConnection::type_info<2>
  {
    using type = ::GameLobby;
  };

  template <>
  struct GameServerConnection::type_info<3>
  {
    using type = ::GameLobbyPrivateData;
  };

  template <>
  struct GameServerConnection::type_info<4>
  {
    using type = ::GameServerConnection;
  };

}

