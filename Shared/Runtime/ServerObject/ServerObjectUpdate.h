#pragma once

#include "Runtime/ServerObject/ServerObject.h"
#include "Foundation/Update/UpdateBucketList.h"

class GameWorld;

using ServerObjectUpdateFunc = void (ServerObject::*)(GameWorld &);

extern template class UpdateList<ServerObject, ServerObjectUpdateFunc>;

class ServerObjectUpdateList : public UpdateList<ServerObject, ServerObjectUpdateFunc> {};

