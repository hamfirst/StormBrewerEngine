#pragma once

#include "Runtime/Event/EventSystem.h"
#include "Server/ServerObject/ServerObject.h"

class GameLogicContainer;

extern template class EventSystem<ServerObject, ServerObjectHandle, GameLogicContainer &>;

class ServerObjectEventSystem : public EventSystem<ServerObject, ServerObjectHandle, GameLogicContainer &>
{

};
