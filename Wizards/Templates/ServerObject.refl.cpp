
#include ""Game/GameCommon.h""

#include ""Game/GameController.refl.h""
#include ""Game/GameServerEventSender.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

void {class_name}::Init(const {class_name}InitData & init_data)
{{

}}

void {class_name}::UpdateFirst(GameLogicContainer & game_container)
{{

}}

void {class_name}::UpdateMiddle(GameLogicContainer & game_container)
{{

}}

void {class_name}::InitPosition(const Vector2 & pos)
{{
  m_Position = GameNetVec2(pos.x, pos.y);
}}

Vector2 {class_name}::GetPosition(GameLogicContainer & game_container) const
{{
  return m_Position;
}}

czstr {class_name}::GetDefaultEntityBinding() const
{{
  return {entity_binding};
}}
