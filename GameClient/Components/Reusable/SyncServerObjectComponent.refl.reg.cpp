
#include "GameClient/GameClientCommon.h"

#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentList.h"
#include "Engine/Component/ComponentUpdateRegistrationTemplates.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "GameClient/Components/Reusable/SyncServerObjectComponent.refl.h"
#include "GameClient/Components/Reusable/SyncServerObjectComponent.refl.meta.h"

REGISTER_COMPONENT_WITH_INIT_DATA(SyncServerObjectComponent, SyncServerObjectComponentInitData, Component);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(SyncServerObjectComponentInitData);
