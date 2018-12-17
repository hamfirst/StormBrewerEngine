
#include "Engine/EngineCommon.h"
#include "Engine/Atlas/AtlasEngineData.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"

#include <sb/vector.h>

AtlasEngineData::AtlasEngineData(AtlasDef & Atlas) :
        m_Atlas(Atlas),
        m_Reloading(false),
        m_VertexBuffer(true)
{

}

AtlasEngineData::~AtlasEngineData()
{

}

void AtlasEngineData::Load()
{
  std::vector<TextureAsset::AssetRef> old_textures = std::move(m_Textures);

  m_Reloading = true;
  for(auto elem : m_Atlas.m_Elements)
  {
    ElementLookupData lookup_data;
    lookup_data.m_NameHash = crc32lowercase(elem.second.m_Name.data());
    lookup_data.m_Index = elem.first;

    bool found_texture = false;
    std::size_t texture_index = 0;
    for(auto tex : m_Atlas.m_Textures)
    {
      auto file_name_hash = crc32lowercase(tex.second.m_Filename.data());
      if(file_name_hash == elem.second.m_TextureHash)
      {
        lookup_data.m_TextureIndex = texture_index;
        found_texture = true;
        break;
      }

      texture_index++;
    }

    if(found_texture == false)
    {
      continue;
    }

    auto & elem_data = elem.second.m_Data;

    switch((AtlasDefType)elem_data.m_Type)
    {
      case AtlasDefType::kImage:
        lookup_data.m_MinSize.x = elem_data.m_EndX - elem_data.m_StartX + 1;
        lookup_data.m_MinSize.y = elem_data.m_EndY - elem_data.m_StartY + 1;
        break;
      case AtlasDefType::kRepeat:
        lookup_data.m_MinSize.x = 0;
        lookup_data.m_MinSize.y = 0;
        break;
      case AtlasDefType::k3SliceHorizontal:
        lookup_data.m_MinSize.x = elem_data.m_StartOffsetX + elem_data.m_EndOffsetX;
        lookup_data.m_MinSize.y = elem_data.m_EndY - elem_data.m_StartY + 1;
        break;
      case AtlasDefType::k3SliceVertical:
        lookup_data.m_MinSize.x = elem_data.m_EndX - elem_data.m_StartX + 1;
        lookup_data.m_MinSize.x = elem_data.m_StartOffsetY + elem_data.m_EndOffsetY;
        break;
      case AtlasDefType::k9Slice:
        lookup_data.m_MinSize.x = elem_data.m_StartOffsetX + elem_data.m_EndOffsetX;
        lookup_data.m_MinSize.x = elem_data.m_StartOffsetY + elem_data.m_EndOffsetY;
        break;
    }

    m_ElementLookup.push_back(lookup_data);
  }

  for (auto elem : m_Atlas.m_Textures)
  {
    m_Textures.push_back(TextureAsset::Load(elem.second.m_Filename.data(), false));
  }

  m_Reloading = false;
}

void AtlasEngineData::Render(RenderState & render_state, czstr name, const Box & pos, const Color & color)
{
  auto name_hash = crc32lowercase(name);
  auto position = pos;

  ElementLookupData * index_lookup = nullptr;
  for(auto & elem : m_ElementLookup)
  {
    if(elem.m_NameHash == name_hash)
    {
      index_lookup = &elem;
      break;
    }
  }

  if(index_lookup == nullptr)
  {
    return;
  }

  auto & elem_def = m_Atlas.m_Elements[index_lookup->m_Index].m_Data;
  auto & texture = m_Textures[index_lookup->m_TextureIndex];

  if(texture.IsLoaded() == false)
  {
    return;
  }

  auto pos_size = position.Size();
  if(pos_size.x < index_lookup->m_MinSize.x)
  {
    position.m_End.x = position.m_Start.x + index_lookup->m_MinSize.x;
  }
  if(pos_size.y < index_lookup->m_MinSize.y)
  {
    position.m_End.y = position.m_Start.y + index_lookup->m_MinSize.y;
  }

  QuadVertexBufferBuilder buffer_builder;

  QuadVertexBuilderInfo quad;
  quad.m_Color = color;
  quad.m_TextureSize = texture->GetSize();

  if (elem_def.m_Type == AtlasDefType::k9Slice)
  {
    // Bottom left
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_StartOffsetX, elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_StartOffsetX, elem_def.m_StartOffsetY };
    buffer_builder.AddQuad(quad);

    // Top left
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_StartOffsetX, elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_StartOffsetX, elem_def.m_EndOffsetY };
    buffer_builder.AddQuad(quad);

    // Bottom right
    quad.m_Position.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_EndOffsetX, elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_EndOffsetX, elem_def.m_StartOffsetY };
    buffer_builder.AddQuad(quad);

    // Top right
    quad.m_Position.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_EndOffsetX, elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_EndOffsetX, elem_def.m_EndOffsetY };
    buffer_builder.AddQuad(quad);

    int repeat_width = (int)(position.m_End.x - position.m_Start.x - elem_def.m_StartOffsetX - elem_def.m_EndOffsetX);
    int repeat_height = (int)(position.m_End.y - position.m_Start.y - elem_def.m_StartOffsetY - elem_def.m_EndOffsetY);

    int repeat_texture_width = (int)(elem_def.m_EndX - elem_def.m_StartX - elem_def.m_StartOffsetX - elem_def.m_EndOffsetX);
    int repeat_texture_height = (int)(elem_def.m_EndY - elem_def.m_StartY - elem_def.m_StartOffsetY - elem_def.m_EndOffsetY);

    // Left side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y + elem_def.m_StartOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_StartOffsetX, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, elem_def.m_StartY + elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_EndOffsetX, elem_def.m_StartY + repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);

    // Right side
    quad.m_Position.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, position.m_Start.y + elem_def.m_StartOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_EndOffsetX, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, elem_def.m_StartY + elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_EndOffsetX, repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);

    // Bottom side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x + elem_def.m_StartOffsetX, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX + elem_def.m_StartOffsetX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, elem_def.m_StartOffsetY };
    buffer_builder.AddRepeatingQuad(quad);

    // Top side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x + elem_def.m_StartOffsetX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX + elem_def.m_StartOffsetX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, elem_def.m_EndOffsetY };
    buffer_builder.AddRepeatingQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ position.m_Start.x + elem_def.m_StartOffsetX, position.m_Start.y + elem_def.m_StartOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX + elem_def.m_StartOffsetX, elem_def.m_StartY + elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);
  }
  else if (elem_def.m_Type == AtlasDefType::k3SliceHorizontal)
  {
    int height = (int)(position.m_End.y - position.m_Start.y);
    int texture_height = (int)(position.m_End.y - elem_def.m_StartY);

    int repeat_width = (int)(position.m_End.x - position.m_Start.x - elem_def.m_StartOffsetX - elem_def.m_EndOffsetX);
    int repeat_texture_width = (int)(position.m_End.x - position.m_Start.x - elem_def.m_StartOffsetX - elem_def.m_EndOffsetX);

    // Left side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_StartOffsetX, height };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_StartOffsetX, texture_height };
    buffer_builder.AddQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ position.m_Start.x + elem_def.m_StartOffsetX, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, height };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX + elem_def.m_StartOffsetX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, texture_height };
    buffer_builder.AddQuad(quad);

    // Right side
    quad.m_Position.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ elem_def.m_EndOffsetX, height };
    quad.m_TexCoords.m_Start = Vector2{ position.m_End.x - elem_def.m_EndOffsetX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ elem_def.m_EndOffsetX, texture_height };
    buffer_builder.AddQuad(quad);
  }
  else if (elem_def.m_Type == AtlasDefType::k3SliceVertical)
  {
    int width = (int)(position.m_End.x - position.m_Start.x);
    int texture_width = (int)(position.m_End.x - elem_def.m_StartX);

    int repeat_height = (int)(position.m_End.y - position.m_Start.y - elem_def.m_StartOffsetY - elem_def.m_EndOffsetY);
    int repeat_texture_height = (int)(elem_def.m_EndY - elem_def.m_StartY - elem_def.m_StartOffsetY - elem_def.m_EndOffsetY);

    // Bottom side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, elem_def.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, elem_def.m_StartOffsetY };
    buffer_builder.AddQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y + elem_def.m_StartOffsetX };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, elem_def.m_StartY + elem_def.m_StartOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, repeat_texture_height };
    buffer_builder.AddQuad(quad);

    // Top side
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_Start = Vector2{ elem_def.m_StartX, position.m_End.y - elem_def.m_EndOffsetY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, elem_def.m_EndOffsetY };
    buffer_builder.AddQuad(quad);
  }
  else if(elem_def.m_Type == AtlasDefType::kImage)
  {
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y };
    quad.m_Position.m_End = Vector2{ position.m_End.x, position.m_End.y };
    quad.m_TexCoords.m_Start = Vector2{ 0, 0 };
    quad.m_TexCoords.m_End = texture->GetSize();
    buffer_builder.AddQuad(quad);
  }
  else
  {
    quad.m_Position.m_Start = Vector2{ position.m_Start.x, position.m_Start.y };
    quad.m_Position.m_End = Vector2{ position.m_End.x, position.m_End.y };
    quad.m_TexCoords.m_Start = Vector2{ 0, 0 };
    quad.m_TexCoords.m_End = texture->GetSize();
    buffer_builder.AddRepeatingQuad(quad);
  }

  buffer_builder.FillVertexBufferInvertY(m_VertexBuffer, pos);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  render_state.BindShader(shader);

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec2{ render_state.GetRenderSize() });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ 0, 0 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  render_state.BindTexture(*texture);
  render_state.BindVertexBuffer(m_VertexBuffer);
  render_state.Draw();
}

Any CreateAtlasEngineData(AtlasDef & Atlas)
{
  return Any(AtlasEngineData(Atlas));
}

void UpdateAtlasEngineData(Any & engine_data)
{
  AtlasEngineData * atlas_data = engine_data.Get<AtlasEngineData>();
  if (atlas_data == nullptr)
  {
    return;
  }

  atlas_data->Load();
}

void RenderAtlas(Any & engine_data, RenderState & render_state, czstr name, const Box & position, const Color & color)
{
  AtlasEngineData * atlas_data = engine_data.Get<AtlasEngineData>();
  if (atlas_data == nullptr)
  {
    return;
  }

  atlas_data->Render(render_state, name, position);
}
