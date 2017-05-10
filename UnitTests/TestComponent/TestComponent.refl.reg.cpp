
#include "Foundation/Common.h"
#include "Runtime/Component/ComponentSystem.h"
#include "Runtime/Component/ComponentList.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"
#include "Runtime/Component/ComponentInitDataTypeDatabaseRegister.h"
#include "Runtime/Component/ComponentUpdateRegistrationTemplates.h"

#include <StormData/StormData.h>
#include <StormData/StormDataJson.h>

#include "UnitTests/TestComponent/TestComponent.refl.h"
#include "UnitTests/TestComponent/TestComponent.refl.meta.h"

REGISTER_COMPONENT_WITH_INIT_DATA(TestComponent, TestComponentInitData, Component);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(TestComponentInitData);
