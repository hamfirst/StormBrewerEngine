#pragma once

#include <StormRefl/StormRefl.h>


struct VisualEffectInstanceEmitterGlobalData
{
  STORM_REFL;
  float m_PositionX;
  float m_PositionY;
  float m_PrevPositionX;
  float m_PrevPositionY;
  float m_EffectTimeAlive;
};

struct VisualEffectInstanceEmitterAutoData
{
  STORM_REFL;
};

struct VisualEffectInstanceEmitterScriptData
{
  STORM_REFL;
  float m_MaxParticles = 10000.0f;
  float m_EmitterLifetime = 0;
  float m_SpawnRate = 5.0f;
};

struct VisualEffectInstanceRandBlock
{
  STORM_REFL;
  float m_RandA;
  float m_RandB;
  float m_RandC;
  float m_RandD;
  float m_RandE;
  float m_RandF;
  float m_RandG;
  float m_RandH;
  float m_RandAngleA;
  float m_RandAngleB;
};

struct VisualEffectInstanceEmitterSpawnData
{
  STORM_REFL;
  float m_SpawnOffsetX = 0.0f;
  float m_SpawnOffsetY = 0.0f;
  float m_SpawnVelocityX = 0.0f;
  float m_SpawnVelocityY = 0.0f;
};

struct VisualEffectInstanceParticleAutoData
{
  STORM_REFL;
  float m_PositionX;
  float m_PositionY;
  float m_VelocityX;
  float m_VelocityY;
  float m_Speed;
  float m_TimeAlive;
  float m_TimePct;
  float m_InvTimePct;
  float m_ParticleId;
};

struct VisualEffectInstanceParticleScriptData
{
  STORM_REFL;
  float m_ColorR = 1.0f;
  float m_ColorG = 1.0f;
  float m_ColorB = 1.0f;
  float m_ColorA = 1.0f;

  float m_SizeX = 1.0f;
  float m_SizeY = 1.0f;
  float m_Rotation = 0.0f;

  float m_ForceX = 0.0f;
  float m_ForceY = 0.0f;
  float m_Drag = 0.0f;

  float m_DestinationX = 0.0f;
  float m_DestinationY = 0.0f;
  float m_DestinationLerp = 0.0f;

  float m_MaxLifetime = 1.0f;
  float m_Collision = 0.0f;
};

