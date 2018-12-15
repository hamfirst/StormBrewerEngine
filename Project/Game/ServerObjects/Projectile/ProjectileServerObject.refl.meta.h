#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileServerObject.refl.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.meta.h"
#include "Game/Configs/ProjectileConfig.refl.meta.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ProjectileServerObjectSpawnData"; }
  static constexpr auto GetNameHash() { return 0x16E394D5; }
  static ProjectileServerObjectSpawnData & GetDefault() { static ProjectileServerObjectSpawnData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObjectSpawnData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObjectSpawnData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObjectSpawnData *>(ptr);
    if(typeid(ProjectileServerObjectSpawnData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObjectSpawnData *>(ptr);
    if(typeid(ProjectileServerObjectSpawnData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<0>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObjectSpawnData::m_Position; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Position; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Position; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data<0, Self> : public StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Position; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Position; }
  void SetDefault() { self.m_Position = StormReflTypeInfo<ProjectileServerObjectSpawnData>::GetDefault().m_Position; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<1>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Direction"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE26AF0A8; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObjectSpawnData::m_Direction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Direction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Direction; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data<1, Self> : public StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Direction; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Direction; }
  void SetDefault() { self.m_Direction = StormReflTypeInfo<ProjectileServerObjectSpawnData>::GetDefault().m_Direction; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TeamIndex"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1156ED7E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObjectSpawnData::m_TeamIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObjectSpawnData *>(obj); return &ptr->m_TeamIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObjectSpawnData *>(obj); return &ptr->m_TeamIndex; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data<2, Self> : public StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TeamIndex; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TeamIndex; }
  void SetDefault() { self.m_TeamIndex = StormReflTypeInfo<ProjectileServerObjectSpawnData>::GetDefault().m_TeamIndex; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<3>
{
  using member_type = ServerObjectHandle; // ServerObjectHandle
  static constexpr auto GetName() { return "m_OwnerHandle"; }
  static constexpr auto GetType() { return "ServerObjectHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x09D2FBB0; }
  static constexpr unsigned GetTypeNameHash() { return 0xCB9DB57C; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObjectSpawnData::m_OwnerHandle; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObjectSpawnData *>(obj); return &ptr->m_OwnerHandle; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObjectSpawnData *>(obj); return &ptr->m_OwnerHandle; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data<3, Self> : public StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectHandle> & Get() { return self.m_OwnerHandle; }
  std::add_const_t<std::remove_reference_t<ServerObjectHandle>> & Get() const { return self.m_OwnerHandle; }
  void SetDefault() { self.m_OwnerHandle = StormReflTypeInfo<ProjectileServerObjectSpawnData>::GetDefault().m_OwnerHandle; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<4>
{
  using member_type = const ConfigPtr<ProjectileConfig> *; // const ConfigPtr<ProjectileConfig> *
  static constexpr auto GetName() { return "m_Config"; }
  static constexpr auto GetType() { return "const ConfigPtr<ProjectileConfig> *"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B578B4; }
  static constexpr unsigned GetTypeNameHash() { return 0x38CD7873; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObjectSpawnData::m_Config; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Config; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObjectSpawnData *>(obj); return &ptr->m_Config; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data<4, Self> : public StormReflTypeInfo<ProjectileServerObjectSpawnData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, const ConfigPtr<ProjectileConfig> *> & Get() { return self.m_Config; }
  std::add_const_t<std::remove_reference_t<const ConfigPtr<ProjectileConfig> *>> & Get() const { return self.m_Config; }
  void SetDefault() { self.m_Config = StormReflTypeInfo<ProjectileServerObjectSpawnData>::GetDefault().m_Config; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObjectInitData>
{
  using MyBase = GameServerObjectBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x5A391BFB; }
  static ProjectileServerObjectInitData & GetDefault() { static ProjectileServerObjectInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObjectInitData *>(ptr);
    if(typeid(ProjectileServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObjectInitData *>(ptr);
    if(typeid(ProjectileServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int fields_n = 6 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileServerObject"; }
  static constexpr auto GetNameHash() { return 0x0D66E014; }
  static ProjectileServerObject & GetDefault() { static ProjectileServerObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<const GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileServerObject *>(ptr);
    if(typeid(ProjectileServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileServerObject *>(ptr);
    if(typeid(ProjectileServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<const GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Direction"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE26AF0A8; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Direction; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Direction; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Direction; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Direction; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Direction; }
  void SetDefault() { self.m_Direction = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Direction; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, kMaxTeams - 1>; // NetRangedNumber<int, -1, 3>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 3>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x338ACEE7; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, kMaxTeams - 1>> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, kMaxTeams - 1>>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ServerObjectHandle; // ServerObjectHandle
  static constexpr auto GetName() { return "m_Owner"; }
  static constexpr auto GetType() { return "ServerObjectHandle"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4256761C; }
  static constexpr unsigned GetTypeNameHash() { return 0xCB9DB57C; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Owner; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Owner; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Owner; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectHandle> & Get() { return self.m_Owner; }
  std::add_const_t<std::remove_reference_t<ServerObjectHandle>> & Get() const { return self.m_Owner; }
  void SetDefault() { self.m_Owner = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Owner; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ProjectileConfigPtr; // NetReflectionStaticListPtr<ConfigPtr<ProjectileConfig>, &g_ProjectileConfigs, &g_ProjectileConfigsCount, true>
  static constexpr auto GetName() { return "m_Config"; }
  static constexpr auto GetType() { return "NetReflectionStaticListPtr<ConfigPtr<ProjectileConfig>, &g_ProjectileConfigs, &g_ProjectileConfigsCount, true>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B578B4; }
  static constexpr unsigned GetTypeNameHash() { return 0xA35C1C16; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Config; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Config; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Config; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ProjectileConfigPtr> & Get() { return self.m_Config; }
  std::add_const_t<std::remove_reference_t<ProjectileConfigPtr>> & Get() const { return self.m_Config; }
  void SetDefault() { self.m_Config = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Config; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>; // ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>
  static constexpr auto GetName() { return "m_Motion"; }
  static constexpr auto GetType() { return "ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8C1F620; }
  static constexpr unsigned GetTypeNameHash() { return 0xAFE7A191; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Motion; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Motion; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Motion; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>> & Get() { return self.m_Motion; }
  std::add_const_t<std::remove_reference_t<ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig>>> & Get() const { return self.m_Motion; }
  void SetDefault() { self.m_Motion = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Motion; }
};

template <>
struct StormReflTypeInfo<ProjectileServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>; // ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>
  static constexpr auto GetName() { return "m_Response"; }
  static constexpr auto GetType() { return "ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC857DFD5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C22E067; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileServerObject::m_Response; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileServerObject *>(obj); return &ptr->m_Response; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileServerObject *>(obj); return &ptr->m_Response; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileServerObject>::field_data<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>> & Get() { return self.m_Response; }
  std::add_const_t<std::remove_reference_t<ServerObjectComponent<ProjectileResponseBase, ProjectileResponseBaseConfig>>> & Get() const { return self.m_Response; }
  void SetDefault() { self.m_Response = StormReflTypeInfo<ProjectileServerObject>::GetDefault().m_Response; }
};

template <>
struct StormReflFuncInfo<ProjectileServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct ProjectileServerObject
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileServerObject::type_info<0>
  {
    using type = ::ProjectileServerObjectSpawnData;
  };

  template <>
  struct ProjectileServerObject::type_info<1>
  {
    using type = ::ProjectileServerObjectInitData;
  };

  template <>
  struct ProjectileServerObject::type_info<2>
  {
    using type = ::ProjectileServerObject;
  };

}

