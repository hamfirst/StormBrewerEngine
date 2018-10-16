#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkExternals.refl.h"


template <>
struct StormReflTypeInfo<GameNetworkExternalEvent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameNetworkExternalEvent"; }
  static constexpr auto GetNameHash() { return 0xDD637770; }
  static GameNetworkExternalEvent & GetDefault() { static GameNetworkExternalEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameNetworkExternalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameNetworkExternalEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameNetworkExternalEvent *>(ptr);
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameNetworkExternalEvent *>(ptr);
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerJoinedEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerJoinedEvent"; }
  static constexpr auto GetNameHash() { return 0x2EC69003; }
  static PlayerJoinedEvent & GetDefault() { static PlayerJoinedEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerJoinedEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerJoinedEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerJoinedEvent *>(ptr);
    if(typeid(PlayerJoinedEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerJoinedEvent *>(ptr);
    if(typeid(PlayerJoinedEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerJoinedEvent::m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<PlayerJoinedEvent>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_RandomSeed"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x37FE06D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerJoinedEvent::m_RandomSeed; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_RandomSeed; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_RandomSeed; }
  void SetDefault() { self.m_RandomSeed = StormReflTypeInfo<PlayerJoinedEvent>::GetDefault().m_RandomSeed; }
};

template <>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerJoinedEvent::m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerJoinedEvent>::field_data<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<PlayerJoinedEvent>::field_data_static<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<PlayerJoinedEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<PlayerLeaveEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerLeaveEvent"; }
  static constexpr auto GetNameHash() { return 0x7CDAAD89; }
  static PlayerLeaveEvent & GetDefault() { static PlayerLeaveEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerLeaveEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerLeaveEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerLeaveEvent *>(ptr);
    if(typeid(PlayerLeaveEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerLeaveEvent *>(ptr);
    if(typeid(PlayerLeaveEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerLeaveEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerLeaveEvent::m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerLeaveEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<PlayerLeaveEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<PlayerLeaveEvent>::GetDefault().m_PlayerIndex; }
};

namespace StormReflFileInfo
{
  struct GameNetworkExternals
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameNetworkExternals::type_info<0>
  {
    using type = ::GameNetworkExternalEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<1>
  {
    using type = ::PlayerJoinedEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<2>
  {
    using type = ::PlayerLeaveEvent;
  };

}

