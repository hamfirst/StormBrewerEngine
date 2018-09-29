#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerConfig.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerConfig"; }
  static constexpr auto GetNameHash() { return 0xFE5D6668; }
  static PlayerConfig & GetDefault() { static PlayerConfig def; return def; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<0>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_MoveSpeed"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x418ABC46; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_MoveSpeed; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<0, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_MoveSpeed; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_MoveSpeed; }
  void SetDefault() { self.m_MoveSpeed = StormReflTypeInfo<PlayerConfig>::GetDefault().m_MoveSpeed; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<1>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_MoveAccel"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x13507455; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_MoveAccel; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<1, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_MoveAccel; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_MoveAccel; }
  void SetDefault() { self.m_MoveAccel = StormReflTypeInfo<PlayerConfig>::GetDefault().m_MoveAccel; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<2>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_AirControlAccel"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35369914; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_AirControlAccel; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<2, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_AirControlAccel; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_AirControlAccel; }
  void SetDefault() { self.m_AirControlAccel = StormReflTypeInfo<PlayerConfig>::GetDefault().m_AirControlAccel; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<3>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_JumpSpeed"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFE52A770; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_JumpSpeed; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<3, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_JumpSpeed; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_JumpSpeed; }
  void SetDefault() { self.m_JumpSpeed = StormReflTypeInfo<PlayerConfig>::GetDefault().m_JumpSpeed; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<4>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Gravity"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFEF5072; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_Gravity; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<4, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_Gravity; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_Gravity; }
  void SetDefault() { self.m_Gravity = StormReflTypeInfo<PlayerConfig>::GetDefault().m_Gravity; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<5>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_GravityJumpReduce"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1209E625; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_GravityJumpReduce; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<5, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_GravityJumpReduce; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_GravityJumpReduce; }
  void SetDefault() { self.m_GravityJumpReduce = StormReflTypeInfo<PlayerConfig>::GetDefault().m_GravityJumpReduce; }
};

template <>
struct StormReflTypeInfo<PlayerConfig>::field_data_static<6>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_FallthroughThreshold"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD78E2B8C; }
  static constexpr unsigned GetTypeNameHash() { return 0x363C5348; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &PlayerConfig::m_FallthroughThreshold; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerConfig>::field_data<6, Self> : public StormReflTypeInfo<PlayerConfig>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_FallthroughThreshold; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_FallthroughThreshold; }
  void SetDefault() { self.m_FallthroughThreshold = StormReflTypeInfo<PlayerConfig>::GetDefault().m_FallthroughThreshold; }
};

namespace StormReflFileInfo
{
  struct PlayerConfig
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerConfig::type_info<0>
  {
    using type = ::PlayerConfig;
  };

}

