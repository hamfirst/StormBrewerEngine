#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "TileSheetDef.refl.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.meta.h"


template <>
struct StormReflTypeInfo<TileSheetDef>
{
  using MyBase = SpriteBaseDef;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "TileSheetDef"; }
  static constexpr auto GetNameHash() { return 0xF790F69F; }
  static TileSheetDef & GetDefault() { static TileSheetDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<TileSheetDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x48F83F55 == type_name_hash) return static_cast<SpriteBaseDef *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const TileSheetDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x48F83F55 == type_name_hash) return static_cast<const SpriteBaseDef *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<TileSheetDef *>(ptr);
    if(typeid(TileSheetDef).hash_code() == type_id_hash) return c;
    if(typeid(SpriteBaseDef).hash_code() == type_id_hash) return static_cast<SpriteBaseDef *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const TileSheetDef *>(ptr);
    if(typeid(TileSheetDef).hash_code() == type_id_hash) return c;
    if(typeid(SpriteBaseDef).hash_code() == type_id_hash) return static_cast<const SpriteBaseDef *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct TileSheetDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct TileSheetDef::type_info<0>
  {
    using type = ::TileSheetDef;
  };

}

