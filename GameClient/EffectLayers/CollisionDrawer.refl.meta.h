#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "CollisionDrawer.refl.h"
#include "Runtime/Map/MapEffectLayerDef.refl.meta.h"


template <>
struct StormReflTypeInfo<CollisionDrawerInitData>
{
  using MyBase = MapEffectLayerInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "CollisionDrawerInitData"; }
  static constexpr auto GetNameHash() { return 0x46FFA8DB; }
  static CollisionDrawerInitData & GetDefault() { static CollisionDrawerInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<CollisionDrawerInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x14A370F8 == type_name_hash) return static_cast<MapEffectLayerInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const CollisionDrawerInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x14A370F8 == type_name_hash) return static_cast<const MapEffectLayerInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<CollisionDrawerInitData *>(ptr);
    if(typeid(CollisionDrawerInitData).hash_code() == type_id_hash) return c;
    if(typeid(MapEffectLayerInitData).hash_code() == type_id_hash) return static_cast<MapEffectLayerInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const CollisionDrawerInitData *>(ptr);
    if(typeid(CollisionDrawerInitData).hash_code() == type_id_hash) return c;
    if(typeid(MapEffectLayerInitData).hash_code() == type_id_hash) return static_cast<const MapEffectLayerInitData *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct CollisionDrawer
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct CollisionDrawer::type_info<0>
  {
    using type = ::CollisionDrawerInitData;
  };

}

