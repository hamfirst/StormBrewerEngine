
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"

#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"
#include "Runtime/Asset/Asset.h"

#include "Engine/Entity/Entity.h"
#include "Engine/Asset/AudioAsset.h"

#include "GameClient/Components/Reusable/AttachVfxComponent.refl.h"
#include "GameClient/Components/Reusable/AttachVfxComponent.refl.meta.h"

AttachVfxComponent::AttachVfxComponent(AttachVfxComponentInitData && init_data)
{
  m_VfxAsset = VisualEffectResource::Load(init_data.m_VfxFile.data());
  m_SpawnFinalParticle = init_data.m_SpawnFinalParticle;
  m_InitialUpdate = true;
  m_AttachAnchorHash = crc32(init_data.m_AttachAnchor.data());
  m_LayerOffset = init_data.m_LayerOffset;
}

AttachVfxComponent::~AttachVfxComponent()
{
  
}


void AttachVfxComponent::OnDestroy()
{
  auto vfx = m_Vfx.Resolve();
  if (vfx)
  {
    vfx->StopSpawning();
  }
}

void AttachVfxComponent::UpdateLast()
{
  if (m_InitialUpdate)
  {
    if (m_VfxAsset->IsLoaded())
    {
      auto vfx = CreateVisualEffect(m_VfxAsset, GetEntity()->GetLayer() + m_LayerOffset, GetEntity()->GetPosition());
      m_Vfx = vfx->GetHandle();
    }

    m_InitialUpdate = false;
  }

  auto vfx = m_Vfx.Resolve();
  if (vfx)
  {
    auto pos = GetEntity()->GetPosition();
    if (m_AttachAnchorHash)
    {
      auto & sprite = GetEntity()->GetSprite();
      auto & anim_state = GetEntity()->GetAnimationState();
      auto frame_id = sprite->GetAnimationFrameId(anim_state.m_AnimIndex, anim_state.m_AnimFrame);

      auto anchor = (Vector2f)sprite->GetAnchor(m_AttachAnchorHash, frame_id);
      anchor.x *= GetEntity()->GetRenderState().m_Matrix.x;

      pos += anchor;
    }

    vfx->SetPosition(pos);
  }
}
