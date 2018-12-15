#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotServerObject.refl.h"
#include "Game/ServerObjects/CharacterFacing.refl.meta.h"
#include "Game/ServerObjects/GameServerObjectBase.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<BotServerObjectInitData>
{
  using MyBase = GameServerObjectBaseInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x1C601FCD; }
  static BotServerObjectInitData & GetDefault() { static BotServerObjectInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BotServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObjectInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xE8EFD458 == type_name_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(0x2D36BDE7 == type_name_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BotServerObjectInitData *>(ptr);
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<ServerObjectInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObjectInitData *>(ptr);
    if(typeid(BotServerObjectInitData).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBaseInitData).hash_code() == type_id_hash) return static_cast<const GameServerObjectBaseInitData *>(c);
    if(typeid(ServerObjectInitData).hash_code() == type_id_hash) return static_cast<const ServerObjectInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BotServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int fields_n = 6 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObject"; }
  static constexpr auto GetNameHash() { return 0xF3F6D91E; }
  static BotServerObject & GetDefault() { static BotServerObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<BotServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x25DA07B6 == type_name_hash) return static_cast<const GameServerObjectBase *>(c);
    if(0x9D89FBB7 == type_name_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<BotServerObject *>(ptr);
    if(typeid(BotServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<ServerObject *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const BotServerObject *>(ptr);
    if(typeid(BotServerObject).hash_code() == type_id_hash) return c;
    if(typeid(GameServerObjectBase).hash_code() == type_id_hash) return static_cast<const GameServerObjectBase *>(c);
    if(typeid(ServerObject).hash_code() == type_id_hash) return static_cast<const ServerObject *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Velocity; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_Velocity; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_Velocity; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Velocity; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Velocity; }
  void SetDefault() { self.m_Velocity = StormReflTypeInfo<BotServerObject>::GetDefault().m_Velocity; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_OnGround"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50DDA915; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_OnGround; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_OnGround; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_OnGround; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_OnGround; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_OnGround; }
  void SetDefault() { self.m_OnGround = StormReflTypeInfo<BotServerObject>::GetDefault().m_OnGround; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, 30>; // NetRangedNumber<int, -1, 30>
  static constexpr auto GetName() { return "m_AnimIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9984B871; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3BD22BD; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimIndex; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, 30>> & Get() { return self.m_AnimIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, 30>>> & Get() const { return self.m_AnimIndex; }
  void SetDefault() { self.m_AnimIndex = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimIndex; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AnimFrame"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAC0FE3BD; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimFrame; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimFrame; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimFrame; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AnimFrame; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AnimFrame; }
  void SetDefault() { self.m_AnimFrame = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimFrame; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 63>; // NetRangedNumber<int, 0, 63>
  static constexpr auto GetName() { return "m_AnimDelay"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 63>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB6D5FEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x46CFECEB; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimDelay; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_AnimDelay; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_AnimDelay; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 63>> & Get() { return self.m_AnimDelay; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 63>>> & Get() const { return self.m_AnimDelay; }
  void SetDefault() { self.m_AnimDelay = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimDelay; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  using member_type = NetEnum<CharacterFacing>; // NetEnum<CharacterFacing>
  static constexpr auto GetName() { return "m_Facing"; }
  static constexpr auto GetType() { return "NetEnum<CharacterFacing>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC03F5E41; }
  static constexpr unsigned GetTypeNameHash() { return 0x94981591; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<GameServerObjectBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Facing; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<BotServerObject *>(obj); return &ptr->m_Facing; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const BotServerObject *>(obj); return &ptr->m_Facing; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<GameServerObjectBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<CharacterFacing>> & Get() { return self.m_Facing; }
  std::add_const_t<std::remove_reference_t<NetEnum<CharacterFacing>>> & Get() const { return self.m_Facing; }
  void SetDefault() { self.m_Facing = StormReflTypeInfo<BotServerObject>::GetDefault().m_Facing; }
};

template <>
struct StormReflFuncInfo<BotServerObject>
{
  using MyBase = GameServerObjectBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct BotServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BotServerObject::type_info<0>
  {
    using type = ::BotServerObjectInitData;
  };

  template <>
  struct BotServerObject::type_info<1>
  {
    using type = ::BotServerObject;
  };

}

