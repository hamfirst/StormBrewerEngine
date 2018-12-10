#include ""Game/GameCommon.h""
#include ""Foundation/SkipField/SkipField.h""

#include ""StormRefl/StormReflMetaFuncs.h""
#include ""StormRefl/StormReflJsonStd.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""Runtime/Config/ConfigRegistrationMacros.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

REGISTER_CONFIG_TYPE({class_name}, ""{friendly_name}"", ""{class_name_lower}"", ""Configs"");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({class_name});
