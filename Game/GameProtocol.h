#pragma once

#include "StormNet/NetProtocol.h"
#include "StormNet/NetPipeMessage.h"
#include "StormNet/NetPipeBuffer.h"
#include "StormNet/NetPipeFullState.h"
#include "StormNet/NetPipeVariant.h"
#include "StormNet/NetPipeDeltaState.h"
#include "StormNet/NetPipeDeltaStateReliable.h"
#include "StormNet/NetReflection.h"

#include "Game/GameFullState.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"

#include "Game/GameNetworkSettings.h"

using ServerProtocolDef = NetProtocolDefinition<
  NetPipeMessage<ToServerMessage, NetPipeMode::kReliable>,
#if NET_MODE == NET_MODE_GGPO
  NetPipeFullState<GameGGPOClientUpdate, NetPipeMode::kUnreliableSequenced>>;
#else
  NetPipeMessage<ClientNetworkEvent, NetPipeMode::kReliable>,
  NetPipeFullState<ClientAuthData, NetPipeMode::kUnreliableSequenced>>;
#endif

using ClientProtocolDef = NetProtocolDefinition<
  NetPipeMessage<FromServerMessage, NetPipeMode::kReliable>,

#if NET_MODE == NET_MODE_GGPO
  NetPipeVariant<NetPipeMode::kUnreliableSequenced, GameGGPOServerGameState, GameStateStaging, GameStateLoading>>;
#else
  NetPipeMessage<GlobalNetworkEvent, NetPipeMode::kReliable>,
  NetPipeMessage<TargetNetworkEvent, NetPipeMode::kReliable>,

  NetPipeFullStateSeq<GameFullState, NetPipeMode::kUnreliableSequenced>,
  NetPipeFullState<ClientLocalData, NetPipeMode::kReliable>,
#if NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  NetPipeFullState<GameFullState, NetPipeMode::kReliable>>;
#else
  NetPipeFullState<GameFullState, NetPipeMode::kUnreliableSequenced>>;
#endif
#endif

using ServerProtocol = NetProtocolInfo<ServerProtocolDef>::template AsymmetricProtocolType<ClientProtocolDef>;
using ClientProtocol = NetProtocolInfo<ClientProtocolDef>::template AsymmetricProtocolType<ServerProtocolDef>;
