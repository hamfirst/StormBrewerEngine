

#include "Game/GameCommon.h"


#include "GameShared/GameLogicContainer.h"
#include "Game/NetworkEvents/GameServerEventSender.h"
#include "Game/Stage/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"

#include "StormNet/NetReflectionTypeDatabaseRegister.h"

NET_REGISTER_BASE_TYPE_ABSTRACT(PlayerStateBase);
NET_SET_DEFAULT_TYPE(PlayerStateBase, PlayerStateIdle);

