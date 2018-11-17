#pragma once

#include "Foundation/Any/Any.h"

#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/TileSheet/TileSheetResource.h"

#define kSpriteDefaultSkin 0

class SpriteEngineData
{
public:
  SpriteEngineData(SpriteBaseDef & sprite);
  SpriteEngineData(const SpriteEngineData & rhs) = delete;
  SpriteEngineData(SpriteEngineData && rhs) = default;

  ~SpriteEngineData();

  void Load();

  void BuildVertexBuffer();
  Optional<Box> Render(RenderState & render_state, int animation_index, int animation_frame, uint32_t skin_name, ShaderProgram & shader);

  static Optional<Box> RenderSprite(SpritePtr & sprite, RenderState & render_state, int animation_index, int animation_frame, uint32_t skin_name_hash,
    const Vector2f & position, const RenderVec4 & matrix = RenderVec4{ 1, 0, 0, 1 }, 
    const Color & color = Color(1.0f, 1.0f, 1.0f, 1.0f), ShaderProgram & shader = g_ShaderManager.GetDefaultWorldSpaceShader());
  static Optional<Box> RenderSprite(NotNullPtr<SpriteResource> resource, RenderState & render_state, int animation_index, int animation_frame, uint32_t skin_name_hash,
    const Vector2f & position, const RenderVec4 & matrix = RenderVec4{ 1, 0, 0, 1 },
    const Color & color = Color(1.0f, 1.0f, 1.0f, 1.0f), ShaderProgram & shader = g_ShaderManager.GetDefaultWorldSpaceShader());

  static Optional<Box> RenderTile(TileSheetPtr & tile_sheet, RenderState & render_state, int animation_index, int animation_frame, uint32_t skin_name_hash,
    const Vector2f & position, const RenderVec4 & matrix = RenderVec4{ 1, 0, 0, 1 }, 
    const Color & color = Color(1.0f, 1.0f, 1.0f, 1.0f), ShaderProgram & shader = g_ShaderManager.GetDefaultWorldSpaceShader());

  static NullOptPtr<TextureAsset> GetSpriteFrame(SpritePtr & sprite, int animation_index, int animation_frame, Box & texture_coords);
  static NullOptPtr<TextureAsset> GetSpriteFrame(NotNullPtr<SpriteResource> resource, int animation_index, int animation_frame, Box & texture_coords);
private:
  SpriteBaseDef & m_Sprite;
  bool m_Reloading;

  int m_TexturesPerSkin;

  std::vector<std::pair<int, int>> m_Frames;
  std::vector<int> m_FrameTextures;
  std::vector<Box> m_FrameTextureCoords;
  std::vector<TextureAsset::LoadCallbackLink> m_Textures;
  std::vector<uint32_t> m_SkinNameHashes;

  VertexBuffer m_VertexBuffer;
};

Any CreateSpriteEngineData(SpriteBaseDef & sprite);
void UpdateSpriteEngineData(Any & engine_data);
void RenderSprite(Any & engine_data, RenderState & render_state, EntityRenderState & entity_render_state, const Vector2 & position);



