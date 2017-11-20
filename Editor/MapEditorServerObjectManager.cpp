
#include "Foundation/FileSystem/Path.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"

#include "StormData/StormDataJson.h"

#include "MapEditorServerObjectManager.h"
#include "MapEditor.h"


MapEditorServerObjectManager::MapEditorServerObjectManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_SpriteMirror(editor),
  m_Hidden(false),
  m_Collapsed(false)
{
  m_GetSprite = CreateMirrorList<RMergeList, MapServerObject, ServerObjectInitDataPolyType, MapEditorServerObjectManagerElement, MapEditorServerObjectManager>(
    m_SpriteMirror,
    m_Map.m_ServerObjectLayers[layer_index].m_Objects,
    [this]() -> void * { auto layer = m_Map.m_ServerObjectLayers.TryGet(m_LayerIndex); return layer ? &layer->m_Objects : nullptr; },
    ".m_ServerObject.m_InitData",
    [](MapServerObject & elem, NotNullPtr<MapEditorServerObjectManager>) -> ServerObjectInitDataPolyType & { return elem.m_ServerObject.m_InitData; },
    [](ServerObjectInitDataPolyType & init_data, MapEditorServerObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorServerObjectManager> ptr) {},
    [](ServerObjectInitDataPolyType & init_data, MapEditorServerObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorServerObjectManager> ptr)
    {
      auto entity_file = g_ServerObjectSystem.GetEntityBindingForInitDataTypeNameHash(init_data.GetTypeNameHash());
      if (entity_file != nullptr)
      {
        elem.m_Entity = EntityResource::Load(entity_file);
      }
      else
      {
        elem.m_Entity.Clear();
      }
    }, this);
}

void MapEditorServerObjectManager::AddServerObject(czstr ServerObject_file, const Vector2 & pos)
{
  m_Editor->BeginTransaction();

  auto new_index = m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.HighestIndex() + 1;
  auto & map_ServerObject = m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.EmplaceBack();
  map_ServerObject.m_Name = GetFileStemForCanonicalPath(ServerObject_file);
  map_ServerObject.m_XPosition = pos.x;
  map_ServerObject.m_YPosition = pos.y;

  std::string link_dst_path = ".m_ServerObjectLayers[" + std::to_string(m_LayerIndex) + "].m_Objects[" + std::to_string(new_index) + "].m_ServerObject";
  m_Editor->CreateLink(ServerObject_file, "", link_dst_path.data());

  m_Editor->CommitChanges();
}

void MapEditorServerObjectManager::RemoveServerObject(std::size_t index)
{
  ClearSelection();

  m_Editor->BeginTransaction();
  std::string link_dst_path = ".m_ServerObjectLayers[" + std::to_string(m_LayerIndex) + "].m_Objects[" + std::to_string(index) + "].m_ServerObject";

  m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  m_Editor->CommitChanges();
}

void MapEditorServerObjectManager::SetPreviewServerObject(czstr server_object_file)
{
  m_PreviewServerObjectFile = server_object_file;
  m_PreviewServerObjectPosition.Clear();
  m_PreviewEntity.Clear();

  ServerObjectResource::LoadWithCallback(server_object_file, [this](NotNullPtr<ServerObjectResource> resource) {
    auto init_data_type_name_hash = resource->GetData()->m_InitData.GetTypeNameHash();
    auto entity_file = g_ServerObjectSystem.GetEntityBindingForInitDataTypeNameHash(init_data_type_name_hash);
    if (entity_file)
    {
      m_PreviewEntity = EntityResource::Load(entity_file);
    }
    else
    {
      m_PreviewEntity.Clear();
    }
  }, m_PreviewServerObject);
}

void MapEditorServerObjectManager::SetPreviewServerObjectPosition(const Vector2 & pos)
{
  m_PreviewServerObjectPosition = pos;
}

void MapEditorServerObjectManager::ClearPreviewServerObject()
{
  m_PreviewServerObject.Clear();
  m_PreviewServerObjectPosition.Clear();
  m_PreviewEntity.Clear();
}

void MapEditorServerObjectManager::CommitPreviewServerObject()
{
  if (m_PreviewServerObject.GetResource() == nullptr || m_PreviewServerObjectPosition == false)
  {
    return;
  }

  AddServerObject(m_PreviewServerObjectFile.data(), m_PreviewServerObjectPosition.Value());
}

void MapEditorServerObjectManager::SelectServerObjects(const Box & box)
{
  ClearSelection();
  m_SelectedServerObjectOffset = {};

  for (auto & elem : m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && BoxIntersect(box, data->m_Frame.Value()))
    {
      m_SelectedServerObjects.push_back(elem.first);
    }
  }
}

Optional<std::string> MapEditorServerObjectManager::FindServerObject(const Vector2 & pos)
{
  for (auto & elem : m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && PointInBox(data->m_Frame.Value(), pos))
    {
      auto links = m_Editor->GetLinks();
      auto test_path = std::string(".m_ServerObjectLayers[") + std::to_string(m_LayerIndex) + "].m_Objects[" + std::to_string(elem.first) + "].m_ServerObject";

      for (auto & link : links)
      {
        if (link.m_LocalPath == test_path)
        {
          return link.m_SourceAsset;
        }
      }

      return{};
    }
  }

  return{};
}

void MapEditorServerObjectManager::DropSelection()
{
  if (m_SelectedServerObjects.size() == 0)
  {
    return;
  }

  if (m_SelectedServerObjectOffset.x != 0 || m_SelectedServerObjectOffset.y != 0)
  {
    m_Editor->BeginTransaction();
    for (auto & elem : m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects)
    {
      if (vfind(m_SelectedServerObjects, elem.first))
      {
        elem.second.m_XPosition += m_SelectedServerObjectOffset.x;
        elem.second.m_YPosition += m_SelectedServerObjectOffset.y;
      }
    }

    m_Editor->CommitChanges();
  }

  m_SelectedServerObjectOffset = {};
}

void MapEditorServerObjectManager::ClearSelection()
{
  DropSelection();

  m_SelectedServerObjects.clear();
}

void MapEditorServerObjectManager::DeselectServerObjects()
{
  m_SelectedServerObjects.clear();
  for (auto & elem : m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects)
  {
    if (vfind(m_SelectedServerObjects, elem.first))
    {
      elem.second.m_XPosition += m_SelectedServerObjectOffset.x;
      elem.second.m_YPosition += m_SelectedServerObjectOffset.y;
    }
  }

  m_SelectedServerObjects.clear();
  m_SelectedServerObjectOffset = {};
}

void MapEditorServerObjectManager::DeleteSelectedServerObjects()
{
  if (m_SelectedServerObjects.size() == 0)
  {
    return;
  }

  m_Editor->BeginTransaction();

  for (auto index : m_SelectedServerObjects)
  {
    m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  }

  m_SelectedServerObjects.clear();
  m_SelectedServerObjectOffset = {};

  m_Editor->CommitChanges();
}

void MapEditorServerObjectManager::MoveSelection(const Vector2 & offset)
{
  m_SelectedServerObjectOffset = offset;
}

bool MapEditorServerObjectManager::IsOnSelectedServerObject(const Vector2 & pos)
{
  for (auto selection : m_SelectedServerObjects)
  {
    if (m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
    {
      continue;
    }

    auto & ServerObject = m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects[selection];
    auto data = m_GetSprite(selection);

    if (data == nullptr || data->m_Frame == false)
    {
      continue;
    }

    auto frame = data->m_Frame.Value();
    if (PointInBox(frame, pos))
    {
      return true;
    }
  }

  return false;
}

void MapEditorServerObjectManager::SetSingleSelection(std::size_t ServerObject_index)
{
  ClearSelection();
  m_SelectedServerObjects.push_back(ServerObject_index);
}

Optional<std::size_t> MapEditorServerObjectManager::GetSingleSelectionIndex()
{
  if (m_SelectedServerObjects.size() != 1)
  {
    return{};
  }

  if (m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.HasAt(m_SelectedServerObjects[0]) == false)
  {
    return{};
  }

  return m_SelectedServerObjects[0];
}

void MapEditorServerObjectManager::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center)
{
  for (auto & elem : m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetSprite(elem.first);
    auto entity = data->m_Entity.GetResource();

    if (entity)
    {
      auto & sprite = entity->GetSprite();

      Box tex_coords;
      if (SpriteEngineData::GetSpriteFrame(sprite, 0, 0, tex_coords))
      {
        auto pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
        auto frame_size = tex_coords.Size();
        Box frame = Box::FromFrameCenterAndSize(pos, frame_size);

        if (vfind(m_SelectedServerObjects, elem.first))
        {
          frame.m_Start += m_SelectedServerObjectOffset;
          frame.m_End += m_SelectedServerObjectOffset;
          pos += m_SelectedServerObjectOffset;
        }

        data->m_Frame = frame;

        if (BoxIntersect(viewport_bounds, frame))
        {
          auto & shader = g_ShaderManager.GetDefaultShader();

          RenderVec2 draw_pos = pos;
          draw_pos -= screen_center;

          SpriteEngineData::RenderSprite(sprite, 0, 0, kSpriteDefaultSkin, draw_pos);
        }
      }
    }
  }
}

void MapEditorServerObjectManager::DrawPreviewServerObject(const RenderVec2 & screen_center)
{
  auto entity = m_PreviewEntity.GetResource();
  if (entity == nullptr || entity->IsLoaded() == false || m_PreviewServerObjectPosition == false)
  {
    return;
  }

  auto & sprite = entity->GetSprite();

  RenderVec2 draw_pos = RenderVec2{ m_PreviewServerObjectPosition.Value() };
  draw_pos -= screen_center;

  SpriteEngineData::RenderSprite(sprite, 0, 0, kSpriteDefaultSkin, draw_pos, RenderVec4{ 1, 0, 0, 1 }, Color(255, 255, 255, 160));
}

void MapEditorServerObjectManager::DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderUtil & render_util)
{
  if (m_SelectedServerObjects.size() == 0)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  for (auto selection : m_SelectedServerObjects)
  {
    if (m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
    {
      continue;
    }

    auto & ServerObject = m_Map.m_ServerObjectLayers[m_LayerIndex].m_Objects[selection];
    auto data = m_GetSprite(selection);

    if (data == nullptr || data->m_Frame == false)
    {
      continue;
    }

    auto frame = data->m_Frame.Value();
    if (BoxIntersect(viewport_bounds, frame))
    {
      quad.m_Position = frame;
      quad.m_TexCoords = Box::FromPoint({});
      quad.m_TextureSize = Vector2(1, 1);
      quad.m_Color = Color(255, 255, 255, 255);

      line_builder.AddBox(quad);
    }
  }

  line_builder.FillVertexBuffer(vertex_buffer);
  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 0, 1, 1 });
  render_util.GetDefaultTexture().BindTexture(0);

  vertex_buffer.Bind();

  vertex_buffer.CreateDefaultBinding(shader);
  vertex_buffer.Draw();
  vertex_buffer.Unbind();
}

void MapEditorServerObjectManager::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorServerObjectManager::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorServerObjectManager::IsHidden()
{
  return m_Hidden;
}

void MapEditorServerObjectManager::ToggleColapsed()
{
  m_Collapsed = !m_Collapsed;
}

bool MapEditorServerObjectManager::IsCollapsed()
{
  return m_Collapsed;
}
