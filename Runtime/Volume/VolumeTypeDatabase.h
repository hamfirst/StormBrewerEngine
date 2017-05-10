#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Runtime/Volume/VolumeDef.refl.h"

class VolumeDataBase;

struct PropertyField;
class PropertyFieldDatabase;

struct VolumeDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

class VolumeTypeDatabase : public StormDataTypeDatabase<VolumeDataBase, VolumeDataTypeInfo>
{
public:
  template <typename Component, typename InitData, typename ... BaseTypes>
  static void RegisterType();
};

