#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "VisualEffectTypes.refl.h"


template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceEmitterGlobalData"; }
  static constexpr auto GetNameHash() { return 0x90655156; }
  static VisualEffectInstanceEmitterGlobalData & GetDefault() { static VisualEffectInstanceEmitterGlobalData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrevPositionX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1D8826ED; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_PrevPositionX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrevPositionX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrevPositionX; }
  void SetDefault() { self.m_PrevPositionX = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_PrevPositionX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PrevPositionY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A8F167B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_PrevPositionY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PrevPositionY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PrevPositionY; }
  void SetDefault() { self.m_PrevPositionY = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_PrevPositionY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EffectTimeAlive"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0E8DFABA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_EffectTimeAlive; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<4, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EffectTimeAlive; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EffectTimeAlive; }
  void SetDefault() { self.m_EffectTimeAlive = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_EffectTimeAlive; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ParticleId"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87D1B063; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterGlobalData::m_ParticleId; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data<5, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ParticleId; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ParticleId; }
  void SetDefault() { self.m_ParticleId = StormReflTypeInfo<VisualEffectInstanceEmitterGlobalData>::GetDefault().m_ParticleId; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterAutoData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceEmitterAutoData"; }
  static constexpr auto GetNameHash() { return 0xAC46C0AF; }
  static VisualEffectInstanceEmitterAutoData & GetDefault() { static VisualEffectInstanceEmitterAutoData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceEmitterScriptData"; }
  static constexpr auto GetNameHash() { return 0x1C3AC268; }
  static VisualEffectInstanceEmitterScriptData & GetDefault() { static VisualEffectInstanceEmitterScriptData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_MaxParticles"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6C3F10C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterScriptData::m_MaxParticles; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_MaxParticles; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_MaxParticles; }
  void SetDefault() { self.m_MaxParticles = StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::GetDefault().m_MaxParticles; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_EmitterLifetime"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x84A572E7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterScriptData::m_EmitterLifetime; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_EmitterLifetime; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_EmitterLifetime; }
  void SetDefault() { self.m_EmitterLifetime = StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::GetDefault().m_EmitterLifetime; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SpawnRate"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1C29A72A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterScriptData::m_SpawnRate; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SpawnRate; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SpawnRate; }
  void SetDefault() { self.m_SpawnRate = StormReflTypeInfo<VisualEffectInstanceEmitterScriptData>::GetDefault().m_SpawnRate; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>
{
  using MyBase = void;
  static constexpr int fields_n = 10;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceRandBlock"; }
  static constexpr auto GetNameHash() { return 0xBBFAB166; }
  static VisualEffectInstanceRandBlock & GetDefault() { static VisualEffectInstanceRandBlock def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x099F7D3B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandA; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandA; }
  void SetDefault() { self.m_RandA = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandA; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x90962C81; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandB; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandB; }
  void SetDefault() { self.m_RandB = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandB; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandC"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7911C17; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandC; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandC; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandC; }
  void SetDefault() { self.m_RandC = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandC; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandD"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79F589B4; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandD; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandD; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandD; }
  void SetDefault() { self.m_RandD = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandD; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandE"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0EF2B922; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandE; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<4, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandE; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandE; }
  void SetDefault() { self.m_RandE = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandE; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandF"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x97FBE898; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandF; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<5, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandF; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandF; }
  void SetDefault() { self.m_RandF = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandF; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE0FCD80E; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandG; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<6, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandG; }
  void SetDefault() { self.m_RandG = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandG; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandH"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7043C59F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandH; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<7, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandH; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandH; }
  void SetDefault() { self.m_RandH = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandH; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandAngleA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x76649879; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandAngleA; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<8, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandAngleA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandAngleA; }
  void SetDefault() { self.m_RandAngleA = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandAngleA; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_RandAngleB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEF6DC9C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceRandBlock::m_RandAngleB; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data<9, Self> : public StormReflTypeInfo<VisualEffectInstanceRandBlock>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_RandAngleB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_RandAngleB; }
  void SetDefault() { self.m_RandAngleB = StormReflTypeInfo<VisualEffectInstanceRandBlock>::GetDefault().m_RandAngleB; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceEmitterSpawnData"; }
  static constexpr auto GetNameHash() { return 0x8F02FED0; }
  static VisualEffectInstanceEmitterSpawnData & GetDefault() { static VisualEffectInstanceEmitterSpawnData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SpawnOffsetX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7DCEC592; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterSpawnData::m_SpawnOffsetX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SpawnOffsetX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SpawnOffsetX; }
  void SetDefault() { self.m_SpawnOffsetX = StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::GetDefault().m_SpawnOffsetX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SpawnOffsetY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0AC9F504; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterSpawnData::m_SpawnOffsetY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SpawnOffsetY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SpawnOffsetY; }
  void SetDefault() { self.m_SpawnOffsetY = StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::GetDefault().m_SpawnOffsetY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SpawnVelocityX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x300101EE; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterSpawnData::m_SpawnVelocityX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SpawnVelocityX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SpawnVelocityX; }
  void SetDefault() { self.m_SpawnVelocityX = StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::GetDefault().m_SpawnVelocityX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SpawnVelocityY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47063178; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceEmitterSpawnData::m_SpawnVelocityY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SpawnVelocityY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SpawnVelocityY; }
  void SetDefault() { self.m_SpawnVelocityY = StormReflTypeInfo<VisualEffectInstanceEmitterSpawnData>::GetDefault().m_SpawnVelocityY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceParticleAutoData"; }
  static constexpr auto GetNameHash() { return 0x004F2D4F; }
  static VisualEffectInstanceParticleAutoData & GetDefault() { static VisualEffectInstanceParticleAutoData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA6033D27; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_PositionX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionX; }
  void SetDefault() { self.m_PositionX = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_PositionX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_PositionY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD1040DB1; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_PositionY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_PositionY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_PositionY; }
  void SetDefault() { self.m_PositionY = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_PositionY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_VelocityX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC426D4CA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_VelocityX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_VelocityX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_VelocityX; }
  void SetDefault() { self.m_VelocityX = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_VelocityX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_VelocityY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB321E45C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_VelocityY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_VelocityY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_VelocityY; }
  void SetDefault() { self.m_VelocityY = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_VelocityY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Speed"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x82106E96; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_Speed; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<4, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Speed; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Speed; }
  void SetDefault() { self.m_Speed = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_Speed; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TimeAlive"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFD422D7A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_TimeAlive; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<5, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TimeAlive; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TimeAlive; }
  void SetDefault() { self.m_TimeAlive = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_TimeAlive; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_TimePct"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x271C173D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_TimePct; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<6, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_TimePct; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_TimePct; }
  void SetDefault() { self.m_TimePct = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_TimePct; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_InvTimePct"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5A60E82A; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_InvTimePct; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<7, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_InvTimePct; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_InvTimePct; }
  void SetDefault() { self.m_InvTimePct = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_InvTimePct; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ParticleId"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87D1B063; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleAutoData::m_ParticleId; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data<8, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ParticleId; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ParticleId; }
  void SetDefault() { self.m_ParticleId = StormReflTypeInfo<VisualEffectInstanceParticleAutoData>::GetDefault().m_ParticleId; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>
{
  using MyBase = void;
  static constexpr int fields_n = 15;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VisualEffectInstanceParticleScriptData"; }
  static constexpr auto GetNameHash() { return 0x9CFF0348; }
  static VisualEffectInstanceParticleScriptData & GetDefault() { static VisualEffectInstanceParticleScriptData def; return def; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorR"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3E88409; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ColorR; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<0, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorR; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorR; }
  void SetDefault() { self.m_ColorR = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ColorR; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorG"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE3560E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ColorG; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<1, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorG; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorG; }
  void SetDefault() { self.m_ColorG = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ColorG; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorB"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDE5F946D; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ColorB; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<2, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorB; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorB; }
  void SetDefault() { self.m_ColorB = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ColorB; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<3>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ColorA"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4756C5D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ColorA; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<3, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ColorA; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ColorA; }
  void SetDefault() { self.m_ColorA = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ColorA; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<4>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SizeX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9714EE49; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_SizeX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<4, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SizeX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SizeX; }
  void SetDefault() { self.m_SizeX = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_SizeX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<5>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_SizeY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE013DEDF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_SizeY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<5, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_SizeY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_SizeY; }
  void SetDefault() { self.m_SizeY = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_SizeY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<6>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Rotation"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDF504CDF; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_Rotation; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<6, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Rotation; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Rotation; }
  void SetDefault() { self.m_Rotation = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_Rotation; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<7>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ForceX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCFAFA1FA; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ForceX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<7, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ForceX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ForceX; }
  void SetDefault() { self.m_ForceX = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ForceX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<8>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ForceY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8A8916C; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_ForceY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<8, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ForceY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ForceY; }
  void SetDefault() { self.m_ForceY = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_ForceY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<9>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Drag"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x53D83874; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_Drag; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<9, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Drag; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Drag; }
  void SetDefault() { self.m_Drag = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_Drag; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<10>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_DestinationX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x260DC3E5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_DestinationX; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<10, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_DestinationX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_DestinationX; }
  void SetDefault() { self.m_DestinationX = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_DestinationX; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<11>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_DestinationY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x510AF373; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_DestinationY; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<11, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_DestinationY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_DestinationY; }
  void SetDefault() { self.m_DestinationY = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_DestinationY; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<12>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_DestinationLerp"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x12659004; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_DestinationLerp; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<12, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_DestinationLerp; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_DestinationLerp; }
  void SetDefault() { self.m_DestinationLerp = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_DestinationLerp; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<13>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_MaxLifetime"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC175EE03; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 13; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_MaxLifetime; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<13, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<13>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_MaxLifetime; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_MaxLifetime; }
  void SetDefault() { self.m_MaxLifetime = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_MaxLifetime; }
};

template <>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<14>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Collision"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87ED02A5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 14; }
  static constexpr auto GetMemberPtr() { return &VisualEffectInstanceParticleScriptData::m_Collision; }
};

template <typename Self>
struct StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data<14, Self> : public StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::field_data_static<14>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Collision; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Collision; }
  void SetDefault() { self.m_Collision = StormReflTypeInfo<VisualEffectInstanceParticleScriptData>::GetDefault().m_Collision; }
};

namespace StormReflFileInfo
{
  struct VisualEffectTypes
  {
    static const int types_n = 7;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct VisualEffectTypes::type_info<0>
  {
    using type = ::VisualEffectInstanceEmitterGlobalData;
  };

  template <>
  struct VisualEffectTypes::type_info<1>
  {
    using type = ::VisualEffectInstanceEmitterAutoData;
  };

  template <>
  struct VisualEffectTypes::type_info<2>
  {
    using type = ::VisualEffectInstanceEmitterScriptData;
  };

  template <>
  struct VisualEffectTypes::type_info<3>
  {
    using type = ::VisualEffectInstanceRandBlock;
  };

  template <>
  struct VisualEffectTypes::type_info<4>
  {
    using type = ::VisualEffectInstanceEmitterSpawnData;
  };

  template <>
  struct VisualEffectTypes::type_info<5>
  {
    using type = ::VisualEffectInstanceParticleAutoData;
  };

  template <>
  struct VisualEffectTypes::type_info<6>
  {
    using type = ::VisualEffectInstanceParticleScriptData;
  };

}

