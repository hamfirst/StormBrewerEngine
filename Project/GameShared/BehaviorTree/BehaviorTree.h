
#pragma once

#include "StormBehavior/StormBehaviorTree.h"

class BotServerObject;
class GameLogicContainer;

using BotBehaviorTree = StormBehaviorTree<BotServerObject, GameLogicContainer>;
