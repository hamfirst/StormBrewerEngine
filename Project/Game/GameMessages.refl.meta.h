#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameMessages.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<FromServerMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "FromServerMessage"; }
  static constexpr auto GetNameHash() { return 0x038F16E6; }
  static constexpr bool HasDefault() { return true; }
  static FromServerMessage & GetDefault() { static FromServerMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<FromServerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const FromServerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<FromServerMessage *>(ptr);
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const FromServerMessage *>(ptr);
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<LoadLevelMessage>
{
  using MyBase = FromServerMessage;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "LoadLevelMessage"; }
  static constexpr auto GetNameHash() { return 0x36A8A4D8; }
  static constexpr bool HasDefault() { return true; }
  static LoadLevelMessage & GetDefault() { static LoadLevelMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<LoadLevelMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const LoadLevelMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<LoadLevelMessage *>(ptr);
    if(typeid(LoadLevelMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const LoadLevelMessage *>(ptr);
    if(typeid(LoadLevelMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<LoadLevelMessage>::field_data_static<0 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<FromServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &LoadLevelMessage::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LoadLevelMessage *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LoadLevelMessage *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<LoadLevelMessage>::field_data<0 + StormReflTypeInfo<FromServerMessage>::fields_n, Self> : public StormReflTypeInfo<LoadLevelMessage>::field_data_static<0 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<LoadLevelMessage>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<LoadLevelMessage>::field_data_static<1 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_LoadToken"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6FC5862D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<FromServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &LoadLevelMessage::m_LoadToken; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LoadLevelMessage *>(obj); return &ptr->m_LoadToken; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LoadLevelMessage *>(obj); return &ptr->m_LoadToken; }
};

template <typename Self>
struct StormReflTypeInfo<LoadLevelMessage>::field_data<1 + StormReflTypeInfo<FromServerMessage>::fields_n, Self> : public StormReflTypeInfo<LoadLevelMessage>::field_data_static<1 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_LoadToken; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_LoadToken; }
  void SetDefault() { self.m_LoadToken = StormReflTypeInfo<LoadLevelMessage>::GetDefault().m_LoadToken; }
};

template <>
struct StormReflTypeInfo<PongMessage>
{
  using MyBase = FromServerMessage;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PongMessage"; }
  static constexpr auto GetNameHash() { return 0x9936163C; }
  static constexpr bool HasDefault() { return true; }
  static PongMessage & GetDefault() { static PongMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PongMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PongMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PongMessage *>(ptr);
    if(typeid(PongMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PongMessage *>(ptr);
    if(typeid(PongMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GotTextChatMessage>
{
  using MyBase = FromServerMessage;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GotTextChatMessage"; }
  static constexpr auto GetNameHash() { return 0x435CBC01; }
  static constexpr bool HasDefault() { return true; }
  static GotTextChatMessage & GetDefault() { static GotTextChatMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GotTextChatMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GotTextChatMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x038F16E6 == type_name_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GotTextChatMessage *>(ptr);
    if(typeid(GotTextChatMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<FromServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GotTextChatMessage *>(ptr);
    if(typeid(GotTextChatMessage).hash_code() == type_id_hash) return c;
    if(typeid(FromServerMessage).hash_code() == type_id_hash) return static_cast<const FromServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GotTextChatMessage>::field_data_static<0 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<FromServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &GotTextChatMessage::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GotTextChatMessage *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GotTextChatMessage *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GotTextChatMessage>::field_data<0 + StormReflTypeInfo<FromServerMessage>::fields_n, Self> : public StormReflTypeInfo<GotTextChatMessage>::field_data_static<0 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GotTextChatMessage>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GotTextChatMessage>::field_data_static<1 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x234F45AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<FromServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &GotTextChatMessage::m_Message; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GotTextChatMessage *>(obj); return &ptr->m_Message; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GotTextChatMessage *>(obj); return &ptr->m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<GotTextChatMessage>::field_data<1 + StormReflTypeInfo<FromServerMessage>::fields_n, Self> : public StormReflTypeInfo<GotTextChatMessage>::field_data_static<1 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<GotTextChatMessage>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<GotTextChatMessage>::field_data_static<2 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 1>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 1>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x01BCAC65; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<FromServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &GotTextChatMessage::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GotTextChatMessage *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GotTextChatMessage *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GotTextChatMessage>::field_data<2 + StormReflTypeInfo<FromServerMessage>::fields_n, Self> : public StormReflTypeInfo<GotTextChatMessage>::field_data_static<2 + StormReflTypeInfo<FromServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GotTextChatMessage>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<ToServerMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ToServerMessage"; }
  static constexpr auto GetNameHash() { return 0x4C3A63B8; }
  static constexpr bool HasDefault() { return true; }
  static ToServerMessage & GetDefault() { static ToServerMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ToServerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ToServerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ToServerMessage *>(ptr);
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ToServerMessage *>(ptr);
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PingMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PingMessage"; }
  static constexpr auto GetNameHash() { return 0x9428667B; }
  static constexpr bool HasDefault() { return true; }
  static PingMessage & GetDefault() { static PingMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PingMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PingMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PingMessage *>(ptr);
    if(typeid(PingMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PingMessage *>(ptr);
    if(typeid(PingMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameJoinInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameJoinInfo"; }
  static constexpr auto GetNameHash() { return 0x1A3CAE21; }
  static constexpr bool HasDefault() { return true; }
  static GameJoinInfo & GetDefault() { static GameJoinInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameJoinInfo *>(ptr);
    if(typeid(GameJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameJoinInfo *>(ptr);
    if(typeid(GameJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameJoinInfo>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameJoinInfo::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameJoinInfo *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameJoinInfo *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<GameJoinInfo>::field_data<0, Self> : public StormReflTypeInfo<GameJoinInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<GameJoinInfo>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<GameJoinInfo>::field_data_static<1>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameJoinInfo::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameJoinInfo *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameJoinInfo *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<GameJoinInfo>::field_data<1, Self> : public StormReflTypeInfo<GameJoinInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<GameJoinInfo>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<CreatePrivateGameMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "CreatePrivateGameMessage"; }
  static constexpr auto GetNameHash() { return 0x38033229; }
  static constexpr bool HasDefault() { return true; }
  static CreatePrivateGameMessage & GetDefault() { static CreatePrivateGameMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<CreatePrivateGameMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const CreatePrivateGameMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<CreatePrivateGameMessage *>(ptr);
    if(typeid(CreatePrivateGameMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const CreatePrivateGameMessage *>(ptr);
    if(typeid(CreatePrivateGameMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<CreatePrivateGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = GameJoinInfo; // GameJoinInfo
  static constexpr auto GetName() { return "m_JoinInfo"; }
  static constexpr auto GetType() { return "GameJoinInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xECDD5DF3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1A3CAE21; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &CreatePrivateGameMessage::m_JoinInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<CreatePrivateGameMessage *>(obj); return &ptr->m_JoinInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const CreatePrivateGameMessage *>(obj); return &ptr->m_JoinInfo; }
};

template <typename Self>
struct StormReflTypeInfo<CreatePrivateGameMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<CreatePrivateGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameJoinInfo> & Get() { return self.m_JoinInfo; }
  std::add_const_t<std::remove_reference_t<GameJoinInfo>> & Get() const { return self.m_JoinInfo; }
  void SetDefault() { self.m_JoinInfo = StormReflTypeInfo<CreatePrivateGameMessage>::GetDefault().m_JoinInfo; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "JoinGameMessage"; }
  static constexpr auto GetNameHash() { return 0xF8762C60; }
  static constexpr bool HasDefault() { return true; }
  static JoinGameMessage & GetDefault() { static JoinGameMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<JoinGameMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const JoinGameMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<JoinGameMessage *>(ptr);
    if(typeid(JoinGameMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const JoinGameMessage *>(ptr);
    if(typeid(JoinGameMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<JoinGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_PrivateRoomId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA1CFF09F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &JoinGameMessage::m_PrivateRoomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<JoinGameMessage *>(obj); return &ptr->m_PrivateRoomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const JoinGameMessage *>(obj); return &ptr->m_PrivateRoomId; }
};

template <typename Self>
struct StormReflTypeInfo<JoinGameMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<JoinGameMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_PrivateRoomId; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_PrivateRoomId; }
  void SetDefault() { self.m_PrivateRoomId = StormReflTypeInfo<JoinGameMessage>::GetDefault().m_PrivateRoomId; }
};

template <>
struct StormReflTypeInfo<JoinGameMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = GameJoinInfo; // GameJoinInfo
  static constexpr auto GetName() { return "m_JoinInfo"; }
  static constexpr auto GetType() { return "GameJoinInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xECDD5DF3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1A3CAE21; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &JoinGameMessage::m_JoinInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<JoinGameMessage *>(obj); return &ptr->m_JoinInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const JoinGameMessage *>(obj); return &ptr->m_JoinInfo; }
};

template <typename Self>
struct StormReflTypeInfo<JoinGameMessage>::field_data<1 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<JoinGameMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameJoinInfo> & Get() { return self.m_JoinInfo; }
  std::add_const_t<std::remove_reference_t<GameJoinInfo>> & Get() const { return self.m_JoinInfo; }
  void SetDefault() { self.m_JoinInfo = StormReflTypeInfo<JoinGameMessage>::GetDefault().m_JoinInfo; }
};

template <>
struct StormReflTypeInfo<ReadyMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ReadyMessage"; }
  static constexpr auto GetNameHash() { return 0xE2CFDB46; }
  static constexpr bool HasDefault() { return true; }
  static ReadyMessage & GetDefault() { static ReadyMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ReadyMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ReadyMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ReadyMessage *>(ptr);
    if(typeid(ReadyMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ReadyMessage *>(ptr);
    if(typeid(ReadyMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ReadyMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5A315CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ReadyMessage::m_Ready; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ReadyMessage *>(obj); return &ptr->m_Ready; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ReadyMessage *>(obj); return &ptr->m_Ready; }
};

template <typename Self>
struct StormReflTypeInfo<ReadyMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<ReadyMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Ready; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Ready; }
  void SetDefault() { self.m_Ready = StormReflTypeInfo<ReadyMessage>::GetDefault().m_Ready; }
};

template <>
struct StormReflTypeInfo<KickPlayerMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "KickPlayerMessage"; }
  static constexpr auto GetNameHash() { return 0xF686ED9D; }
  static constexpr bool HasDefault() { return true; }
  static KickPlayerMessage & GetDefault() { static KickPlayerMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<KickPlayerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const KickPlayerMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<KickPlayerMessage *>(ptr);
    if(typeid(KickPlayerMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const KickPlayerMessage *>(ptr);
    if(typeid(KickPlayerMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<KickPlayerMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &KickPlayerMessage::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<KickPlayerMessage *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const KickPlayerMessage *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<KickPlayerMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<KickPlayerMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<KickPlayerMessage>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<FinishLoadingMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "FinishLoadingMessage"; }
  static constexpr auto GetNameHash() { return 0x0A4980F3; }
  static constexpr bool HasDefault() { return true; }
  static FinishLoadingMessage & GetDefault() { static FinishLoadingMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<FinishLoadingMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const FinishLoadingMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<FinishLoadingMessage *>(ptr);
    if(typeid(FinishLoadingMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const FinishLoadingMessage *>(ptr);
    if(typeid(FinishLoadingMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<FinishLoadingMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_LoadToken"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6FC5862D; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &FinishLoadingMessage::m_LoadToken; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<FinishLoadingMessage *>(obj); return &ptr->m_LoadToken; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const FinishLoadingMessage *>(obj); return &ptr->m_LoadToken; }
};

template <typename Self>
struct StormReflTypeInfo<FinishLoadingMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<FinishLoadingMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_LoadToken; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_LoadToken; }
  void SetDefault() { self.m_LoadToken = StormReflTypeInfo<FinishLoadingMessage>::GetDefault().m_LoadToken; }
};

template <>
struct StormReflTypeInfo<SendTextChatMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "SendTextChatMessage"; }
  static constexpr auto GetNameHash() { return 0x3A40CDC6; }
  static constexpr bool HasDefault() { return true; }
  static SendTextChatMessage & GetDefault() { static SendTextChatMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SendTextChatMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SendTextChatMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SendTextChatMessage *>(ptr);
    if(typeid(SendTextChatMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SendTextChatMessage *>(ptr);
    if(typeid(SendTextChatMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SendTextChatMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x234F45AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &SendTextChatMessage::m_Message; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SendTextChatMessage *>(obj); return &ptr->m_Message; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SendTextChatMessage *>(obj); return &ptr->m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<SendTextChatMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<SendTextChatMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<SendTextChatMessage>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<SendTextChatMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_TeamOnly"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA13FDB1E; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &SendTextChatMessage::m_TeamOnly; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SendTextChatMessage *>(obj); return &ptr->m_TeamOnly; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SendTextChatMessage *>(obj); return &ptr->m_TeamOnly; }
};

template <typename Self>
struct StormReflTypeInfo<SendTextChatMessage>::field_data<1 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<SendTextChatMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_TeamOnly; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_TeamOnly; }
  void SetDefault() { self.m_TeamOnly = StormReflTypeInfo<SendTextChatMessage>::GetDefault().m_TeamOnly; }
};

template <>
struct StormReflTypeInfo<ChangeLoadoutMessage>
{
  using MyBase = ToServerMessage;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangeLoadoutMessage"; }
  static constexpr auto GetNameHash() { return 0x3F6B92A1; }
  static constexpr bool HasDefault() { return true; }
  static ChangeLoadoutMessage & GetDefault() { static ChangeLoadoutMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangeLoadoutMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeLoadoutMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4C3A63B8 == type_name_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangeLoadoutMessage *>(ptr);
    if(typeid(ChangeLoadoutMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<ToServerMessage *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeLoadoutMessage *>(ptr);
    if(typeid(ChangeLoadoutMessage).hash_code() == type_id_hash) return c;
    if(typeid(ToServerMessage).hash_code() == type_id_hash) return static_cast<const ToServerMessage *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangeLoadoutMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeLoadoutMessage::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeLoadoutMessage *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeLoadoutMessage *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeLoadoutMessage>::field_data<0 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<ChangeLoadoutMessage>::field_data_static<0 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangeLoadoutMessage>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangeLoadoutMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  using member_type = GamePlayerLoadout; // GamePlayerLoadout
  static constexpr auto GetName() { return "m_Loadout"; }
  static constexpr auto GetType() { return "GamePlayerLoadout"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB97BB97; }
  static constexpr unsigned GetTypeNameHash() { return 0xFEBDA94B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ToServerMessage>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeLoadoutMessage::m_Loadout; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeLoadoutMessage *>(obj); return &ptr->m_Loadout; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeLoadoutMessage *>(obj); return &ptr->m_Loadout; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeLoadoutMessage>::field_data<1 + StormReflTypeInfo<ToServerMessage>::fields_n, Self> : public StormReflTypeInfo<ChangeLoadoutMessage>::field_data_static<1 + StormReflTypeInfo<ToServerMessage>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GamePlayerLoadout> & Get() { return self.m_Loadout; }
  std::add_const_t<std::remove_reference_t<GamePlayerLoadout>> & Get() const { return self.m_Loadout; }
  void SetDefault() { self.m_Loadout = StormReflTypeInfo<ChangeLoadoutMessage>::GetDefault().m_Loadout; }
};

namespace StormReflFileInfo
{
  struct GameMessages
  {
    static const int types_n = 14;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameMessages::type_info<0>
  {
    using type = ::FromServerMessage;
  };

  template <>
  struct GameMessages::type_info<1>
  {
    using type = ::LoadLevelMessage;
  };

  template <>
  struct GameMessages::type_info<2>
  {
    using type = ::PongMessage;
  };

  template <>
  struct GameMessages::type_info<3>
  {
    using type = ::GotTextChatMessage;
  };

  template <>
  struct GameMessages::type_info<4>
  {
    using type = ::ToServerMessage;
  };

  template <>
  struct GameMessages::type_info<5>
  {
    using type = ::PingMessage;
  };

  template <>
  struct GameMessages::type_info<6>
  {
    using type = ::GameJoinInfo;
  };

  template <>
  struct GameMessages::type_info<7>
  {
    using type = ::CreatePrivateGameMessage;
  };

  template <>
  struct GameMessages::type_info<8>
  {
    using type = ::JoinGameMessage;
  };

  template <>
  struct GameMessages::type_info<9>
  {
    using type = ::ReadyMessage;
  };

  template <>
  struct GameMessages::type_info<10>
  {
    using type = ::KickPlayerMessage;
  };

  template <>
  struct GameMessages::type_info<11>
  {
    using type = ::FinishLoadingMessage;
  };

  template <>
  struct GameMessages::type_info<12>
  {
    using type = ::SendTextChatMessage;
  };

  template <>
  struct GameMessages::type_info<13>
  {
    using type = ::ChangeLoadoutMessage;
  };

}

