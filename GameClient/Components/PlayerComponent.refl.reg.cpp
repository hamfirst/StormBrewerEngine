
#include "Foundation/Common.h"

#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentList.h"
#include "Engine/Component/ComponentUpdateRegistrationTemplates.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "GameClient/Components/PlayerComponent.refl.h"
#include "GameClient/Components/PlayerComponent.refl.meta.h"

REGISTER_COMPONENT_WITH_INIT_DATA(PlayerComponent, PlayerComponentInitData, Component);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(PlayerComponentInitData);
