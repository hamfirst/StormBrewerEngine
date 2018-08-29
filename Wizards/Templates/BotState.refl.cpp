#include ""Game/GameCommon.h""

#include ""Game/GameLogicContainer.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""

#include ""Game/ServerObjects/Bot/BotServerObject.refl.h""
#include ""Game/ServerObjects/Bot/BotSettings.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

#include ""StormNet/NetReflectionTypeDatabase.h""

NET_REGISTER_TYPE({class_name}, BotStateBase);

void {class_name}::Move(BotServerObject & Bot, GameLogicContainer & game_container)
{{

}}

void {class_name}::Transition(BotServerObject & Bot, GameLogicContainer & game_container)
{{

}}

void {class_name}::Animate(BotServerObject & Bot, GameLogicContainer & game_container)
{{
	Bot.FrameAdvance(COMPILE_TIME_CRC32_STR(""Animation""));

    Bot.TriggerAnimationEvents(game_container, *this);
}}
