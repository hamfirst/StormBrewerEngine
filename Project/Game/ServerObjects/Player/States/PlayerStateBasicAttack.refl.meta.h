#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateBasicAttack.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"
#include "Game/GameplayEvents/DamageType.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerStateBasicAttackSettings"; }
  static constexpr auto GetNameHash() { return 0x92F8B625; }
  static constexpr bool HasDefault() { return true; }
  static PlayerStateBasicAttackSettings & GetDefault() { static PlayerStateBasicAttackSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttackSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttackSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttackSettings *>(ptr);
    if(typeid(PlayerStateBasicAttackSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttackSettings *>(ptr);
    if(typeid(PlayerStateBasicAttackSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_ApplyMovement"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5D5D69F2; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackSettings::m_ApplyMovement; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackSettings *>(obj); return &ptr->m_ApplyMovement; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackSettings *>(obj); return &ptr->m_ApplyMovement; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data<0, Self> : public StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_ApplyMovement; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_ApplyMovement; }
  void SetDefault() { self.m_ApplyMovement = StormReflTypeInfo<PlayerStateBasicAttackSettings>::GetDefault().m_ApplyMovement; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_RetainMovement"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB4D46B6E; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackSettings::m_RetainMovement; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackSettings *>(obj); return &ptr->m_RetainMovement; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackSettings *>(obj); return &ptr->m_RetainMovement; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data<1, Self> : public StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_RetainMovement; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_RetainMovement; }
  void SetDefault() { self.m_RetainMovement = StormReflTypeInfo<PlayerStateBasicAttackSettings>::GetDefault().m_RetainMovement; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_ApplyGravity"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x664F734B; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackSettings::m_ApplyGravity; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackSettings *>(obj); return &ptr->m_ApplyGravity; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackSettings *>(obj); return &ptr->m_ApplyGravity; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data<2, Self> : public StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_ApplyGravity; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_ApplyGravity; }
  void SetDefault() { self.m_ApplyGravity = StormReflTypeInfo<PlayerStateBasicAttackSettings>::GetDefault().m_ApplyGravity; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_InterruptIfNoGround"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6F4B264F; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackSettings::m_InterruptIfNoGround; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackSettings *>(obj); return &ptr->m_InterruptIfNoGround; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackSettings *>(obj); return &ptr->m_InterruptIfNoGround; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data<3, Self> : public StormReflTypeInfo<PlayerStateBasicAttackSettings>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_InterruptIfNoGround; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_InterruptIfNoGround; }
  void SetDefault() { self.m_InterruptIfNoGround = StormReflTypeInfo<PlayerStateBasicAttackSettings>::GetDefault().m_InterruptIfNoGround; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerStateBasicAttackDamageSettings"; }
  static constexpr auto GetNameHash() { return 0xAB94091A; }
  static constexpr bool HasDefault() { return true; }
  static PlayerStateBasicAttackDamageSettings & GetDefault() { static PlayerStateBasicAttackDamageSettings def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttackDamageSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttackDamageSettings *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttackDamageSettings *>(ptr);
    if(typeid(PlayerStateBasicAttackDamageSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttackDamageSettings *>(ptr);
    if(typeid(PlayerStateBasicAttackDamageSettings).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data_static<0>
{
  using member_type = NetRangedNumber<int, 1, 64>; // NetRangedNumber<int, 1, 64>
  static constexpr auto GetName() { return "m_DamageAmount"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 1, 64>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3237A596; }
  static constexpr unsigned GetTypeNameHash() { return 0xC2D2A989; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackDamageSettings::m_DamageAmount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackDamageSettings *>(obj); return &ptr->m_DamageAmount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackDamageSettings *>(obj); return &ptr->m_DamageAmount; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data<0, Self> : public StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 1, 64>> & Get() { return self.m_DamageAmount; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 1, 64>>> & Get() const { return self.m_DamageAmount; }
  void SetDefault() { self.m_DamageAmount = StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::GetDefault().m_DamageAmount; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data_static<1>
{
  using member_type = NetEnum<DamageType>; // NetEnum<DamageType>
  static constexpr auto GetName() { return "m_DamageType"; }
  static constexpr auto GetType() { return "NetEnum<DamageType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD583A2B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x73E55A5E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttackDamageSettings::m_DamageType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttackDamageSettings *>(obj); return &ptr->m_DamageType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttackDamageSettings *>(obj); return &ptr->m_DamageType; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data<1, Self> : public StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<DamageType>> & Get() { return self.m_DamageType; }
  std::add_const_t<std::remove_reference_t<NetEnum<DamageType>>> & Get() const { return self.m_DamageType; }
  void SetDefault() { self.m_DamageType = StormReflTypeInfo<PlayerStateBasicAttackDamageSettings>::GetDefault().m_DamageType; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttack>
{
  using MyBase = PlayerStateBase;
  static constexpr int fields_n = 3 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerStateBasicAttack"; }
  static constexpr auto GetNameHash() { return 0x8B41490B; }
  static constexpr bool HasDefault() { return true; }
  static PlayerStateBasicAttack & GetDefault() { static PlayerStateBasicAttack def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttack *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<PlayerStateEventHandler<PlayerStateBasicAttack> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttack *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x887CB291 == type_name_hash) return static_cast<const PlayerStateBase *>(c);
    if(0x8FB16778 == type_name_hash) return static_cast<const PlayerStateEventHandler<PlayerStateBasicAttack> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayerStateBasicAttack *>(ptr);
    if(typeid(PlayerStateBasicAttack).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateBasicAttack>).hash_code() == type_id_hash) return static_cast<PlayerStateEventHandler<PlayerStateBasicAttack> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayerStateBasicAttack *>(ptr);
    if(typeid(PlayerStateBasicAttack).hash_code() == type_id_hash) return c;
    if(typeid(PlayerStateBase).hash_code() == type_id_hash) return static_cast<const PlayerStateBase *>(c);
    if(typeid(PlayerStateEventHandler<PlayerStateBasicAttack>).hash_code() == type_id_hash) return static_cast<const PlayerStateEventHandler<PlayerStateBasicAttack> *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<0 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_AnimationHash"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x44C6FEA4; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<PlayerStateBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttack::m_AnimationHash; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttack *>(obj); return &ptr->m_AnimationHash; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttack *>(obj); return &ptr->m_AnimationHash; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data<0 + StormReflTypeInfo<PlayerStateBase>::fields_n, Self> : public StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<0 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_AnimationHash; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_AnimationHash; }
  void SetDefault() { self.m_AnimationHash = StormReflTypeInfo<PlayerStateBasicAttack>::GetDefault().m_AnimationHash; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<1 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  using member_type = PlayerStateBasicAttackSettings; // PlayerStateBasicAttackSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "PlayerStateBasicAttackSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x92F8B625; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<PlayerStateBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttack::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttack *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttack *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data<1 + StormReflTypeInfo<PlayerStateBase>::fields_n, Self> : public StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<1 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, PlayerStateBasicAttackSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<PlayerStateBasicAttackSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<PlayerStateBasicAttack>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<2 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  using member_type = NetOptional<PlayerStateBasicAttackDamageSettings>; // NetOptional<PlayerStateBasicAttackDamageSettings>
  static constexpr auto GetName() { return "m_DamageSettings"; }
  static constexpr auto GetType() { return "NetOptional<PlayerStateBasicAttackDamageSettings>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF6A83A13; }
  static constexpr unsigned GetTypeNameHash() { return 0x189AF9C7; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<PlayerStateBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerStateBasicAttack::m_DamageSettings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayerStateBasicAttack *>(obj); return &ptr->m_DamageSettings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayerStateBasicAttack *>(obj); return &ptr->m_DamageSettings; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerStateBasicAttack>::field_data<2 + StormReflTypeInfo<PlayerStateBase>::fields_n, Self> : public StormReflTypeInfo<PlayerStateBasicAttack>::field_data_static<2 + StormReflTypeInfo<PlayerStateBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetOptional<PlayerStateBasicAttackDamageSettings>> & Get() { return self.m_DamageSettings; }
  std::add_const_t<std::remove_reference_t<NetOptional<PlayerStateBasicAttackDamageSettings>>> & Get() const { return self.m_DamageSettings; }
  void SetDefault() { self.m_DamageSettings = StormReflTypeInfo<PlayerStateBasicAttack>::GetDefault().m_DamageSettings; }
};

template <>
struct StormReflFuncInfo<PlayerStateBasicAttack>
{
  using MyBase = PlayerStateBase;
  static constexpr int funcs_n = 1 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<PlayerStateBasicAttack>::func_data_static<0 + StormReflFuncInfo<PlayerStateBase>::funcs_n>
{
  using func_ptr_type = bool (PlayerStateBasicAttack::*)(const DealDamageAnimationEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleDealDamageEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x197B96A4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<PlayerStateBase>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerStateBasicAttack::HandleDealDamageEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerStateBasicAttack>::func_data_static<0 + StormReflFuncInfo<PlayerStateBase>::funcs_n>::param_info<0>
{
  using param_type = const DealDamageAnimationEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const DealDamageAnimationEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0x558C63ED; }
};

template <>
struct StormReflFuncInfo<PlayerStateBasicAttack>::func_data_static<0 + StormReflFuncInfo<PlayerStateBase>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
};

namespace StormReflFileInfo
{
  struct PlayerStateBasicAttack
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateBasicAttack::type_info<0>
  {
    using type = ::PlayerStateBasicAttackSettings;
  };

  template <>
  struct PlayerStateBasicAttack::type_info<1>
  {
    using type = ::PlayerStateBasicAttackDamageSettings;
  };

  template <>
  struct PlayerStateBasicAttack::type_info<2>
  {
    using type = ::PlayerStateBasicAttack;
  };

}

