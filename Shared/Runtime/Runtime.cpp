
#include "Runtime/RuntimeCommon.h"

#include <StormData/StormDataJson.h>

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/DocumentResource/DocumentResourceManager.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/Entity/EntityDef.refl.meta.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"
#include "Runtime/VisualEffect/VisualEffectDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapEffectLayerTypeRegister.h"
#include "Runtime/Volume/VolumeTypeRegister.h"
#include "Runtime/Path/PathTypeRegister.h"
#include "Runtime/Anchor/AnchorTypeRegister.h"
#include "Runtime/Config/ConfigManager.h"
#include "Runtime/UI/UIElementTypeRegister.h"
#include "Runtime/SpriteBase/SpriteAnimationEventRegister.h"
#include "Runtime/Asset/Asset.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"
#include "Runtime/ServerObject/ServerObjectInitDataTypeDatabase.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

void RuntimeInit()
{
  g_TypeDatabaseRegisterCallList.CallAll();
  g_ConfigRegistrationCallList.CallAll();
  g_ServerObjectRegisterCallList.CallAll();
  g_UIElementRegisterCallList.CallAll();
  g_GlobalAssetListRegister.CallAll();
  g_GlobalDependentAssetRegister.CallAll();
  g_ServerObjectSystem.FinalizeTypes();
}

void RuntimeCleanup()
{

}

void RuntimeRegisterTypes(PropertyFieldDatabase & property_db)
{
  GetProperyMetaData<SpriteDef>(property_db);
  GetProperyMetaData<EntityDef>(property_db);
  GetProperyMetaData<ServerObjectDef>(property_db);
  GetProperyMetaData<MapEntity>(property_db);
  GetProperyMetaData<MapServerObject>(property_db);
  GetProperyMetaData<MapParalaxLayerObject>(property_db);
  GetProperyMetaData<MapDef>(property_db);
  GetProperyMetaData<UIDef>(property_db);
  GetProperyMetaData<VisualEffectDef>(property_db);

  g_ConfigTypeManager.RegisterConfigProperties(property_db);
  g_UIElementTypeDatabase.RegisterTypes(property_db);
}
