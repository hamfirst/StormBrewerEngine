#pragma once

#include "Foundation/SpatialDatabase/SpatialDatabase.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/VisualEffect/VisualEffectResource.h"
#include "Runtime/Animation/AnimationState.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/VisualEffect/VisualEffectHandle.h"

class RenderState;

struct MapParalaxLayerTexture
{
  AssetReference<TextureAsset> m_Texture;
  Vector2 m_Pos;
};

struct MapParalaxLayerSprite
{
  SpritePtr m_Sprite;
  Vector2 m_Pos;
  AnimationState m_State;
  uint32_t m_AnimationHash;
};

struct MapParalaxLayerVfx
{
  VisualEffectResourcePtr m_Vfx;
  VisualEffectHandle m_Handle;
};

class MapParalaxLayerInstance
{
public:

  MapParalaxLayerInstance(MapDef & map, std::size_t layer_index, NotNullPtr<VisualEffectManager> vfx_manager);
  ~MapParalaxLayerInstance();

  void Update();
  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state);

  int GetLayerOrder() const;

private:

  AssetReference<TextureAsset> m_Texture;

  std::vector<MapParalaxLayerTexture> m_Textures;
  std::vector<MapParalaxLayerSprite> m_Sprites;
  std::vector<MapParalaxLayerVfx> m_VisualEffects;

  int m_LayerOrder;

  bool m_RepeatX;
  bool m_RepeatY;

  float m_OffsetX;
  float m_OffsetY;

  float m_ParalaxX;
  float m_ParalaxY;

  float m_VelocityX;
  float m_VelocityY;
};
