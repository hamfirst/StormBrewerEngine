
#include "Foundation/FileSystem/Path.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "Runtime/Map/MapDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include "MapEditorEntityManager.h"
#include "MapEditor.h"


MapEditorEntityManager::MapEditorEntityManager(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_SpriteMirror(editor),
  m_Hidden(false),
  m_Collapsed(false)
{
  m_GetSprite = CreateMirrorList<RMergeList, MapEntity, RString, MapEditorEntityManagerElement, MapEditorEntityManager>(
    m_SpriteMirror,
    m_Map.m_EntityLayers[layer_index].m_Entities,
    [this]() -> void * { auto layer = m_Map.m_EntityLayers.TryGet(m_LayerIndex); return layer ? &layer->m_Entities : nullptr; },
    ".m_EntityDef.m_Sprite",
    [](MapEntity & elem, NotNullPtr<MapEditorEntityManager>) -> RString & { return elem.m_EntityDef.m_Sprite; },
    [](RString & filename, MapEditorEntityManagerElement & elem, std::size_t index, NotNullPtr<MapEditorEntityManager> ptr) { },
    [](RString & filename, MapEditorEntityManagerElement & elem, std::size_t index, NotNullPtr<MapEditorEntityManager> ptr)
    { 
      if (filename.length() > 0)
      {
        elem.m_Sprite = SpriteResource::Load(filename.data());
      }
      else
      {
        elem.m_Sprite = {};
      }
    }, this);
}

void MapEditorEntityManager::AddEntity(czstr entity_file, const Vector2 & pos)
{
  m_Editor->BeginTransaction();

  auto new_index = m_Map.m_EntityLayers[m_LayerIndex].m_Entities.HighestIndex() + 1;
  auto & map_entity = m_Map.m_EntityLayers[m_LayerIndex].m_Entities.EmplaceBack();
  map_entity.m_Name = GetFileStemForCanonicalPath(entity_file);
  map_entity.m_GUID = GetRandomNumber();
  map_entity.m_XPosition = pos.x;
  map_entity.m_YPosition = pos.y;
 
  std::string link_dst_path = ".m_EntityLayers[" + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(new_index) + "].m_EntityDef";
  m_Editor->CreateLink(entity_file, "", link_dst_path.data());

  m_Editor->CommitChanges();
}

void MapEditorEntityManager::RemoveEntity(std::size_t index)
{
  ClearSelection();

  m_Editor->BeginTransaction();
  std::string link_dst_path = ".m_EntityLayers[" + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(index) + "].m_EntityDef";

  m_Map.m_EntityLayers[m_LayerIndex].m_Entities.RemoveAt(index);
  m_Editor->CommitChanges();
}

void MapEditorEntityManager::SetPreviewEntity(czstr entity_file)
{
  m_PreviewEntityFile = entity_file;
  m_PreviewEntity = EntityResource::Load(entity_file);
  m_PreviewEntityPosition.Clear();
}

void MapEditorEntityManager::SetPreviewEntityPosition(const Vector2 & pos)
{
  m_PreviewEntityPosition = pos;
}

void MapEditorEntityManager::ClearPreviewEntity()
{
  m_PreviewEntity.Clear();
  m_PreviewEntityPosition.Clear();
}

void MapEditorEntityManager::CommitPreviewEntity()
{
  if (m_PreviewEntity.GetResource() == nullptr || m_PreviewEntityPosition == false)
  {
    return;
  }

  AddEntity(m_PreviewEntityFile.data(), m_PreviewEntityPosition.Value());
}

void MapEditorEntityManager::SelectEntities(const Box & box)
{
  ClearSelection();
  m_SelectedEntityOffset = {};

  for (auto elem : m_Map.m_EntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && BoxIntersect(box, data->m_Frame.Value()))
    {
      m_SelectedEntities.push_back(elem.first);
    }
  }
}

Optional<std::string> MapEditorEntityManager::FindEntity(const Vector2 & pos)
{
  for (auto elem : m_Map.m_EntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);

    if (data->m_Frame && PointInBox(data->m_Frame.Value(), pos))
    {
      auto links = m_Editor->GetLinks();
      auto test_path = std::string(".m_EntityLayers[") + std::to_string(m_LayerIndex) + "].m_Entities[" + std::to_string(elem.first) + "].m_EntityDef";

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

void MapEditorEntityManager::DropSelection()
{
  if (m_SelectedEntities.size() == 0)
  {
    return;
  }

  if (m_SelectedEntityOffset.x != 0 || m_SelectedEntityOffset.y != 0)
  {
    m_Editor->BeginTransaction();
    for (auto elem : m_Map.m_EntityLayers[m_LayerIndex].m_Entities)
    {
      if (vfind(m_SelectedEntities, elem.first))
      {
        elem.second.m_XPosition += m_SelectedEntityOffset.x;
        elem.second.m_YPosition += m_SelectedEntityOffset.y;
      }
    }

    m_Editor->CommitChanges();
  }

  m_SelectedEntityOffset = {};
}

void MapEditorEntityManager::ClearSelection()
{
  DropSelection();

  m_SelectedEntities.clear();
}

void MapEditorEntityManager::DeselectEntities()
{
  m_SelectedEntities.clear();
  for (auto elem : m_Map.m_EntityLayers[m_LayerIndex].m_Entities)
  {
    if (vfind(m_SelectedEntities, elem.first))
    {
      elem.second.m_XPosition += m_SelectedEntityOffset.x;
      elem.second.m_YPosition += m_SelectedEntityOffset.y;
    }
  }

  m_SelectedEntities.clear();
  m_SelectedEntityOffset = {};
}

void MapEditorEntityManager::DeleteSelectedEntities()
{
  if (m_SelectedEntities.size() == 0)
  {
    return;
  }

  m_Editor->BeginTransaction();

  for (auto index : m_SelectedEntities)
  {
    m_Map.m_EntityLayers[m_LayerIndex].m_Entities.RemoveAt(index);
  }

  m_SelectedEntities.clear();
  m_SelectedEntityOffset = {};

  m_Editor->CommitChanges();
}

void MapEditorEntityManager::MoveSelection(const Vector2 & offset)
{
  m_SelectedEntityOffset = offset;
}

bool MapEditorEntityManager::IsOnSelectedEntity(const Vector2 & pos)
{
  for (auto selection : m_SelectedEntities)
  {
    if (m_Map.m_EntityLayers[m_LayerIndex].m_Entities.HasAt(selection) == false)
    {
      continue;
    }

    auto & entity = m_Map.m_EntityLayers[m_LayerIndex].m_Entities[selection];
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

void MapEditorEntityManager::SetSingleSelection(std::size_t entity_index)
{
  ClearSelection();
  m_SelectedEntities.push_back(entity_index);
}

Optional<std::size_t> MapEditorEntityManager::GetSingleSelectionIndex()
{
  if (m_SelectedEntities.size() != 1)
  {
    return{};
  }

  if (m_Map.m_EntityLayers[m_LayerIndex].m_Entities.HasAt(m_SelectedEntities[0]) == false)
  {
    return{};
  }

  return m_SelectedEntities[0];
}

void MapEditorEntityManager::Draw(const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  for (auto elem : m_Map.m_EntityLayers[m_LayerIndex].m_Entities)
  {
    auto data = m_GetSprite(elem.first);

    Box tex_coords;
    if (SpriteEngineData::GetSpriteFrame(data->m_Sprite, 0, 0, tex_coords))
    {
      auto pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
      auto frame_size = tex_coords.Size();
      Box frame = Box::FromFrameCenterAndSize(pos, frame_size);

      if (vfind(m_SelectedEntities, elem.first))
      {
        frame.m_Start += m_SelectedEntityOffset;
        frame.m_End += m_SelectedEntityOffset;
        pos += m_SelectedEntityOffset;
      }

      data->m_Frame = frame;

      if (BoxIntersect(viewport_bounds, frame))
      {
        auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();

        RenderVec2 draw_pos = pos;
        draw_pos -= screen_center;

        SpriteEngineData::RenderSprite(data->m_Sprite, render_state, 0, 0, kSpriteDefaultSkin, draw_pos);
      }
    }
  }
}

void MapEditorEntityManager::DrawPreviewEntity(const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  auto entity = m_PreviewEntity.GetResource();
  if (entity == nullptr || entity->IsLoaded() == false || m_PreviewEntityPosition == false)
  {
    return;
  }

  auto & sprite = entity->GetSprite();

  RenderVec2 draw_pos = RenderVec2{ m_PreviewEntityPosition.Value() };
  draw_pos -= screen_center;

  SpriteEngineData::RenderSprite(sprite, render_state, 0, 0, kSpriteDefaultSkin, draw_pos, RenderVec4{ 1, 0, 0, 1 }, Color(255, 255, 255, 160));
}

void MapEditorEntityManager::DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_SelectedEntities.size() == 0)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  for (auto selection : m_SelectedEntities)
  {
    if (m_Map.m_EntityLayers[m_LayerIndex].m_Entities.HasAt(selection) == false)
    {
      continue;
    }

    auto & entity = m_Map.m_EntityLayers[m_LayerIndex].m_Entities[selection];
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
  auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
  render_state.BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 0, 1, 1 });

  render_state.BindTexture(render_util.GetDefaultTexture());
  render_state.BindVertexBuffer(vertex_buffer);
  render_state.Draw();
}

void MapEditorEntityManager::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorEntityManager::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorEntityManager::IsHidden()
{
  return m_Hidden;
}

void MapEditorEntityManager::ToggleColapsed()
{
  m_Collapsed = !m_Collapsed;
}

bool MapEditorEntityManager::IsCollapsed()
{
  return m_Collapsed;
}
