#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerComponent.refl.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerComponentInitData>
{
  using MyBase = ComponentInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerComponentInitData"; }
  static constexpr auto GetNameHash() { return 0x274103D2; }
  static constexpr bool HasDefault() { return true; }
  static PlayerComponentInitData & GetDefault() { static PlayerComponentInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerComponentInitData *>(ptr);
    if(typeid(PlayerComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerComponentInitData *>(ptr);
    if(typeid(PlayerComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct PlayerComponent
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerComponent::type_info<0>
  {
    using type = ::PlayerComponentInitData;
  };

}

