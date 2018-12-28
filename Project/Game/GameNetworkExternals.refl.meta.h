#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameNetworkExternals.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


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
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerJoinedEvent *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerJoinedEvent *>(obj); return &ptr->m_UserName; }
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
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerJoinedEvent *>(obj); return &ptr->m_RandomSeed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerJoinedEvent *>(obj); return &ptr->m_RandomSeed; }
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
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerJoinedEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerJoinedEvent *>(obj); return &ptr->m_PlayerIndex; }
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
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerLeaveEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerLeaveEvent *>(obj); return &ptr->m_PlayerIndex; }
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

template <>
struct StormReflTypeInfo<ObserverJoinedEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ObserverJoinedEvent"; }
  static constexpr auto GetNameHash() { return 0x72605784; }
  static ObserverJoinedEvent & GetDefault() { static ObserverJoinedEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ObserverJoinedEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ObserverJoinedEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ObserverJoinedEvent *>(ptr);
    if(typeid(ObserverJoinedEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ObserverJoinedEvent *>(ptr);
    if(typeid(ObserverJoinedEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ObserverJoinedEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ObserverJoinedEvent::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ObserverJoinedEvent *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ObserverJoinedEvent *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<ObserverJoinedEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ObserverJoinedEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<ObserverJoinedEvent>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<ObserverJoinedEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ObserverJoinedEvent::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ObserverJoinedEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ObserverJoinedEvent *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ObserverJoinedEvent>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ObserverJoinedEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ObserverJoinedEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ObserverLeaveEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ObserverLeaveEvent"; }
  static constexpr auto GetNameHash() { return 0x69772E32; }
  static ObserverLeaveEvent & GetDefault() { static ObserverLeaveEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ObserverLeaveEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ObserverLeaveEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ObserverLeaveEvent *>(ptr);
    if(typeid(ObserverLeaveEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ObserverLeaveEvent *>(ptr);
    if(typeid(ObserverLeaveEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ObserverLeaveEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ObserverLeaveEvent::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ObserverLeaveEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ObserverLeaveEvent *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ObserverLeaveEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ObserverLeaveEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ObserverLeaveEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangePlayerNameEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangePlayerNameEvent"; }
  static constexpr auto GetNameHash() { return 0x3BCFA3CA; }
  static ChangePlayerNameEvent & GetDefault() { static ChangePlayerNameEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerNameEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerNameEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerNameEvent *>(ptr);
    if(typeid(ChangePlayerNameEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerNameEvent *>(ptr);
    if(typeid(ChangePlayerNameEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangePlayerNameEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerNameEvent::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerNameEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerNameEvent *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerNameEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerNameEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangePlayerNameEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangePlayerNameEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerNameEvent::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerNameEvent *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerNameEvent *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerNameEvent>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerNameEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChangePlayerNameEvent>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChangeObserverNameEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangeObserverNameEvent"; }
  static constexpr auto GetNameHash() { return 0x6E0F4FD2; }
  static ChangeObserverNameEvent & GetDefault() { static ChangeObserverNameEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangeObserverNameEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeObserverNameEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangeObserverNameEvent *>(ptr);
    if(typeid(ChangeObserverNameEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeObserverNameEvent *>(ptr);
    if(typeid(ChangeObserverNameEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangeObserverNameEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_ObserverIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA780578; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverNameEvent::m_ObserverIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverNameEvent *>(obj); return &ptr->m_ObserverIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverNameEvent *>(obj); return &ptr->m_ObserverIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverNameEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverNameEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_ObserverIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_ObserverIndex; }
  void SetDefault() { self.m_ObserverIndex = StormReflTypeInfo<ChangeObserverNameEvent>::GetDefault().m_ObserverIndex; }
};

template <>
struct StormReflTypeInfo<ChangeObserverNameEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverNameEvent::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverNameEvent *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverNameEvent *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverNameEvent>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverNameEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChangeObserverNameEvent>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 5 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangeObserverToPlayer"; }
  static constexpr auto GetNameHash() { return 0x539E4662; }
  static ChangeObserverToPlayer & GetDefault() { static ChangeObserverToPlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangeObserverToPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeObserverToPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangeObserverToPlayer *>(ptr);
    if(typeid(ChangeObserverToPlayer).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeObserverToPlayer *>(ptr);
    if(typeid(ChangeObserverToPlayer).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_ObserverIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA780578; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverToPlayer::m_ObserverIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverToPlayer *>(obj); return &ptr->m_ObserverIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverToPlayer *>(obj); return &ptr->m_ObserverIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_ObserverIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_ObserverIndex; }
  void SetDefault() { self.m_ObserverIndex = StormReflTypeInfo<ChangeObserverToPlayer>::GetDefault().m_ObserverIndex; }
};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverToPlayer::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverToPlayer *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverToPlayer *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangeObserverToPlayer>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = GamePlayerLoadout; // GamePlayerLoadout
  static constexpr auto GetName() { return "m_Loadout"; }
  static constexpr auto GetType() { return "GamePlayerLoadout"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB97BB97; }
  static constexpr unsigned GetTypeNameHash() { return 0xFEBDA94B; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverToPlayer::m_Loadout; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverToPlayer *>(obj); return &ptr->m_Loadout; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverToPlayer *>(obj); return &ptr->m_Loadout; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<2 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GamePlayerLoadout> & Get() { return self.m_Loadout; }
  std::add_const_t<std::remove_reference_t<GamePlayerLoadout>> & Get() const { return self.m_Loadout; }
  void SetDefault() { self.m_Loadout = StormReflTypeInfo<ChangeObserverToPlayer>::GetDefault().m_Loadout; }
};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<3 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, kMaxTeams - 1>; // NetRangedNumber<int, 0, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0xAAFE6A4F; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverToPlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverToPlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverToPlayer *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data<3 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<3 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<ChangeObserverToPlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<4 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_RandomSeed"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x37FE06D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeObserverToPlayer::m_RandomSeed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeObserverToPlayer *>(obj); return &ptr->m_RandomSeed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeObserverToPlayer *>(obj); return &ptr->m_RandomSeed; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeObserverToPlayer>::field_data<4 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeObserverToPlayer>::field_data_static<4 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_RandomSeed; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_RandomSeed; }
  void SetDefault() { self.m_RandomSeed = StormReflTypeInfo<ChangeObserverToPlayer>::GetDefault().m_RandomSeed; }
};

template <>
struct StormReflTypeInfo<ChangePlayerToObserver>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangePlayerToObserver"; }
  static constexpr auto GetNameHash() { return 0xE8783D9A; }
  static ChangePlayerToObserver & GetDefault() { static ChangePlayerToObserver def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerToObserver *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerToObserver *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerToObserver *>(ptr);
    if(typeid(ChangePlayerToObserver).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerToObserver *>(ptr);
    if(typeid(ChangePlayerToObserver).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangePlayerToObserver>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_ObserverIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA780578; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerToObserver::m_ObserverIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerToObserver *>(obj); return &ptr->m_ObserverIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerToObserver *>(obj); return &ptr->m_ObserverIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerToObserver>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerToObserver>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_ObserverIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_ObserverIndex; }
  void SetDefault() { self.m_ObserverIndex = StormReflTypeInfo<ChangePlayerToObserver>::GetDefault().m_ObserverIndex; }
};

template <>
struct StormReflTypeInfo<ChangePlayerToObserver>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerToObserver::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerToObserver *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerToObserver *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerToObserver>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerToObserver>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangePlayerToObserver>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangePlayerTeam>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangePlayerTeam"; }
  static constexpr auto GetNameHash() { return 0x067BBD2B; }
  static ChangePlayerTeam & GetDefault() { static ChangePlayerTeam def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerTeam *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerTeam *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangePlayerTeam *>(ptr);
    if(typeid(ChangePlayerTeam).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangePlayerTeam *>(ptr);
    if(typeid(ChangePlayerTeam).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangePlayerTeam>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerTeam::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerTeam *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerTeam *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerTeam>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerTeam>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangePlayerTeam>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangePlayerTeam>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, kMaxTeams - 1>; // NetRangedNumber<int, 0, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0xAAFE6A4F; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangePlayerTeam::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangePlayerTeam *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangePlayerTeam *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<ChangePlayerTeam>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangePlayerTeam>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<ChangePlayerTeam>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<ChangeLoadoutEvent>
{
  using MyBase = GameNetworkExternalEvent;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ChangeLoadoutEvent"; }
  static constexpr auto GetNameHash() { return 0xB2C78060; }
  static ChangeLoadoutEvent & GetDefault() { static ChangeLoadoutEvent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChangeLoadoutEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeLoadoutEvent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xDD637770 == type_name_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChangeLoadoutEvent *>(ptr);
    if(typeid(ChangeLoadoutEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<GameNetworkExternalEvent *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChangeLoadoutEvent *>(ptr);
    if(typeid(ChangeLoadoutEvent).hash_code() == type_id_hash) return c;
    if(typeid(GameNetworkExternalEvent).hash_code() == type_id_hash) return static_cast<const GameNetworkExternalEvent *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChangeLoadoutEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_PlayerIndex"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5BD26FC9; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeLoadoutEvent::m_PlayerIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeLoadoutEvent *>(obj); return &ptr->m_PlayerIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeLoadoutEvent *>(obj); return &ptr->m_PlayerIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeLoadoutEvent>::field_data<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeLoadoutEvent>::field_data_static<0 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_PlayerIndex; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_PlayerIndex; }
  void SetDefault() { self.m_PlayerIndex = StormReflTypeInfo<ChangeLoadoutEvent>::GetDefault().m_PlayerIndex; }
};

template <>
struct StormReflTypeInfo<ChangeLoadoutEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  using member_type = GamePlayerLoadout; // GamePlayerLoadout
  static constexpr auto GetName() { return "m_Loadout"; }
  static constexpr auto GetType() { return "GamePlayerLoadout"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB97BB97; }
  static constexpr unsigned GetTypeNameHash() { return 0xFEBDA94B; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ChangeLoadoutEvent::m_Loadout; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChangeLoadoutEvent *>(obj); return &ptr->m_Loadout; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChangeLoadoutEvent *>(obj); return &ptr->m_Loadout; }
};

template <typename Self>
struct StormReflTypeInfo<ChangeLoadoutEvent>::field_data<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n, Self> : public StormReflTypeInfo<ChangeLoadoutEvent>::field_data_static<1 + StormReflTypeInfo<GameNetworkExternalEvent>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GamePlayerLoadout> & Get() { return self.m_Loadout; }
  std::add_const_t<std::remove_reference_t<GamePlayerLoadout>> & Get() const { return self.m_Loadout; }
  void SetDefault() { self.m_Loadout = StormReflTypeInfo<ChangeLoadoutEvent>::GetDefault().m_Loadout; }
};

namespace StormReflFileInfo
{
  struct GameNetworkExternals
  {
    static const int types_n = 11;
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

  template <>
  struct GameNetworkExternals::type_info<3>
  {
    using type = ::ObserverJoinedEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<4>
  {
    using type = ::ObserverLeaveEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<5>
  {
    using type = ::ChangePlayerNameEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<6>
  {
    using type = ::ChangeObserverNameEvent;
  };

  template <>
  struct GameNetworkExternals::type_info<7>
  {
    using type = ::ChangeObserverToPlayer;
  };

  template <>
  struct GameNetworkExternals::type_info<8>
  {
    using type = ::ChangePlayerToObserver;
  };

  template <>
  struct GameNetworkExternals::type_info<9>
  {
    using type = ::ChangePlayerTeam;
  };

  template <>
  struct GameNetworkExternals::type_info<10>
  {
    using type = ::ChangeLoadoutEvent;
  };

}

