#pragma once

#include "Foundation/Any/Any.h"

#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Entity/Entity.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/TileSheet/TileSheetResource.h"

class SpriteEngineData
{
public:
  SpriteEngineData(SpriteBaseDef & sprite);
  SpriteEngineData(const SpriteEngineData & rhs) = delete;
  SpriteEngineData(SpriteEngineData && rhs) = default;

  ~SpriteEngineData();

  void Load();

  void BuildVertexBuffer();
  Optional<Box> Render(int animation_index, int animation_frame, const ShaderProgram & shader) const;

  static Optional<Box> RenderSprite(const SpritePtr & sprite, int animation_index, int animation_frame, const ShaderProgram & shader);
  static Optional<Box> RenderTile(const TileSheet & tile_sheet, int animation_index, int animation_frame, const ShaderProgram & shader);

  static NullOptPtr<TextureAsset> GetSpriteFrame(const SpritePtr & sprite, int animation_index, int animation_frame, Box & texture_coords);
private:
  SpriteBaseDef & m_Sprite;
  bool m_Reloading;

  std::vector<std::pair<int, int>> m_Frames;
  std::vector<int> m_FrameTextures;
  std::vector<Box> m_FrameTextureCoords;
  std::vector<TextureAsset::LoadCallbackLink> m_Textures;

  VertexBuffer m_VertexBuffer;
};

Any CreateSpriteEngineData(SpriteBaseDef & sprite);
void UpdateSpriteEngineData(Any & engine_data);
void RenderSprite(Any & engine_data, EntityRenderState & render_state, Vector2 & position);



