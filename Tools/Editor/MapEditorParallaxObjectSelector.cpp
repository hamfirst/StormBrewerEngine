
#include <QPainter>

#include "Foundation/FileSystem/Path.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "Engine/Sprite/SpriteEngineData.h"

#include "MapEditorParallaxObjectSelector.h"
#include "MapEditorParallaxLayer.h"
#include "MapEditor.h"

MapEditorParallaxObjectSelector::MapEditorParallaxObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_PickParallaxObject(std::make_unique<QPushButton>("Pick Parallax Object File...", this))
{
  connect(m_PickParallaxObject.get(), &QPushButton::pressed, this, &MapEditorParallaxObjectSelector::pickParallaxObject);
}

MapEditorParallaxObjectSelector::~MapEditorParallaxObjectSelector()
{

}

void MapEditorParallaxObjectSelector::Clear()
{
  m_ParallaxObjectFile.clear();
  m_ParallaxObject = {};
}

void MapEditorParallaxObjectSelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorParallaxObjectSelector::SetSelectedParallaxObject(czstr file)
{
  m_ParallaxObjectFile = file;
  m_ParallaxObject = MapEditorParallaxLayer::CreateObjectFromPath(file, [this] { update(); });
}

void MapEditorParallaxObjectSelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.drawText(300, 13, m_ParallaxObjectFile.data());

  auto texture_link = m_ParallaxObject.Get<TextureAsset::LoadCallbackLink>();
  if (texture_link)
  {
    auto texture = texture_link->Get();
    if (texture && texture->IsLoaded())
    {
      auto pixel_buffer = texture->GetPixelBuffer();

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
        return;
      }

      QImage img(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);

      auto texture_size = texture->GetSize();
      p.drawImage(QRect(300, 20, texture_size.x * 2, texture_size.y * 2), img, QRect(0, 0, texture_size.x, texture_size.y));
    }

    return;
  }

  auto sprite_link = m_ParallaxObject.Get<SpriteLoadLink>();
  if (sprite_link && sprite_link->IsLoaded())
  {
    auto sprite = sprite_link->GetResource();
    if (sprite && sprite->GetData()->m_Animations.HighestIndex() >= 0)
    {
      Box tex_coords;
      auto texture = SpriteEngineData::GetSpriteFrame(sprite, 0, 0, tex_coords);

      if (texture)
      {
        auto pixel_buffer = texture->GetPixelBuffer();

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
          return;
        }

        QImage img(pixel_buffer->GetPixelBuffer(), pixel_buffer->GetWidth(), pixel_buffer->GetHeight(), img_format);

        auto texture_size = tex_coords.Size();
        p.drawImage(QRect(300, 20, texture_size.x * 2, texture_size.y * 2), img, QRect(tex_coords.m_Start.x, tex_coords.m_Start.y, texture_size.x, texture_size.y));
      }
    }
  }
}

void MapEditorParallaxObjectSelector::resizeEvent(QResizeEvent * ev)
{
  m_PickParallaxObject->setGeometry(0, 0, 300, height());
}

void MapEditorParallaxObjectSelector::pickParallaxObject()
{
  auto file_name = m_Editor->GetFileNameForAssetType("parallax");
  if (file_name)
  {
    auto type = MapEditorParallaxLayer::GetParallaxTypeForPath(file_name->data());
    if (type)
    {
      MapParallaxLayerObject object = {};
      object.m_File = file_name.Value();
      object.m_Type = type.Value();
      object.m_Name = GetFileStemForCanonicalPath(file_name.Value());

      m_Editor->SetSelectedParallaxObject(m_LayerIndex, object);
    }
  }
}
