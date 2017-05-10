#pragma once

#include "StormNet/NetProtocol.h"
#include "StormNet/NetPipeMessage.h"
#include "StormNet/NetPipeBuffer.h"
#include "StormNet/NetPipeFullState.h"
#include "StormNet/NetPipeDeltaState.h"
#include "StormNet/NetPipeDeltaStateReliable.h"

#include "Game/GameMessages.refl.h"
#include "Game/GameSimulation.refl.h"

using ServerProtocolDef = NetProtocolDefinition<
  NetPipeMessage<ToServerMessage, NetPipeMode::kReliable>,
  NetPipeFullState<ClientAuthData, NetPipeMode::kUnreliableSequenced>>;

using ClientProtocolDef = NetProtocolDefinition<
  NetPipeMessage<FromServerMessage, NetPipeMode::kReliable>,
  NetPipeDeltaState<GameSimulation, 255, NetPipeMode::kUnreliableSequenced>,
  NetPipeFullState<ClientLocalData, NetPipeMode::kReliable>,
  NetPipeMessage<SimEventBase, NetPipeMode::kReliable>>;

using ServerProtocol = NetProtocolInfo<ServerProtocolDef>::template AsymmetricProtocolType<ClientProtocolDef>;
using ClientProtocol = NetProtocolInfo<ClientProtocolDef>::template AsymmetricProtocolType<ServerProtocolDef>;
