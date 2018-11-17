
#include <QPainter>

#include "Engine/Sprite/SpriteEngineData.h"

#include "MapEditorEntitySelector.h"
#include "MapEditor.h"

MapEditorEntitySelector::MapEditorEntitySelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_PickEntity(std::make_unique<QPushButton>("Pick Entity File...", this))
{
  connect(m_PickEntity.get(), &QPushButton::pressed, this, &MapEditorEntitySelector::pickEntity);
}

MapEditorEntitySelector::~MapEditorEntitySelector()
{

}

void MapEditorEntitySelector::Clear()
{
  m_EntityFile.clear();
  m_Entity = {};
}

void MapEditorEntitySelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorEntitySelector::SetSelectedEntity(czstr entity_file)
{
  m_EntityFile = entity_file;
  EntityResource::LoadWithCallback(entity_file, [this](NotNullPtr<EntityResource>) { repaint(); }, m_Entity);
}

void MapEditorEntitySelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.drawText(300, 13, m_EntityFile.data());

  auto entity_resource = m_Entity.GetResource();
  if (entity_resource)
  {
    auto & sprite = entity_resource->GetSprite();

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

void MapEditorEntitySelector::resizeEvent(QResizeEvent * ev)
{
  m_PickEntity->setGeometry(0, 0, 300, height());
}

void MapEditorEntitySelector::pickEntity()
{
  auto file_name = m_Editor->GetFileNameForAssetType("entity");
  if (file_name)
  {
    m_Editor->SetSelectedEntity(m_LayerIndex, file_name->data());
  }
}
