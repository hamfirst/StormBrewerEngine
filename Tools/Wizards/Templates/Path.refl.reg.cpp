#include ""Game/GameCommon.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataTypeDatabase.h""
#include ""StormData/StormDataParent.h""

#include ""Runtime/Path/PathTypeDatabase.h""
#include ""Runtime/Path/PathTypeRegister.h""

#include ""Foundation/PropertyMeta/PropertyFieldMetaFuncs.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({class_name});
REGISTER_PATH_DATA({class_name});
