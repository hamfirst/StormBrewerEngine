#pragma once

#include "Foundation/TypeDatabase/TypeDatabase.h"

#include "Runtime/Map/MapEffectLayerDef.refl.h"

template <typename DataType, typename LogicType>
struct TypeDatabaseInitLogicInfo<DataType, LogicType, MapEffectLayerLogicInfo>
{
  static void Process(MapEffectLayerLogicInfo & logic_type_info)
  {
    logic_type_info.m_CreateCodeObj = [](void *ptr)
    {
      auto data = static_cast<DataType *>(ptr);
      return std::make_unique<LogicType>(*data);
    };
  }
};

