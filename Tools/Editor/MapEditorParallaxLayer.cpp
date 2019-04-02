

#include "StormData/StormDataJson.h"

#include "Foundation/FileSystem/Path.h"
#include "Foundation/BasicTypes/BasicTypeFuncs.h"

#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Sprite/SpriteResource.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexList.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Sprite/SpriteEngineData.h"

#include "MapEditorParallaxLayer.h"
#include "MapEditor.h"


MapEditorParallaxLayer::MapEditorParallaxLayer(NotNullPtr<MapEditor> editor, MapDef & map, int layer_index) :
  m_Editor(editor),
  m_Map(map),
  m_LayerIndex(layer_index),
  m_ObjectMirror(m_Editor),
  m_TextureWatcher(m_Editor)
{
  HandleTextureChanged();

  m_GetObject = CreateMirrorList<RMergeList, MapParallaxLayerObject, MapParallaxLayerObject, MapEditorParallaxObjectManagerElement, MapEditorParallaxLayer>(
    m_ObjectMirror,
    m_Map.m_ParallaxLayers[layer_index].m_Objects,
    [this]() -> void * { auto layer = m_Map.m_ParallaxLayers.TryGet(m_LayerIndex); return layer ? &layer->m_Objects : nullptr; },
    "",
    [](MapParallaxLayerObject & elem, NotNullPtr<MapEditorParallaxLayer>) -> MapParallaxLayerObject & { return elem; },
    [](MapParallaxLayerObject & init_data, MapEditorParallaxObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorParallaxLayer> ptr) {},
    [](MapParallaxLayerObject & init_data, MapEditorParallaxObjectManagerElement & elem, std::size_t index, NotNullPtr<MapEditorParallaxLayer> ptr)
    {
      elem.m_Object = MapEditorParallaxLayer::CreateObjectFromPath(init_data.m_File.data(), [] {});
    }, this);
}

void MapEditorParallaxLayer::AddParallaxObject(const MapParallaxLayerObject & parallax_object_data)
{
  m_Editor->BeginTransaction();
  m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.EmplaceBack(parallax_object_data);
  m_Editor->CommitChanges();
}

void MapEditorParallaxLayer::RemoveParallaxObject(std::size_t index)
{
  ClearSelection();

  m_Editor->BeginTransaction();
  m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  m_Editor->CommitChanges();
}

void MapEditorParallaxLayer::SetPreviewParallaxObjectPosition(const Vector2 & pos)
{
  m_PreviewPosition = pos;
}

void MapEditorParallaxLayer::ClearPreviewParallaxObject()
{
  m_PreviewPosition.Clear();
}

void MapEditorParallaxLayer::CommitPreviewParallaxObject()
{
  if (m_PreviewPosition.IsValid() == false)
  {
    return;
  }

  m_Editor->CreateNewParallaxObject(m_LayerIndex, m_PreviewPosition.Value());
}

void MapEditorParallaxLayer::SelectParallaxObjects(const Box & box)
{
  ClearSelection();
  m_SelectedParallaxObjectOffset = {};

  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetObject(elem.first);

    if (data->m_Frame && BoxIntersect(box, data->m_Frame.Value()))
    {
      m_SelectedParallaxObjects.push_back(elem.first);
    }
  }
}

Optional<MapParallaxLayerObject> MapEditorParallaxLayer::FindParallaxObject(const Vector2 & pos)
{
  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    auto data = m_GetObject(elem.first);

    if (data->m_Frame && PointInBox(data->m_Frame.Value(), pos))
    {
      return elem.second;
    }
  }

  return{};
}

void MapEditorParallaxLayer::DropSelection()
{
  if (m_SelectedParallaxObjects.size() == 0)
  {
    return;
  }

  if (m_SelectedParallaxObjectOffset.x != 0 || m_SelectedParallaxObjectOffset.y != 0)
  {
    m_Editor->BeginTransaction();
    for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
    {
      if (vfind(m_SelectedParallaxObjects, elem.first))
      {
        elem.second.m_XPosition += m_SelectedParallaxObjectOffset.x;
        elem.second.m_YPosition += m_SelectedParallaxObjectOffset.y;
      }
    }

    m_Editor->CommitChanges();
  }

  m_SelectedParallaxObjectOffset = {};
}

void MapEditorParallaxLayer::ClearSelection()
{
  DropSelection();

  m_SelectedParallaxObjects.clear();
}

void MapEditorParallaxLayer::DeselectParallaxObjects()
{
  m_SelectedParallaxObjects.clear();
  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    if (vfind(m_SelectedParallaxObjects, elem.first))
    {
      elem.second.m_XPosition += m_SelectedParallaxObjectOffset.x;
      elem.second.m_YPosition += m_SelectedParallaxObjectOffset.y;
    }
  }

  m_SelectedParallaxObjects.clear();
  m_SelectedParallaxObjectOffset = {};
}

void MapEditorParallaxLayer::DeleteSelectedParallaxObjects()
{
  if (m_SelectedParallaxObjects.size() == 0)
  {
    return;
  }

  m_Editor->BeginTransaction();

  for (auto index : m_SelectedParallaxObjects)
  {
    m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.RemoveAt(index);
  }

  m_SelectedParallaxObjects.clear();
  m_SelectedParallaxObjectOffset = {};

  m_Editor->CommitChanges();
}

void MapEditorParallaxLayer::MoveSelection(const Vector2 & offset)
{
  m_SelectedParallaxObjectOffset = offset;
}

bool MapEditorParallaxLayer::IsOnSelectedParallaxObject(const Vector2 & pos)
{
  for (auto selection : m_SelectedParallaxObjects)
  {
    if (m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
    {
      continue;
    }

    auto & ParallaxObject = m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects[selection];
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

void MapEditorParallaxLayer::SetSingleSelection(std::size_t ParallaxObject_index)
{
  ClearSelection();
  m_SelectedParallaxObjects.push_back(ParallaxObject_index);
}

Optional<std::size_t> MapEditorParallaxLayer::GetSingleSelectionIndex()
{
  if (m_SelectedParallaxObjects.size() != 1)
  {
    return{};
  }

  if (m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.HasAt(m_SelectedParallaxObjects[0]) == false)
  {
    return{};
  }

  return m_SelectedParallaxObjects[0];
}

void MapEditorParallaxLayer::Draw(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  auto layer = m_Map.m_ParallaxLayers.TryGet(m_LayerIndex);
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

    float offset_x = (layer->m_ParallaxX == 0.0f ? 0.0f : (screen_center.x / -layer->m_ParallaxX.AsFloat())) + time * layer->m_VelocityX.AsFloat() + layer->m_OffsetX.AsFloat();
    float offset_y = (layer->m_ParallaxY == 0.0f ? 0.0f : (screen_center.y / -layer->m_ParallaxY.AsFloat())) + time * layer->m_VelocityY.AsFloat() + layer->m_OffsetY.AsFloat();

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

    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_state.GetFullRenderDimensions());
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

  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParallaxLayerObjectType::kTexture)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);
    if (vfind(m_SelectedParallaxObjects, elem.first))
    {
      pos += m_SelectedParallaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state);
  }

  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParallaxLayerObjectType::kSprite)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);

    if (vfind(m_SelectedParallaxObjects, elem.first))
    {
      pos += m_SelectedParallaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state);
  }

  for (auto elem : m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects)
  {
    if (elem.second.m_Type != MapParallaxLayerObjectType::kVfx)
    {
      continue;
    }

    Vector2 pos = Vector2(elem.second.m_XPosition, elem.second.m_YPosition);

    if (vfind(m_SelectedParallaxObjects, elem.first))
    {
      pos += m_SelectedParallaxObjectOffset;
    }

    auto data = m_GetObject(elem.first);
    data->m_Frame = DrawObject(data->m_Object, elem.second, pos, buffer, viewport_bounds, screen_center, render_state);
  }
}

void MapEditorParallaxLayer::DrawPreviewParallaxObject(VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  if (m_PreviewPosition.IsValid() == false)
  {
    return;
  }

  DrawObject(m_Editor->GetParallaxObject(), m_Editor->GetParallaxObjectInitData(), m_PreviewPosition.Value(), buffer, viewport_bounds, screen_center, render_state);
}

void MapEditorParallaxLayer::DrawSelection(VertexBuffer & vertex_buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
{
  if (m_SelectedParallaxObjects.size() == 0)
  {
    return;
  }

  LineVertexBufferBuilder line_builder;
  QuadVertexBuilderInfo quad;

  for (auto selection : m_SelectedParallaxObjects)
  {
    if (m_Map.m_ParallaxLayers[m_LayerIndex].m_Objects.HasAt(selection) == false)
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

  render_state.BindTexture(render_state.GetDefaultTexture());
  render_state.BindVertexBuffer(vertex_buffer);
  render_state.Draw();
}

Optional<Box> MapEditorParallaxLayer::DrawObject(MapEditorParallaxObjectType & object, MapParallaxLayerObject & object_data,
  const Vector2 & pos, VertexBuffer & buffer, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state)
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

void MapEditorParallaxLayer::ToggleHidden()
{
  m_Hidden = !m_Hidden;
}

void MapEditorParallaxLayer::SetHidden(bool hidden)
{
  m_Hidden = hidden;
}

bool MapEditorParallaxLayer::IsHidden()
{
  return m_Hidden;
}

void MapEditorParallaxLayer::ToggleColapsed()
{
  m_Collapsed = !m_Collapsed;
}

bool MapEditorParallaxLayer::IsCollapsed()
{
  return m_Collapsed;
}

Optional<MapParallaxLayerObjectType> MapEditorParallaxLayer::GetParallaxTypeForPath(czstr file_path)
{
  std::string path = file_path;
  ConvertToCanonicalPath(path, GetCanonicalRootPath());
  auto ext = GetFileExtensionForPath(path);

  if (ext == "png")
  {
    return MapParallaxLayerObjectType::kTexture;
  }
  else if (ext == "sprite")
  {
    return MapParallaxLayerObjectType::kSprite;
  }
  else if (ext == "vfx")
  {
    return MapParallaxLayerObjectType::kVfx;
  }
  else
  {
    return {};
  }
}

void MapEditorParallaxLayer::HandleTextureChanged()
{
  auto layer = m_Map.m_ParallaxLayers.TryGet(m_LayerIndex);
  if(layer == nullptr)
  {
    return;
  }

  if (layer->m_Image.size() > 0)
  {
    m_TextureAsset = TextureAsset::Load(layer->m_Image.data());
  }
}
