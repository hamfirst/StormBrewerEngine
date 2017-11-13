
#include "Engine/EngineCommon.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

#include <sb/vector.h>

SpriteEngineData::SpriteEngineData(SpriteBaseDef & sprite) :
  m_Sprite(sprite),
  m_Reloading(false),
  m_TexturesPerSkin(0)
{

}

SpriteEngineData::~SpriteEngineData()
{

}

void SpriteEngineData::Load()
{
  std::vector<TextureAsset::LoadCallbackLink> old_textures = std::move(m_Textures);

  m_Reloading = true;
  m_TexturesPerSkin = 0;
  for (auto elem : m_Sprite.m_Textures)
  {
    m_Textures.push_back(TextureAsset::LoadWithCallback(elem.second.m_Filename.data(), [this](NullOptPtr<TextureAsset>) { BuildVertexBuffer(); }));
    m_TexturesPerSkin++;
  }

  m_SkinNameHashes.clear();
  for (auto elem : m_Sprite.m_Skins)
  {
    m_SkinNameHashes.emplace_back(crc32(elem.second.m_Name.ToString()));

    for (auto tex : m_Sprite.m_Textures)
    {
      auto tex_hash = crc32lowercase(tex.second.m_Filename.ToString());

      bool found = false;
      for (auto rep : elem.second.m_TextureReplacements)
      {
        if (crc32lowercase(rep.second.m_Texture.ToString()) == tex_hash)
        {
          m_Textures.push_back(TextureAsset::LoadWithCallback(rep.second.m_Replacement.data(), [this](NullOptPtr<TextureAsset>) {}));
          found = true;
          break;
        }
      }

      if (found == false)
      {
        m_Textures.push_back(TextureAsset::LoadWithCallback(tex.second.m_Filename.data(), [this](NullOptPtr<TextureAsset>) {}));
      }
    }
  }

  m_Reloading = false;
  BuildVertexBuffer();
}

void SpriteEngineData::BuildVertexBuffer()
{
  if (m_Reloading)
  {
    return;
  }

  std::vector<std::pair<uint32_t, std::size_t>> texture_lookup;
  for (auto elem : m_Sprite.m_Textures)
  {
    texture_lookup.emplace_back(std::make_pair(crc32(elem.second.m_Filename.data()), elem.first));
  }

  m_Frames.clear();

  QuadVertexBufferBuilder builder;
  QuadVertexBuilderInfo default_frame = {};
  default_frame.m_TextureSize = Vector2(1, 1);

  int frame_index = 0;

  for (auto anim : m_Sprite.m_Animations)
  {
    int start_frame = frame_index;

    for (auto frame : anim.second.m_Frames)
    {
      frame_index++;
    }

    m_Frames.push_back(std::make_pair(start_frame, frame_index - start_frame));
  }

  for (auto anim : m_Sprite.m_Animations)
  {
    for (auto frame : anim.second.m_Frames)
    {
      uint64_t frame_id = frame.second.m_FrameId;
      int frame_index = (int)(frame_id & 0xFFFFFF);
      uint32_t texture_hash = (uint32_t)(frame_id >> 32);
      int texture_index = -1;
      std::size_t texture_id = 0;

      for (std::size_t index = 0, end = texture_lookup.size(); index < end; ++index)
      {
        if (texture_lookup[index].first == texture_hash)
        {
          texture_index = (int)index;
          texture_id = texture_lookup[index].second;
          break;
        }
      }

      m_FrameTextures.push_back(texture_index);
      m_FrameTextureCoords.emplace_back(Box{});

      auto & frame_coords = m_FrameTextureCoords.back();

      if (texture_index == -1)
      {
        builder.AddQuad(default_frame);
        continue;
      }

      auto texture_asset = m_Textures[texture_index].Get();
      if (texture_asset == nullptr || texture_asset->IsLoaded() == false)
      {
        builder.AddQuad(default_frame);
        continue;
      }

      if (texture_asset->GetWidth() <= 0 || texture_asset->GetHeight() <= 0)
      {
        builder.AddQuad(default_frame);
        continue;
      }

      auto & texture_data = m_Sprite.m_Textures[(int)texture_id];

      auto frames_per_line = (texture_asset->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;
      
      int src_x = (frame_index % frames_per_line) * texture_data.m_FrameWidth;
      int src_y = texture_asset->GetHeight() - texture_data.m_FrameHeight - (frame_index / frames_per_line) * texture_data.m_FrameHeight;

      Vector2 texture_size = Vector2(texture_data.m_FrameWidth, texture_data.m_FrameHeight);
      Vector2 half_texture_size = texture_size / 2;

      QuadVertexBuilderInfo quad;
      quad.m_Position.m_Start = half_texture_size * -1;
      quad.m_Position.m_End = quad.m_Position.m_Start + texture_size;

      quad.m_TextureSize = Vector2(texture_asset->GetWidth(), texture_asset->GetHeight());
      quad.m_TexCoords.m_Start = Vector2(src_x, src_y);
      quad.m_TexCoords.m_End = Vector2(src_x + texture_data.m_FrameWidth, src_y + texture_data.m_FrameHeight);
      quad.m_Color = Color(255, 255, 255, 255);

      frame_coords = quad.m_TexCoords;

      builder.AddQuad(quad);
    }
  }

  builder.FillVertexBuffer(m_VertexBuffer);
}

Optional<Box> SpriteEngineData::Render(int animation_index, int animation_frame, uint32_t skin_name_hash, const ShaderProgram & shader) const
{
  if (animation_index < 0 || animation_index >= m_Frames.size())
  {
    return{};
  }

  if (animation_frame < 0 || animation_frame >= m_Frames[animation_index].second)
  {
    return{};
  }

  int frame_index = m_Frames[animation_index].first + animation_frame;
  auto texture_index = m_FrameTextures[frame_index];
  if (texture_index == -1)
  {
    return{};
  }

  if (skin_name_hash == 0)
  {
    m_Textures[texture_index].Get()->GetTexture().BindTexture(0);
  }
  else
  {
    bool found_name = false;
    for (std::size_t index = 0, end = m_SkinNameHashes.size(); index < end; ++index)
    {
      if (m_SkinNameHashes[index] == skin_name_hash)
      {
        m_Textures[(index + 1) * m_TexturesPerSkin + texture_index].Get()->GetTexture().BindTexture(0);
        found_name = true;
        break;
      }
    }

    if (found_name == false)
    {
      m_Textures[texture_index].Get()->GetTexture().BindTexture(0);
    }
  }

  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(shader);
  m_VertexBuffer.Draw(frame_index * 6, frame_index * 6 + 6);

  return m_FrameTextureCoords[frame_index];
}


Optional<Box> SpriteEngineData::RenderSprite(const SpritePtr & sprite, int animation_index, int animation_frame, uint32_t skin_name_hash,
  const Vector2f & position, const RenderVec4 & matrix, const Color & color, const ShaderProgram & shader)
{
  auto resource = sprite.GetResource();
  if (resource == nullptr)
  {
    return{};
  }

  return RenderSprite(resource, animation_index, animation_frame, skin_name_hash, position, matrix, color, shader);
}

Optional<Box> SpriteEngineData::RenderSprite(NotNullPtr<const SpriteResource> resource, int animation_index, int animation_frame, uint32_t skin_name_hash,
  const Vector2f & position, const RenderVec4 & matrix, const Color & color, const ShaderProgram & shader)
{
  const SpriteEngineData * sprite_data = resource->m_EngineData.Get<SpriteEngineData>();
  if (sprite_data == nullptr)
  {
    return{};
  }

  auto rounded_pos = position;
  rounded_pos.x = floorf(rounded_pos.x);
  rounded_pos.y = floorf(rounded_pos.y);

  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), rounded_pos);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), matrix);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);

  return sprite_data->Render(animation_index, animation_frame, skin_name_hash, shader);
}

Optional<Box> SpriteEngineData::RenderTile(const TileSheetPtr & tile_sheet, int animation_index, int animation_frame, uint32_t skin_name_hash,
  const Vector2f & position, const RenderVec4 & matrix, const Color & color, const ShaderProgram & shader)
{
  auto resource = tile_sheet.GetResource();
  if (resource == nullptr)
  {
    return{};
  }

  const SpriteEngineData * sprite_data = resource->m_EngineData.Get<SpriteEngineData>();
  if (sprite_data == nullptr)
  {
    return{};
  }

  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), position);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), matrix);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);

  return sprite_data->Render(animation_index, animation_frame, skin_name_hash, shader);
}

NullOptPtr<TextureAsset> SpriteEngineData::GetSpriteFrame(const SpritePtr & sprite, int animation_index, int animation_frame, Box & texture_coords)
{
  auto resource = sprite.GetResource();
  if (resource == nullptr)
  {
    return nullptr;
  }

  return GetSpriteFrame(resource, animation_index, animation_frame, texture_coords);
}

NullOptPtr<TextureAsset> SpriteEngineData::GetSpriteFrame(NotNullPtr<const SpriteResource> resource, int animation_index, int animation_frame, Box & texture_coords)
{
  SpriteEngineData * sprite_data = (SpriteEngineData *)resource->m_EngineData.Get<SpriteEngineData>();
  if (sprite_data == nullptr)
  {
    return nullptr;
  }

  if (animation_index >= sprite_data->m_Frames.size())
  {
    return nullptr;
  }

  if (animation_index < 0 || animation_index >= sprite_data->m_Frames.size())
  {
    return nullptr;
  }

  if (animation_frame < 0 || animation_frame >= sprite_data->m_Frames[animation_index].second)
  {
    return nullptr;
  }

  int frame_index = sprite_data->m_Frames[animation_index].first + animation_frame;
  auto texture_index = sprite_data->m_FrameTextures[frame_index];
  if (texture_index == -1)
  {
    return nullptr;
  }

  texture_coords = sprite_data->m_FrameTextureCoords[frame_index];
  return sprite_data->m_Textures[texture_index].Get();
}

Any CreateSpriteEngineData(SpriteBaseDef & sprite)
{
  return Any(SpriteEngineData(sprite));
}

void UpdateSpriteEngineData(Any & engine_data)
{
  SpriteEngineData * sprite_data = engine_data.Get<SpriteEngineData>();
  if (sprite_data == nullptr)
  {
    return;
  }

  sprite_data->Load();
}

void RenderSprite(Any & engine_data, EntityRenderState & render_state, Vector2 & position)
{
  SpriteEngineData * sprite_data = engine_data.Get<SpriteEngineData>();
  if (sprite_data == nullptr)
  {
    return;
  }

  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ position } );
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), render_state.m_Matrix);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), render_state.m_Color);

  sprite_data->Render(render_state.m_AnimIndex, render_state.m_AnimFrame, render_state.m_SkinNameHash, shader);
}
