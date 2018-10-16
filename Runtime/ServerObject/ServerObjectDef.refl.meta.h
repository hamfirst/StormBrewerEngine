#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerObjectDef.refl.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ServerObjectDef>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerObjectDef"; }
  static constexpr auto GetNameHash() { return 0x97B44C7B; }
  static ServerObjectDef & GetDefault() { static ServerObjectDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerObjectDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerObjectDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerObjectDef *>(ptr);
    if(typeid(ServerObjectDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerObjectDef *>(ptr);
    if(typeid(ServerObjectDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ServerObjectDef>::field_data_static<0>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_IsStatic"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB784F6D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ServerObjectDef::m_IsStatic; }
};

template <typename Self>
struct StormReflTypeInfo<ServerObjectDef>::field_data<0, Self> : public StormReflTypeInfo<ServerObjectDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_IsStatic; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_IsStatic; }
  void SetDefault() { self.m_IsStatic = StormReflTypeInfo<ServerObjectDef>::GetDefault().m_IsStatic; }
};

template <>
struct StormReflTypeInfo<ServerObjectDef>::field_data_static<1>
{
  using member_type = RPolymorphic<ServerObjectInitData>; // RPolymorphicBase<ServerObjectInitData, TypeDatabase<ServerObjectInitData, void>, TypeDatabaseTypeInfo<ServerObjectInitData, void>, false>
  static constexpr auto GetName() { return "m_InitData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<ServerObjectInitData, TypeDatabase<ServerObjectInitData, void>, TypeDatabaseTypeInfo<ServerObjectInitData, void>, false>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x880F1CB3; }
  static constexpr unsigned GetTypeNameHash() { return 0x98B2E037; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ServerObjectDef::m_InitData; }
};

template <typename Self>
struct StormReflTypeInfo<ServerObjectDef>::field_data<1, Self> : public StormReflTypeInfo<ServerObjectDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<ServerObjectInitData>> & Get() { return self.m_InitData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<ServerObjectInitData>>> & Get() const { return self.m_InitData; }
  void SetDefault() { self.m_InitData = StormReflTypeInfo<ServerObjectDef>::GetDefault().m_InitData; }
};

namespace StormReflFileInfo
{
  struct ServerObjectDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerObjectDef::type_info<0>
  {
    using type = ::ServerObjectDef;
  };

}

