
#pragma once

#include "GameClient/GameClientCommon.h"
#include "Runtime/Component/ComponentInitData.refl.h"
#include "Engine/Component/Component.h"

struct AttachVfxComponentInitData : public ComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(AttachVfxComponentInitData);

  RString STORM_REFL_ATTR_VAL(file, vfx) m_VfxFile;
  RBool m_SpawnFinalParticle;
  RString m_AttachAnchor;
  RInt m_LayerOffset;
};

class AttachVfxComponent : public Component
{
public:
  DECLARE_COMPONENT;

  AttachVfxComponent(AttachVfxComponentInitData && init_data);
  virtual ~AttachVfxComponent();

  void OnDestroy() override;

  void UpdateLast();

private:
  VisualEffectResourcePtr m_VfxAsset;
  VisualEffectHandle m_Vfx;

  bool m_InitialUpdate;
  bool m_SpawnFinalParticle;

  uint32_t m_AttachAnchorHash;
  int m_LayerOffset;
};
