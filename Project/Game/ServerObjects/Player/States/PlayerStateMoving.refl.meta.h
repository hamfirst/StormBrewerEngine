#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateMoving.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerStateMoving>
{
  using MyBase = PlayerStateBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerStateMoving"; }
  static constexpr auto GetNameHash() { return 0x54E64448; }
  static PlayerStateMoving & GetDefault() { static PlayerStateMoving def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateMoving *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<PlayerStateEventHandler<PlayerStateMoving> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateMoving *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<const PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<const PlayerStateEventHandler<PlayerStateMoving> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateMoving *>(ptr);
    if(typeid(PlayerStateMoving).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateMoving>).hash_code() == type_id_hash) return static_cast<PlayerStateEventHandler<PlayerStateMoving> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateMoving *>(ptr);
    if(typeid(PlayerStateMoving).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<const PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateMoving>).hash_code() == type_id_hash) return static_cast<const PlayerStateEventHandler<PlayerStateMoving> *>(c);
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<PlayerStateMoving>
{
  using MyBase = PlayerStateBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct PlayerStateMoving
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateMoving::type_info<0>
  {
    using type = ::PlayerStateMoving;
  };

}

