
#include "SpriteBaseTextureLoadList.h"
#include "SpriteBaseEditor.h"

SpriteBaseTextureLoadList::SpriteBaseTextureLoadList(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureList(m_Editor)
{
  m_GetTexture = CreateMirrorList<RMergeList, SpriteBaseDefTexture, RString, AssetSync<TextureAsset>, SpriteBaseTextureLoadList>(
    m_TextureList,
    m_Sprite.m_Textures,
    ".m_Filename",
    [](SpriteBaseDefTexture & elem, NotNullPtr<SpriteBaseTextureLoadList>) -> RString & { return elem.m_Filename; },
    [](RString & filename, AssetSync<TextureAsset> & tex, std::size_t, NotNullPtr<SpriteBaseTextureLoadList>) {},
    [](RString & filename, AssetSync<TextureAsset> & tex, std::size_t, NotNullPtr<SpriteBaseTextureLoadList>) { tex.LoadFile(filename.data()); },
    this
  );
}

NullOptPtr<TextureAsset> SpriteBaseTextureLoadList::GetTexture(std::size_t index)
{
  auto asset_sync = m_GetTexture(index);
  if (asset_sync == nullptr)
  {
    return nullptr;
  }

  return asset_sync->GetAsset();
}

DelegateLink<void> SpriteBaseTextureLoadList::AddUpdateCallback(Delegate<void> && del)
{
  return m_UpdateCallbacks.AddDelegate(std::move(del));
}

Optional<uint64_t> SpriteBaseTextureLoadList::GetDefaultFrame()
{
  for (auto elem : m_Sprite.m_Textures)
  {
    auto & texture_data = elem.second;
    uint64_t frame_id = crc32(elem.second.m_Filename);

    frame_id <<= 32;
    return frame_id;
  }

  return{};
}

Optional<QImage> SpriteBaseTextureLoadList::GetFrameAndImage(uint64_t frame_id, int & src_x, int & src_y, int & src_w, int & src_h)
{
  uint32_t texture_hash = (uint32_t)(frame_id >> 32);
  int frame_index = (int)(frame_id);

  for (auto elem : m_Sprite.m_Textures)
  {
    if (crc32(elem.second.m_Filename) == texture_hash)
    {
      auto & texture_data = elem.second;
      auto texture_asset = GetTexture(elem.first);

      if (texture_asset == nullptr || texture_asset->IsLoaded() == false || texture_data.m_FrameWidth == 0 || texture_data.m_FrameHeight == 0)
      {
        return{};
      }

      auto pixel_buffer = texture_asset->GetPixelBuffer();
      auto frames_per_line = (pixel_buffer->GetWidth() + texture_data.m_FrameWidth - 1) / texture_data.m_FrameWidth;

      src_x = (frame_index % frames_per_line) * texture_data.m_FrameWidth;
      src_y = (frame_index / frames_per_line) * texture_data.m_FrameHeight;
      src_w = texture_data.m_FrameWidth;
      src_h = texture_data.m_FrameHeight;

      QImage::Format img_format;
      switch (pixel_buffer->GetPixelSize())
      {
      case 3:
        img_format = QImage::Format_RGB888;
        break;
      case 4:
        img_format = QImage::Format_RGBA8888;
        break;
      default:
        return{};
      }

      return QImage(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);
    }
  }

  return{};
}

void SpriteBaseTextureLoadList::HandleTextureUpdate()
{
  m_UpdateCallbacks.Call();
}
