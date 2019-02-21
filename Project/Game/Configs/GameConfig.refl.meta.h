#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameConfig.refl.h"


template <>
struct StormReflTypeInfo<GameConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameConfig"; }
  static constexpr auto GetNameHash() { return 0x2470BC89; }
  static constexpr bool HasDefault() { return true; }
  static GameConfig & GetDefault() { static GameConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameConfig *>(ptr);
    if(typeid(GameConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameConfig *>(ptr);
    if(typeid(GameConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct GameConfig
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameConfig::type_info<0>
  {
    using type = ::GameConfig;
  };

}

