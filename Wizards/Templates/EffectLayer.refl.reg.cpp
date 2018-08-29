#include ""GameClient/GameClientCommon.h""

#include ""Foundation/PropertyMeta/PropertyFieldMetaFuncs.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""Runtime/Map/MapEffectLayerTypeDatabase.h""
#include ""Runtime/Map/MapEffectLayerTypeRegister.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

REGISTER_EFFECT_LAYER_DATA({component_name}, {class_name}InitData);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({class_name}InitData);
