#include ""Game/GameCommon.h""

#include ""Game/GameLogicContainer.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""

#include ""Game/ServerObjects/Player/PlayerServerObject.refl.h""

#include ""{rel_path}/{refl_header_file}""
#include ""{rel_path}/{refl_meta_file}""

#include ""StormNet/NetReflectionTypeDatabase.h""

NET_REGISTER_TYPE({class_name}, PlayerStateBase);

void {class_name}::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{{

}}

void {class_name}::Transition(PlayerServerObject & player, GameLogicContainer & game_container)
{{

}}

void {class_name}::Animate(PlayerServerObject & player, GameLogicContainer & game_container)
{{
  player.FrameAdvance(COMPILE_TIME_CRC32_STR(""Animation""));
  player.TriggerAnimationEvents(game_container, *this);
}}
