
#include <QPainter>

#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/ServerObject/ServerObjectSystem.h"

#include "MapEditorServerObjectSelector.h"
#include "MapEditor.h"

MapEditorServerObjectSelector::MapEditorServerObjectSelector(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(-1),
  m_PickServerObject(std::make_unique<QPushButton>("Pick Server Object File...", this))
{
  connect(m_PickServerObject.get(), &QPushButton::pressed, this, &MapEditorServerObjectSelector::pickServerObject);
}

MapEditorServerObjectSelector::~MapEditorServerObjectSelector()
{

}

void MapEditorServerObjectSelector::Clear()
{
  m_ServerObjectFile.clear();
  m_ServerObject = {};
}

void MapEditorServerObjectSelector::SetLayer(int layer_index)
{
  m_LayerIndex = layer_index;
}

void MapEditorServerObjectSelector::SetSelectedServerObject(czstr server_object_file)
{
  m_ServerObjectFile = server_object_file;
  ServerObjectResource::LoadWithCallback(server_object_file, [this](NotNullPtr<ServerObjectResource>) { LoadEntity(); repaint(); }, m_ServerObject);
}

void MapEditorServerObjectSelector::LoadEntity()
{
  auto data = m_ServerObject.GetData();
  auto init_data_type_name_hash = data->m_InitData.GetTypeNameHash();
  
  auto entity_file = g_ServerObjectSystem.GetEntityBindingForInitDataTypeNameHash(init_data_type_name_hash);
  if (entity_file)
  {
    EntityResource::LoadWithCallback(entity_file, [this](NotNullPtr<EntityResource>){ repaint(); }, m_Entity);
  }
  else
  {
    m_Entity.Clear();
  }
}

void MapEditorServerObjectSelector::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.drawText(300, 13, m_ServerObjectFile.data());

  auto server_object_resource = m_ServerObject.GetResource();
  if (server_object_resource)
  {
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
}

void MapEditorServerObjectSelector::resizeEvent(QResizeEvent * ev)
{
  m_PickServerObject->setGeometry(0, 0, 300, height());
}

void MapEditorServerObjectSelector::pickServerObject()
{
  auto file_name = m_Editor->GetFileNameForAssetType("serverobject");
  if (file_name)
  {
    m_Editor->SetSelectedServerObject(m_LayerIndex, file_name->data());
  }
}
