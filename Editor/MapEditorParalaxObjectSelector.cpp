
#include <QPainter>

#include "Foundation/FileSystem/Path.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "Engine/Sprite/SpriteEngineData.h"

#include "MapEditorParalaxObjectSelector.h"
#include "MapEditorParalaxLayer.h"
#include "MapEditor.h"

MapEditorParalaxObjectSelector::MapEditorParalaxObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_PickParalaxObject(std::make_unique<QPushButton>("Pick Paralax Object File...", this))
{
  connect(m_PickParalaxObject.get(), &QPushButton::pressed, this, &MapEditorParalaxObjectSelector::pickParalaxObject);
}

MapEditorParalaxObjectSelector::~MapEditorParalaxObjectSelector()
{

}

void MapEditorParalaxObjectSelector::Clear()
{
  m_ParalaxObjectFile.clear();
  m_ParalaxObject = {};
}

void MapEditorParalaxObjectSelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorParalaxObjectSelector::SetSelectedParalaxObject(czstr file)
{
  m_ParalaxObjectFile = file;
  m_ParalaxObject = MapEditorParalaxLayer::CreateObjectFromPath(file, [this] { update(); });
}

void MapEditorParalaxObjectSelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.drawText(300, 13, m_ParalaxObjectFile.data());

  auto texture_link = m_ParalaxObject.Get<TextureAsset::LoadCallbackLink>();
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

  auto sprite_link = m_ParalaxObject.Get<SpriteLoadLink>();
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

void MapEditorParalaxObjectSelector::resizeEvent(QResizeEvent * ev)
{
  m_PickParalaxObject->setGeometry(0, 0, 300, height());
}

void MapEditorParalaxObjectSelector::pickParalaxObject()
{
  auto file_name = m_Editor->GetFileNameForAssetType("paralax");
  if (file_name)
  {
    auto type = MapEditorParalaxLayer::GetParalaxTypeForPath(file_name->data());
    if (type)
    {
      MapParalaxLayerObject object = {};
      object.m_File = file_name.Value();
      object.m_Type = type.Value();
      object.m_Name = GetFileStemForCanonicalPath(file_name.Value());

      m_Editor->SetSelectedParalaxObject(m_LayerIndex, object);
    }
  }
}
