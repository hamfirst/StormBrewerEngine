#pragma once

#include "Runtime/ServerObject/ServerObject.h"
#include "Foundation/Update/UpdateBucketList.h"

class GameLogicContainer;

using ServerObjectUpdateFunc = void (ServerObject::*)(GameLogicContainer &);

extern template class UpdateList<ServerObject, ServerObjectUpdateFunc>;

class ServerObjectUpdateList : public UpdateList<ServerObject, ServerObjectUpdateFunc> {};

