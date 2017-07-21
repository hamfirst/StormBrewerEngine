
#include "Runtime/RuntimeCommon.h"

#include <StormData/StormDataJson.h>

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/DocumentResource/DocumentResourceManager.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapEffectLayerTypeRegister.h"
#include "Runtime/Volume/VolumeTypeRegister.h"
#include "Runtime/Path/PathTypeRegister.h"
#include "Runtime/Config/ConfigManager.h"

#include "Server/ServerObject/ServerObjectSystem.h"


void RuntimeInit()
{
  g_ConfigRegistrationCallList.CallAll();
  g_ServerObjectRegisterCallList.CallAll();
  g_VolumeRegisterCallList.CallAll();
  g_PathRegisterCallList.CallAll();
  g_MapEffectLayerRegisterCallList.CallAll();

  g_ServerObjectSystem.FinalizeTypes();
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

  g_ConfigTypeManager.RegisterConfigProperties(property_db);
}
