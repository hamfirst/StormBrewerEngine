#include ""GameClient/GameClientCommon.h""

#include ""Engine/Component/ComponentSystem.h""
#include ""Engine/Component/ComponentList.h""
#include ""Engine/Component/ComponentUpdateRegistrationTemplates.h""
#include ""Runtime/Component/ComponentInitDataTypeDatabase.h""
#include ""Runtime/Component/ComponentInitDataTypeDatabaseRegister.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

REGISTER_COMPONENT_WITH_INIT_DATA({class_name}, {class_name}InitData, Component);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({class_name}InitData);
