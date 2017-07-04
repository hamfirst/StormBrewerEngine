#pragma once

#include "StormNet/NetProtocol.h"
#include "StormNet/NetPipeMessage.h"
#include "StormNet/NetPipeBuffer.h"
#include "StormNet/NetPipeFullState.h"
#include "StormNet/NetPipeDeltaState.h"
#include "StormNet/NetPipeDeltaStateReliable.h"

#include "Game/GameFullState.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/GameNetworkEvents.refl.meta.h"

#include "Game/GameNetworkSettings.h"

using ServerProtocolDef = NetProtocolDefinition<
  NetPipeMessage<ToServerMessage, NetPipeMode::kReliable>,
  NetPipeMessage<ClientNetworkEvent, NetPipeMode::kReliable>,
  NetPipeFullState<ClientAuthData, NetPipeMode::kUnreliableSequenced>>;

using ClientProtocolDef = NetProtocolDefinition<
  NetPipeMessage<FromServerMessage, NetPipeMode::kReliable>,
  NetPipeMessage<GlobalNetworkEvent, NetPipeMode::kReliable>,
  NetPipeMessage<TargetNetworkEvent, NetPipeMode::kReliable>,

#if NET_MODE == NET_MODE_GGPO
  NetPipeDeltaState<GameFullState, 255, NetPipeMode::kUnreliableSequenced>,
#elif NET_MODE == NET_MODE_TURN_BASED_DETERMINISTIC
  NetPipeFullState<GameFullState, NetPipeMode::kReliable>,
#else
  NetPipeFullState<GameFullState, NetPipeMode::kUnreliableSequenced>,
#endif

  NetPipeFullState<ClientLocalData, NetPipeMode::kReliable>>;

using ServerProtocol = NetProtocolInfo<ServerProtocolDef>::template AsymmetricProtocolType<ClientProtocolDef>;
using ClientProtocol = NetProtocolInfo<ClientProtocolDef>::template AsymmetricProtocolType<ServerProtocolDef>;
