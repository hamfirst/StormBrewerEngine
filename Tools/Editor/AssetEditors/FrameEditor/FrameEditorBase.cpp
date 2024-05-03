
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "AssetEditors/FrameEditor/FrameEditorBase.h"
#include "AssetEditors/FrameEditor/FrameEditorUtil.h"
#include "AssetEditors/SpriteEditor/SpriteEditor.h"
#include "Utility/DrawUtil.h"

FrameEditorBase::FrameEditorBase(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  uint64_t frame_id,
  QWidget * parent) :
  GeometryEditorBase(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_FrameId(frame_id)
{
  UpdateFrameSize();
}

void FrameEditorBase::UpdateFrameSize()
{
  m_FrameWidth = 0;
  m_FrameHeight = 0;

  if (m_Sprite.m_Textures.HighestIndex() == -1)
  {
    return;
  }

  auto default_texture = m_Sprite.m_Textures.begin();
  SpriteBaseDefTexture * texture_info = &default_texture->second;

  uint32_t texture_hash = m_FrameId >> 32;

  for (auto texture : m_Sprite.m_Textures)
  {
    if (texture_hash == crc32(texture.second.m_Filename))
    {
      texture_info = &texture.second;
    }
  }

  m_FrameWidth = texture_info->m_FrameWidth;
  m_FrameHeight = texture_info->m_FrameHeight;
};

Optional<Vector2> FrameEditorBase::GetFrameSize()
{
  return Vector2(m_FrameWidth, m_FrameHeight);
}

uint64_t FrameEditorBase::GetFrameId()
{
  return m_FrameId;
}

NullOptPtr<TextureAsset> FrameEditorBase::GetTexture()
{
  if (m_Sprite.m_Textures.HighestIndex() == -1)
  {
    return nullptr;
  }

  uint32_t texture_hash = m_FrameId >> 32;

  auto default_texture = m_Sprite.m_Textures.begin();
  SpriteBaseDefTexture * texture_info = &default_texture->second;
  std::size_t texture_index = default_texture->first;

  for (auto texture : m_Sprite.m_Textures)
  {
    if (texture_hash == crc32(texture.second.m_Filename))
    {
      texture_index = texture.first;
      texture_info = &texture.second;
    }
  }

  auto texture = m_TextureAccess.GetTexture(texture_index);
  return texture;
}

void FrameEditorBase::RefreshWatcher()
{

}

void FrameEditorBase::SetFrame(uint64_t frame_id)
{
  m_FrameId = frame_id;
  RefreshWatcher();
  UpdateFrameSize();
  repaint();
}
