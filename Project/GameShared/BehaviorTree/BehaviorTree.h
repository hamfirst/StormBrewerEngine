
#pragma once

#include "StormBehavior/StormBehaviorTree.h"

class BotServerObject;
class GameWorld;

using BotBehaviorTree = StormBehaviorTree<BotServerObject, GameWorld>;
