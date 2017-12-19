#pragma once

#include "Runtime/Event/EventSystem.h"
#include "Runtime/ServerObject/ServerObject.h"

class GameLogicContainer;

extern template class EventSystem<ServerObject, ServerObjectHandle>;

class ServerObjectEventSystem : public EventSystem<ServerObject, ServerObjectHandle>
{

};
