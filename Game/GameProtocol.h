#pragma once

#include "StormNet/NetProtocol.h"
#include "StormNet/NetPipeMessage.h"
#include "StormNet/NetPipeBuffer.h"
#include "StormNet/NetPipeFullState.h"
#include "StormNet/NetPipeDeltaState.h"
#include "StormNet/NetPipeDeltaStateReliable.h"

#include "Game/GameMessages.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkEvents.refl.h"
#include "Game/GameNetworkSettings.h"

using ServerProtocolDef = NetProtocolDefinition<
  NetPipeMessage<ToServerMessage, NetPipeMode::kReliable>,
  NetPipeMessage<ClientNetworkEvent, NetPipeMode::kReliable>,
  NetPipeFullState<ClientAuthData, NetPipeMode::kUnreliableSequenced>>;

using ClientProtocolDef = NetProtocolDefinition<
  NetPipeMessage<FromServerMessage, NetPipeMode::kReliable>,
  NetPipeMessage<GlobalNetworkEvent, NetPipeMode::kReliable>,
  NetPipeMessage<TargetNetworkEvent, NetPipeMode::kReliable>,

#ifdef NETWORK_ALLOW_REWINDING
  NetPipeDeltaState<GameFullState, 255, NetPipeMode::kUnreliableSequenced>,
#else
  NetPipeFullState<GameFullState, NetPipeMode::kUnreliableSequenced>,
#endif

  NetPipeFullState<ClientLocalData, NetPipeMode::kReliable>>;

using ServerProtocol = NetProtocolInfo<ServerProtocolDef>::template AsymmetricProtocolType<ClientProtocolDef>;
using ClientProtocol = NetProtocolInfo<ClientProtocolDef>::template AsymmetricProtocolType<ServerProtocolDef>;
