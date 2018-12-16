#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateBase.refl.h"
#include "Game/Configs/PlayerConfig.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerStateBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerStateBase"; }
  static constexpr auto GetNameHash() { return 0x887CB291; }
  static PlayerStateBase & GetDefault() { static PlayerStateBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBase *>(ptr);
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBase *>(ptr);
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflFuncInfo<PlayerStateBase>
{
  using MyBase = void;
  static constexpr int funcs_n = 0;
  template <int N> struct func_data_static {};
};

namespace StormReflFileInfo
{
  struct PlayerStateBase
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateBase::type_info<0>
  {
    using type = ::PlayerStateBase;
  };

}

