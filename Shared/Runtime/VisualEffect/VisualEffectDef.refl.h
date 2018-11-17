#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/RuntimeCommon.h"
#include "Runtime/UI/UIElementTypeDatabase.h"
#include "Runtime/UI/UITypes.refl.h"

struct RUNTIME_EXPORT VisualEffectDefInputVariable
{
  STORM_DATA_DEFAULT_CONSTRUCTION(VisualEffectDefInputVariable);
  RString m_VariableName;
};

struct RUNTIME_EXPORT VisualEffectDefEquation
{
  STORM_DATA_DEFAULT_CONSTRUCTION(VisualEffectDefEquation);

  RString m_VariableName;
  RString m_Equation;
};

struct RUNTIME_EXPORT VisualEffectDefEmitterProperties
{
  STORM_DATA_DEFAULT_CONSTRUCTION(VisualEffectDefEmitterProperties);

  RString m_Name;
  RString STORM_REFL_ATTR_VAL(file, image) m_Texture;
  RInt m_PrespawnParticles;
  RInt m_UpdateDelay;
  RBool m_Additive;
  RBool m_LinearFilter;
  RBool m_Trail;
};

struct RUNTIME_EXPORT VisualEffectDefEmitter
{
  STORM_DATA_DEFAULT_CONSTRUCTION(VisualEffectDefEmitter);

  VisualEffectDefEmitterProperties m_Properties;
  RMap<uint32_t, VisualEffectDefEquation> m_EmitterEquations;
  RMap<uint32_t, VisualEffectDefEquation> m_SpawnEquations;
  RMap<uint32_t, VisualEffectDefEquation> m_ParticleEquations;
};

class RUNTIME_EXPORT VisualEffectDef
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(VisualEffectDef);

  RMergeList<VisualEffectDefInputVariable> m_Inputs;
  RMergeList<VisualEffectDefEmitter> m_Emitters;

  RInt m_UpdateBoundsX;
  RInt m_UpdateBoundsY;
};
