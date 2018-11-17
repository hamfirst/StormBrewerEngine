
#pragma once

#include "GameClient/GameClientCommon.h"
#include "Runtime/Component/ComponentInitData.refl.h"
#include "Engine/Component/Component.h"

struct SyncServerObjectComponentInitData : public ComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(SyncServerObjectComponentInitData);

  RBool m_SyncSprite;
};

class SyncServerObjectComponent : public Component
{
public:
  DECLARE_COMPONENT;

  SyncServerObjectComponent(SyncServerObjectComponentInitData && init_data);
  virtual ~SyncServerObjectComponent();

  void UpdateFirst();

private:
  bool m_SyncSprite;
};
