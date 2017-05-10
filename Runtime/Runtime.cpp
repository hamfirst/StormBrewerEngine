
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Component/ComponentSystem.h"
#include "Runtime/DocumentResource/DocumentResourceManager.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include <StormData/StormDataJson.h>



void RuntimeInit()
{
  g_ComponentRegisterCallList.CallAll();
  g_ComponentUpdateDepRegisterCallList.CallAll();

  g_ComponentTypeSystem.FinalizeComponentSystem();
}

void RuntimeCleanup()
{

}

void RuntimeRegisterTypes(PropertyFieldDatabase & property_db)
{
  GetProperyMetaData<SpriteDef>(property_db);
  GetProperyMetaData<EntityDef>(property_db);
  GetProperyMetaData<MapEntity>(property_db);
  GetProperyMetaData<MapDef>(property_db);
}
