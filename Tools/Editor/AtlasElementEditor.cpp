
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Atlas/AtlasEngineData.h"

#include "AtlasElementEditor.h"
#include "AtlasTextureLoadList.h"
#include "AtlasEditor.h"
#include "DrawUtil.h"

AtlasElementEditor::AtlasElementEditor(
        NotNullPtr<AtlasEditor> editor,
        AtlasDef & atlas,
        AtlasTextureLoadList & texture_access,
        QWidget * parent) :
        GeometryEditorBase(parent),
        m_Editor(editor),
        m_Atlas(atlas),
        m_TextureAccess(texture_access)
{

}

NullOptPtr<TextureAsset> AtlasElementEditor::GetTexture()
{
  if (m_Atlas.m_Textures.HighestIndex() == -1)
  {
    return nullptr;
  }

  auto texture_hash = 0;
  for(auto elem : m_Atlas.m_Elements)
  {
    if(crc32(elem.second.m_Name.data()) == m_SelectedName)
    {
      texture_hash = elem.second.m_TextureHash;
    }
  }

  auto default_texture = m_Atlas.m_Textures.begin();
  AtlasDefTexture * texture_info = &default_texture->second;
  std::size_t texture_index = default_texture->first;

  for (auto texture : m_Atlas.m_Textures)
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

