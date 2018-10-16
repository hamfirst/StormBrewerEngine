#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapHandles.refl.h"


template <>
struct StormReflTypeInfo<MapHandleBase>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapHandleBase"; }
  static constexpr auto GetNameHash() { return 0xABCB7450; }
  static MapHandleBase & GetDefault() { static MapHandleBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapHandleBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapHandleBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapHandleBase *>(ptr);
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapHandleBase *>(ptr);
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapHandleBase>::field_data_static<0>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_GUID"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83551827; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapHandleBase::m_GUID; }
};

template <typename Self>
struct StormReflTypeInfo<MapHandleBase>::field_data<0, Self> : public StormReflTypeInfo<MapHandleBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_GUID; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_GUID; }
  void SetDefault() { self.m_GUID = StormReflTypeInfo<MapHandleBase>::GetDefault().m_GUID; }
};

template <>
struct StormReflTypeInfo<MapHandleBase>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapHandleBase>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "noui"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xDF10877E; }
};

template <>
struct StormReflTypeInfo<MapEntityHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapEntityHandle"; }
  static constexpr auto GetNameHash() { return 0x9904F950; }
  static MapEntityHandle & GetDefault() { static MapEntityHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapEntityHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapEntityHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapEntityHandle *>(ptr);
    if(typeid(MapEntityHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapEntityHandle *>(ptr);
    if(typeid(MapEntityHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapEffectLayerHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapEffectLayerHandle"; }
  static constexpr auto GetNameHash() { return 0xBCE8D836; }
  static MapEffectLayerHandle & GetDefault() { static MapEffectLayerHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapEffectLayerHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapEffectLayerHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapEffectLayerHandle *>(ptr);
    if(typeid(MapEffectLayerHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapEffectLayerHandle *>(ptr);
    if(typeid(MapEffectLayerHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapServerObjectHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapServerObjectHandle"; }
  static constexpr auto GetNameHash() { return 0x831F1675; }
  static MapServerObjectHandle & GetDefault() { static MapServerObjectHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapServerObjectHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapServerObjectHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapServerObjectHandle *>(ptr);
    if(typeid(MapServerObjectHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapServerObjectHandle *>(ptr);
    if(typeid(MapServerObjectHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapAnchorHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapAnchorHandle"; }
  static constexpr auto GetNameHash() { return 0x6BDD357A; }
  static MapAnchorHandle & GetDefault() { static MapAnchorHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapAnchorHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapAnchorHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapAnchorHandle *>(ptr);
    if(typeid(MapAnchorHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapAnchorHandle *>(ptr);
    if(typeid(MapAnchorHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapPathHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapPathHandle"; }
  static constexpr auto GetNameHash() { return 0xFDA1CFC8; }
  static MapPathHandle & GetDefault() { static MapPathHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapPathHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapPathHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapPathHandle *>(ptr);
    if(typeid(MapPathHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapPathHandle *>(ptr);
    if(typeid(MapPathHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapVolumeHandle>
{
  using MyBase = MapHandleBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "MapVolumeHandle"; }
  static constexpr auto GetNameHash() { return 0x9E0BB55F; }
  static MapVolumeHandle & GetDefault() { static MapVolumeHandle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapVolumeHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapVolumeHandle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xABCB7450 == type_name_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapVolumeHandle *>(ptr);
    if(typeid(MapVolumeHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<MapHandleBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapVolumeHandle *>(ptr);
    if(typeid(MapVolumeHandle).hash_code() == type_id_hash) return c;
    if(typeid(MapHandleBase).hash_code() == type_id_hash) return static_cast<const MapHandleBase *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct MapHandles
  {
    static const int types_n = 7;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapHandles::type_info<0>
  {
    using type = ::MapHandleBase;
  };

  template <>
  struct MapHandles::type_info<1>
  {
    using type = ::MapEntityHandle;
  };

  template <>
  struct MapHandles::type_info<2>
  {
    using type = ::MapEffectLayerHandle;
  };

  template <>
  struct MapHandles::type_info<3>
  {
    using type = ::MapServerObjectHandle;
  };

  template <>
  struct MapHandles::type_info<4>
  {
    using type = ::MapAnchorHandle;
  };

  template <>
  struct MapHandles::type_info<5>
  {
    using type = ::MapPathHandle;
  };

  template <>
  struct MapHandles::type_info<6>
  {
    using type = ::MapVolumeHandle;
  };

}

