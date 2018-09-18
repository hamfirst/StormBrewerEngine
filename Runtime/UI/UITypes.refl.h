#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

enum STORM_REFL_ENUM class UIVariableType : uint16_t
{
  kFloat,
  kString,
};

enum STORM_REFL_ENUM class UIElementType
{
  kContainer,
  kGradient,
  kTextureSlice,
  kSpriteFrame,
  kText,
  kShape,
  kFullTexture,
  kTextInput
};

struct UIRuntimeFieldDesc
{
  UIVariableType m_Type;
  czstr m_Name;
};