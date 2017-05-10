#pragma once

#include "Runtime/RuntimeCommon.h"

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

class RUNTIME_EXPORT ComponentInitData
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(ComponentInitData);

  RInt m_Test;
};
