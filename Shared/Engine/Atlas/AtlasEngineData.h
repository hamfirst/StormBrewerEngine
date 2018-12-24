#pragma once

#include "Foundation/Any/Any.h"

#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/Atlas/AtlasDef.refl.h"
#include "Runtime/Atlas/AtlasResource.h"
#include "Runtime/TileSheet/TileSheetResource.h"

class AtlasEngineData
{
public:
  AtlasEngineData(AtlasDef & Atlas);
  AtlasEngineData(const AtlasEngineData & rhs) = delete;
  AtlasEngineData(AtlasEngineData && rhs) = default;

  ~AtlasEngineData();

  void Load();

  void SetupRender(RenderState & render_state, czstr name, const Box & position, const Color & color = Color(255, 255, 255, 255));
  void Render(RenderState & render_state, czstr name, const Box & position,
          const Color & color = Color(255, 255, 255, 255), ShaderProgram & shader = g_ShaderManager.GetDefaultWorldSpaceShader());

private:
  AtlasDef & m_Atlas;
  bool m_Reloading;

  struct ElementLookupData
  {
    uint32_t m_NameHash;
    std::size_t m_Index;
    std::size_t m_TextureIndex;
    Vector2 m_MinSize;
  };

  std::vector<ElementLookupData> m_ElementLookup;
  std::vector<TextureAsset::AssetRef> m_Textures;

  VertexBuffer m_VertexBuffer;
};

Any CreateAtlasEngineData(AtlasDef & Atlas);
void UpdateAtlasEngineData(Any & engine_data);
void RenderAtlas(Any & engine_data, RenderState & render_state, EntityRenderState & entity_render_state,
        const Vector2 & position, const Color & color = Color(255, 255, 255, 255));



