#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerSpawn.refl.h"
#include "Runtime/Anchor/AnchorDef.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerSpawn>
{
  using MyBase = AnchorDataBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerSpawn"; }
  static constexpr auto GetNameHash() { return 0x286C4F1C; }
  static constexpr bool HasDefault() { return true; }
  static PlayerSpawn & GetDefault() { static PlayerSpawn def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerSpawn *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x474FD0AA == type_name_hash) return static_cast<AnchorDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerSpawn *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x474FD0AA == type_name_hash) return static_cast<const AnchorDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerSpawn *>(ptr);
    if(typeid(PlayerSpawn).hash_code() == type_id_hash) return c;
    if(typeid(AnchorDataBase).hash_code() == type_id_hash) return static_cast<AnchorDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerSpawn *>(ptr);
    if(typeid(PlayerSpawn).hash_code() == type_id_hash) return c;
    if(typeid(AnchorDataBase).hash_code() == type_id_hash) return static_cast<const AnchorDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerSpawn>::field_data_static<0 + StormReflTypeInfo<AnchorDataBase>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<AnchorDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerSpawn::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerSpawn *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerSpawn *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerSpawn>::field_data<0 + StormReflTypeInfo<AnchorDataBase>::fields_n, Self> : public StormReflTypeInfo<PlayerSpawn>::field_data_static<0 + StormReflTypeInfo<AnchorDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<PlayerSpawn>::GetDefault().m_Team; }
};

namespace StormReflFileInfo
{
  struct PlayerSpawn
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerSpawn::type_info<0>
  {
    using type = ::PlayerSpawn;
  };

}

