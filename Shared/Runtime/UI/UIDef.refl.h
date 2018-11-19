#pragma once

#include "StormRefl/StormRefl.h"
#include "StormData/StormData.h"
#include "StormData/StormDataTypes.h"

#include "Runtime/RuntimeCommon.h"
#include "Runtime/UI/UIElementTypeDatabase.h"
#include "Runtime/UI/UITypes.refl.h"


struct RUNTIME_EXPORT UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementInitDataBase);
};

struct RUNTIME_EXPORT UIDefInputVariable
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefInputVariable);
  RString m_VariableName;
  RString m_DefaultEquation;
  REnum<UIVariableType> m_Type;
};

struct RUNTIME_EXPORT UIDefEquation
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefEquation);
  RString m_VariableName;
  RString m_Equation;
};

struct RUNTIME_EXPORT UIDefOutputEquation
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefOutputEquation);
  RInt m_ChildIndex;
  RString m_VariableName;
  RString m_Equation;
};

struct UIDefChild;

struct RUNTIME_EXPORT UIDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDef);

  RPolymorphicBase<UIElementInitDataBase, UIElementTypeDatabase, UIElementDataTypeInfo> m_InitData;

  RMergeList<UIDefInputVariable> m_Inputs;
  RMergeList<UIDefEquation> m_Equations;
  RMergeList<UIDefOutputEquation> m_Outputs;

  RMergeList<UIDefChild> m_Children;
};

struct RUNTIME_EXPORT UIDefChild
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIDefChild);
  UIDef m_UI;
  RString m_Name;
};
