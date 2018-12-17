

#include "StormData/StormDataJson.h"

#include "Foundation/FileSystem/Path.h"
#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "MapEditorParalaxLayer.h"
#include "MapEditor.h"


MapEditorParalaxLayer::MapEditorParalaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_ObjectMirror(m_Editor),
  m_TextureWatcher(m_Editor)
{
  HandleTextureChanged();

  m_GetObject = CreateMirrorList<RMergeList, MapParalaxLayerObject, MapParalaxLayerObject, MapEditorParalaxObjectManagerElement, MapEditorParalaxLayer>(
    m_ObjectMirror,
    m_Map.m_ParalaxLayers[layer_index].m_Objects,
    [this]() -> void * { auto layer = m_Map.m_ParalaxLayers.TryGet(m_LayerIndex); return layer ? &layer->m_Objects : nullptr; },
    "",
    [](MapParalaxLayerObject & elem, NotNullPtr<MapEditorParalaxLayer>) -> MapParalaxLayerObject & { return elem; },
    [](MapParalaxLayerObject & init_data, MapEditorParalaxObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorParalaxLayer> ptr) {},
    [](MapParalaxLayerObject & init_data, MapEditorParalaxObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorParalaxLayer> ptr)
    {
      elem.m_Object = MapEditorParalaxLayer::CreateObjectFromPath(init_data.m_File.data(), [] {});
    }, this);
}

void MapEditorParalaxLayer::AddParalaxObject(const MapParalaxLayerObject & paralax_object_data)
{
  m_Editor->BeginTransaction();
  m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.EmplaceBack(paralax_object_data);
  m_Editor->CommitChanges();
}

void MapEditorParalaxLayer::RemoveParalaxObject(std::size_t index)
{
  ClearSelection();

  m_Editor->BeginTransaction();
  m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  m_Editor->CommitChanges();
}

void MapEditorParalaxLayer::SetPreviewParalaxObjectPosition(const Vector2 & pos)
{
  m_PreviewPosition = pos;
}

void MapEditorParalaxLayer::ClearPreviewParalaxObject()
{
  m_PreviewPosition.Clear();
}

void MapEditorParalaxLayer::CommitPreviewParalaxObject()
{
  if (m_PreviewPosition.IsValid() == false)
  {
    return;
  }

  m_Editor->CreateNewParalaxObject(m_LayerIndex, m_PreviewPosition.Value());
}

void MapEditorParalaxLayer::SelectParalaxObjects(const Box & box)
{
  ClearSelection();
  m_SelectedParalaxObjectOffset = {};

  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetObject(elem.first);

    if (data->m_Frame && BoxIntersect(box, data->m_Frame.Value()))
    {
      m_SelectedParalaxObjects.push_back(elem.first);
    }
  }
}

Optional<MapParalaxLayerObject> MapEditorParalaxLayer::FindParalaxObject(const Vector2 & pos)
{
  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetObject(elem.first);

    if (data->m_Frame && PointInBox(data->m_Frame.Value(), pos))
    {
      return elem.second;
    }
  }

  return{};
}

void MapEditorParalaxLayer::DropSelection()
{
  if (m_SelectedParalaxObjects.size() == 0)
  {
    return;
  }

  if (m_SelectedParalaxObjectOffset.x != 0 || m_SelectedParalaxObjectOffset.y != 0)
  {
    m_Editor->BeginTransaction();
    for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
    {
      if (vfind(m_SelectedParalaxObjects, elem.first))
      {
        elem.second.m_XPosition += m_SelectedParalaxObjectOffset.x;
        elem.second.m_YPosition += m_SelectedParalaxObjectOffset.y;
      }
    }

    m_Editor->CommitChanges();
  }

  m_SelectedParalaxObjectOffset = {};
}

void MapEditorParalaxLayer::ClearSelection()
{
  DropSelection();

  m_SelectedParalaxObjects.clear();
}

void MapEditorParalaxLayer::DeselectParalaxObjects()
{
  m_SelectedParalaxObjects.clear();
  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    if (vfind(m_SelectedParalaxObjects, elem.first))
    {
      elem.second.m_XPosition += m_SelectedParalaxObjectOffset.x;
      elem.second.m_YPosition += m_SelectedParalaxObjectOffset.y;
    }
  }

  m_SelectedParalaxObjects.clear();
  m_SelectedParalaxObjectOffset = {};
}

void MapEditorParalaxLayer::DeleteSelectedParalaxObjects()
{
  if (m_SelectedParalaxObjects.size() == 0)
  {
    return;
  }

  m_Editor->BeginTransaction();

  for (auto index : m_SelectedParalaxObjects)
  {
    m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  }

  m_SelectedParalaxObjects.clear();
  m_SelectedParalaxObjectOffset = {};

  m_Editor->CommitChanges();
}

void MapEditorParalaxLayer::MoveSelection(const Vector2 & offset)
{
  m_SelectedParalaxObjectOffset = offset;
}

bool MapEditorParalaxLayer::IsOnSelectedParalaxObject(const Vector2 & pos)
{
  for (auto selection : m_SelectedParalaxObjects)
  {
    if (m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
    {
      continue;
    }

    auto & ParalaxObject = m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects[selection];
    auto data = m_GetObject(selection);

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

void MapEditorParalaxLayer::SetSingleSelection(std::size_t ParalaxObject_index)
{
  ClearSelection();
  m_SelectedParalaxObjects.push_back(ParalaxObject_index);
}

Optional<std::size_t> MapEditorParalaxLayer::GetSingleSelectionIndex()
{
  if (m_SelectedParalaxObjects.size() != 1)
  {
    return{};
  }

  if (m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.HasAt(m_SelectedParalaxObjects[0]) == false)
  {
    return{};
  }

  return m_SelectedParalaxObjects[0];
}

void MapEditorParalaxLayer::Draw(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  auto layer = m_Map.m_ParalaxLayers.TryGet(m_LayerIndex);
  if (layer == nullptr)
  {
    return;
  }

  auto texture = m_TextureAsset.Resolve();
  if (texture != nullptr && texture->IsLoaded() != false && texture->GetWidth() != 0 && texture->GetHeight() != 0)
  {
    auto viewport_size = viewport_bounds.Size();
    auto half_viewport_size = RenderVec2(viewport_size) * 0.5f;

    int width = layer->m_RepeatX ? texture->GetWidth() : viewport_size.x;
    int height = layer->m_RepeatY ? texture->GetHeight() : viewport_size.y;

    auto time = (float)GetTimeSeconds();

    float offset_x = (layer->m_ParalaxX == 0.0f ? 0.0f : (screen_center.x / -layer->m_ParalaxX.AsFloat())) + time * layer->m_VelocityX.AsFloat() + layer->m_OffsetX.AsFloat();
    float offset_y = (layer->m_ParalaxY == 0.0f ? 0.0f : (screen_center.y / -layer->m_ParalaxY.AsFloat())) + time * layer->m_VelocityY.AsFloat() + layer->m_OffsetY.AsFloat();

    offset_x *= (float)texture->GetWidth() / (float)width;
    offset_y *= (float)texture->GetHeight() / (float)height;

    offset_x = glm::fract(offset_x / texture->GetWidth()) * width;
    offset_y = glm::fract(offset_y / texture->GetHeight()) * height;

    VertexList verts;
    VertexInfo vert;

    RenderVec2 tex_size(width, height);
    RenderVec2 offset(offset_x, offset_y);

    RenderVec2 start_pos = -half_viewport_size;
    RenderVec2 end_pos = half_viewport_size;

    RenderVec2 start_tex_pos = (-half_viewport_size - offset) / tex_size;
    RenderVec2 end_tex_pos = (half_viewport_size - offset) / tex_size;

    vert.m_Color = RenderVec4{ 1,1,1,1 };
    vert.m_Position = start_pos;
    vert.m_TexCoord = start_tex_pos;
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(start_pos.x, end_pos.y);
    vert.m_TexCoord = RenderVec2(start_tex_pos.x, end_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(end_pos.x, start_pos.y);
    vert.m_TexCoord = RenderVec2(end_tex_pos.x, start_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(start_pos.x, end_pos.y);
    vert.m_TexCoord = RenderVec2(start_tex_pos.x, end_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = RenderVec2(end_pos.x, start_pos.y);
    vert.m_TexCoord = RenderVec2(end_tex_pos.x, start_tex_pos.y);
    verts.AddVert(vert);

    vert.m_Position = end_pos;
    vert.m_TexCoord = end_tex_pos;
    verts.AddVert(vert);

    buffer.SetBufferData(verts, VertexBufferType::kTriangles);
    auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
    render_state.BindShader(shader);

    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), RenderVec2{ render_state.GetRenderSize() });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{});
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1, -1, 1, 1 });
    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

    render_state.BindTexture(*texture);
    render_state.BindVertexBuffer(buffer);
    render_state.Draw();
  }

  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParalaxLayerObjectType::kTexture)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
    if (vfind(m_SelectedParalaxObjects, elem.first))
    {
      pos += m_SelectedParalaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state, render_util);
  }

  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParalaxLayerObjectType::kSprite)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);

    if (vfind(m_SelectedParalaxObjects, elem.first))
    {
      pos += m_SelectedParalaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state, render_util);
  }

  for (auto elem : m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParalaxLayerObjectType::kVfx)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);

    if (vfind(m_SelectedParalaxObjects, elem.first))
    {
      pos += m_SelectedParalaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state, render_util);
  }
}

void MapEditorParalaxLayer::DrawPreviewParalaxObject(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_PreviewPosition.IsValid() == false)
  {
    return;
  }

  DrawObject(m_Editor->GetParalaxObject(), m_Editor->GetParalaxObjectInitData(), m_PreviewPosition.Value(), buffer, viewport_bounds, screen_center, render_state, render_util);
}

void MapEditorParalaxLayer::DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (m_SelectedParalaxObjects.size() == 0)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  for (auto selection : m_SelectedParalaxObjects)
  {
    if (m_Map.m_ParalaxLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
    {
      continue;
    }

    auto data = m_GetObject(selection);

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

Optional<Box> MapEditorParalaxLayer::DrawObject(MapEditorParalaxObjectType & object, MapParalaxLayerObject & object_data, 
  const Vector2 & pos, VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  auto texture_link = object.Get<TextureAsset::LoadCallbackLink>();
  if (texture_link)
  {
    auto texture = texture_link->Get();
    if (texture && texture->IsLoaded())
    {
      auto texture_box = Box::FromFrameCenterAndSize(pos, texture->GetSize());
      if (BoxIntersect(texture_box, viewport_bounds))
      {
        QuadVertexBufferBuilder builder;
        QuadVertexBuilderInfo quad;
        quad.m_Color = Color(255, 255, 255, 255);
        quad.m_Position = texture_box;
        quad.m_TexCoords = Box::FromPoints({}, texture->GetSize());
        quad.m_TextureSize = texture->GetSize();
        builder.AddQuad(quad);

        builder.FillVertexBuffer(buffer);
        auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
        render_state.BindShader(shader);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });

        render_state.BindTexture(*texture);
        render_state.BindVertexBuffer(buffer);
        render_state.Draw();
      }

      return texture_box;
    }

    return {};
  }

  auto sprite_link = object.Get<SpriteLoadLink>();
  if (sprite_link)
  {
    if (sprite_link->IsLoaded())
    {
      auto sprite = sprite_link->GetResource();
      auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
      shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });

      int frame = (int)(GetTimeSeconds() * 60.0);

      AnimationState state;
      sprite->SyncToFrame(crc32(object_data.m_Animation.data()), state, frame);

      return SpriteEngineData::RenderSprite(sprite, render_state, state.m_AnimIndex, state.m_AnimFrame, 0, pos);
    }

    return {};
  }

  auto visual_effect_link = object.Get<VisualEffectLoadLink>();
  if (visual_effect_link)
  {
    auto texture = m_Editor->GetTextures().m_VfxTexture.Resolve();
    if (texture->IsLoaded())
    {
      auto texture_box = Box::FromFrameCenterAndSize(pos, texture->GetSize());
      if (BoxIntersect(texture_box, viewport_bounds))
      {
        QuadVertexBufferBuilder builder;
        QuadVertexBuilderInfo quad;
        quad.m_Color = Color(255, 255, 255, 255);
        quad.m_Position = texture_box;
        quad.m_TexCoords = Box::FromPoints({}, texture->GetSize());
        quad.m_TextureSize = texture->GetSize();
        builder.AddQuad(quad);

        builder.FillVertexBuffer(buffer);
        auto & shader = g_ShaderManager.GetDefaultWorldSpaceShader();
        render_state.BindShader(shader);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -screen_center);
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });
        shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1, 1, 1, 1 });

        render_state.BindTexture(*texture);
        render_state.BindVertexBuffer(buffer);
        render_state.Draw();
      }

      return texture_box;
    }

    return {};
  }

  return {};
}

void MapEditorParalaxLayer::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorParalaxLayer::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorParalaxLayer::IsHidden()
{
  return m_Hidden;
}

void MapEditorParalaxLayer::ToggleColapsed()
{
  m_Collapsed = !m_Collapsed;
}

bool MapEditorParalaxLayer::IsCollapsed()
{
  return m_Collapsed;
}

Optional<MapParalaxLayerObjectType> MapEditorParalaxLayer::GetParalaxTypeForPath(czstr file_path)
{
  std::string path = file_path;
  ConvertToCanonicalPath(path, GetCanonicalRootPath());
  auto ext = GetFileExtensionForPath(path);

  if (ext == "png")
  {
    return MapParalaxLayerObjectType::kTexture;
  }
  else if (ext == "sprite")
  {
    return MapParalaxLayerObjectType::kSprite;
  }
  else if (ext == "vfx")
  {
    return MapParalaxLayerObjectType::kVfx;
  }
  else
  {
    return {};
  }
}

void MapEditorParalaxLayer::HandleTextureChanged()
{
  auto layer = m_Map.m_ParalaxLayers.TryGet(m_LayerIndex);
  if(layer == nullptr)
  {
    return;
  }

  if (layer->m_Image.size() > 0)
  {
    m_TextureAsset = TextureAsset::Load(layer->m_Image.data());
  }
}
