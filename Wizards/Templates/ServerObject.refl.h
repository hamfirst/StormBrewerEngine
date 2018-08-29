#pragma once

#include ""Game/GameCommon.h""

#include ""Game/GameLogicContainer.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""
#include ""Game/Systems/GameLogicSystems.h""

#include ""Runtime/ServerObject/ServerObject.h""
#include ""Runtime/ServerObject/ServerObjectInitData.refl.h""
#include ""Runtime/ServerObject/ServerObjectRegistrationMacros.h""

struct {class_name}InitData : public ServerObjectInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({class_name}InitData);
}};

class {class_name} : public ServerObject
{{
public:
  DECLARE_SERVER_OBJECT;

  {class_name}() = default;
  {class_name}(const {class_name} & rhs) = default;
  {class_name}({class_name} && rhs) = default;

  {class_name} & operator = (const {class_name} & rhs) = default;
  {class_name} & operator = ({class_name} && rhs) = default;

  void Init(const {class_name}InitData & init_data);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);
  
  virtual void InitPosition(const Vector2 & pos) override;
  virtual Vector2 GetPosition(GameLogicContainer & game_container) const override;

  virtual czstr GetDefaultEntityBinding() const override;
public:
  // Serialized variables
  GameNetVec2 m_Position = {};
}};
