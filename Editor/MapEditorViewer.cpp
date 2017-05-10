
#include <gl3w/gl3w.h>

#include <QTimer>
#include <QWheelEvent>
#include <QApplication>

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/Map/MapDef.refl.h"

#include "MapEditorViewer.h"
#include "MapEditor.h"
#include "MapEditorToolBase.h"


static const char * kMapViewerWidgetGridVertexShader = SHADER_LITERAL(
  attribute vec2 a_Position;
  attribute vec4 a_Color;

  varying vec4 v_Color;

  void main()
  {
    gl_Position = vec4(a_Position, 0, 1);
    v_Color = a_Color;
  }
);

static const char * kMapViewerWidgetGridFragmentShader = SHADER_LITERAL(

  varying vec4 v_Color;

  uniform sampler2D u_Texture;

  void main()
  {
    gl_FragColor = v_Color;
  }
);

MapEditorViewer::MapEditorViewer(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QOpenGLWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_DrawBuffer(true),
  m_GridWidth(16),
  m_GridHeight(16)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  QTimer * timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MapEditorViewer::tick);
  timer->start(15);

  m_Magnification.Set(2.0f);
}

MapEditorViewer::~MapEditorViewer()
{
}

void MapEditorViewer::SetGridWidth(int width)
{
  m_GridWidth = width;
}

int MapEditorViewer::GetGridWidth() const
{
  return m_GridWidth;
}

void MapEditorViewer::SetGridHeight(int height)
{
  m_GridHeight = height;
}

int MapEditorViewer::GetGridHeight() const
{
  return m_GridHeight;
}

void MapEditorViewer::SetSelectionBox(const Box & box)
{
  m_SelectionBox = box;
}

void MapEditorViewer::ClearSelectionBox()
{
  m_SelectionBox.Clear();
}

void MapEditorViewer::SetTool(std::unique_ptr<MapEditorToolBase> && tool)
{
  ClearTool();
  m_Tool = std::move(tool);
  m_Tool->Init();
}

void MapEditorViewer::ClearTool()
{
  if (m_Tool)
  {
    m_Tool->Cleanup();
  }

  m_Tool.reset();

  if (m_Dragging)
  {
    m_Dragging = false;
    SyncMouse();

    m_LastDrawPos = {};
  }
}

void MapEditorViewer::ChangeLayerSelection(const MapEditorLayerSelection & layer)
{
  m_SelectedLayer = layer;
  ClearTool();
}

void MapEditorViewer::ClearLayerSelection()
{
  m_SelectedLayer.Clear();
  ClearTool();
}

void MapEditorViewer::ZoomToEntity(std::size_t layer_index, std::size_t entity_index)
{
  auto layer = m_Map.m_EntityLayers.TryGet(layer_index);
  if (layer)
  {
    auto entity = layer->m_Entities.TryGet(entity_index);
    if (entity)
    {
      m_Center = RenderVec2{ entity->m_XPosition, entity->m_YPosition };
    }
  }
}

RenderVec2 MapEditorViewer::TransformFromMapSpaceToClipSpace(RenderVec2 map_space)
{
  auto offset = map_space;
  offset -= RenderVec2{ m_Center.x, m_Center.y };
  offset *= m_Magnification.Get();
  offset /= RenderVec2{ width(), height() };
  offset *= 2.0f;

  auto clip_space = offset;
  return clip_space;
}

RenderVec2 MapEditorViewer::TransformFromClipSpaceToMapSpace(RenderVec2 clip_space)
{
  auto offset = clip_space;
  offset *= 0.5f;
  offset *= (1.0f / m_Magnification.Get());
  offset *= RenderVec2{ width(), height() };
  offset += RenderVec2{ m_Center.x, m_Center.y };

  auto texture_space = offset;
  return texture_space;
}

RenderVec2 MapEditorViewer::TransformFromClipSpaceToScreenSpace(RenderVec2 clip_space)
{
  auto texture_space = ((clip_space + RenderVec2(1.0f, 1.0f) * 0.5f)) * RenderVec2(width(), height());
  return texture_space;
}

RenderVec2 MapEditorViewer::TransformFromScreenSpaceToClipSpace(RenderVec2 screen_space)
{
  auto clip_space = ((screen_space / RenderVec2(width(), height())) * 2.0f) - RenderVec2(1.0f, 1.0f);
  clip_space.y *= -1.0f;
  return clip_space;
}

RenderVec2 MapEditorViewer::TransformFromMapSpaceToScreenSpace(RenderVec2 map_space)
{
  auto clip_space = TransformFromMapSpaceToClipSpace(map_space);
  return TransformFromClipSpaceToScreenSpace(clip_space);
}

RenderVec2 MapEditorViewer::TransformFromScreenSpaceToMapSpace(RenderVec2 screen_space)
{
  auto clip_space = TransformFromScreenSpaceToClipSpace(screen_space);
  return TransformFromClipSpaceToMapSpace(clip_space);
}

void MapEditorViewer::SnapToGrid(Vector2 & pos)
{
  if (m_GridWidth <= 0 || m_GridHeight <= 0)
  {
    return;
  }

  pos.x = pos.x - (pos.x >= 0 ? pos.x % m_GridWidth : m_GridWidth - 1 + ((pos.x + 1) % m_GridWidth)) + m_GridWidth / 2;
  pos.y = pos.y - (pos.y >= 0 ? pos.y % m_GridHeight : m_GridHeight - 1 + ((pos.y + 1) % m_GridHeight)) + m_GridWidth / 2;
}

void MapEditorViewer::SetTileFrameInfo(MapTile & tile, uint64_t frame_id)
{
  tile.m_FrameId = (uint32_t)frame_id;
  tile.m_TextureHash = (uint32_t)(frame_id >> 32);
}

uint64_t MapEditorViewer::GetFrameIdForMapTile(const MapTile & tile)
{
  uint64_t frame_id = tile.m_TextureHash;
  frame_id <<= 32;
  frame_id |= tile.m_FrameId;
  return frame_id;
}

Vector2 MapEditorViewer::GetCursorPos()
{
  auto qt_cursor_pos = mapFromGlobal(QCursor::pos());
  auto map_cursor_pos = TransformFromScreenSpaceToMapSpace(RenderVec2{ qt_cursor_pos.x(), qt_cursor_pos.y() });

  Vector2 cursor_pos = map_cursor_pos;
  return cursor_pos;
}

Vector2 MapEditorViewer::GetSnappedCursorPos()
{
  auto cursor_pos = GetCursorPos();
  SnapToGrid(cursor_pos);
  return cursor_pos;
}

void MapEditorViewer::SyncMouse()
{
  bool should_have_mouse = m_Dragging || m_Panning;
  if (should_have_mouse && m_HasMouse == false)
  {
    grabMouse();
    m_HasMouse = true;
  }
  else if (should_have_mouse == false && m_HasMouse)
  {
    releaseMouse();
    m_HasMouse = false;
  }
}

void MapEditorViewer::initializeGL()
{
  m_RenderState.InitRenderState(width(), height());
  m_RenderUtil.LoadShaders();

  m_GridShader = MakeQuickShaderProgram(kMapViewerWidgetGridVertexShader, kMapViewerWidgetGridFragmentShader);
}

void MapEditorViewer::resizeGL(int w, int h)
{
  m_RenderState.SetScreenSize(Vector2(w, h));
}

void MapEditorViewer::paintGL()
{
  if (m_Tool && m_LastDrawPos)
  {
    auto cursor_pos = GetCursorPos();
    if (cursor_pos != m_LastDrawPos.Value())
    {
      m_LastDrawPos = cursor_pos;

      if (m_Dragging)
      {
        
        m_Tool->DrawMove(cursor_pos, 
          (QApplication::keyboardModifiers() & Qt::AltModifier) != 0, 
          (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
          (QApplication::keyboardModifiers() & Qt::ControlModifier) != 0);
      }
      else
      {
        m_Tool->DrawPreview(cursor_pos,
          (QApplication::keyboardModifiers() & Qt::AltModifier) != 0,
          (QApplication::keyboardModifiers() & Qt::ShiftModifier) != 0,
          (QApplication::keyboardModifiers()& Qt::ControlModifier) != 0);
      }
    }
  }

  Color color(100, 149, 237, 255);

  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);

  RenderVec2 window_start = TransformFromScreenSpaceToMapSpace(RenderVec2(0, height() - 1));
  RenderVec2 window_end = TransformFromScreenSpaceToMapSpace(RenderVec2(width() - 1, 0));

  Box viewport_bounds = { window_start, window_end };
  viewport_bounds.m_Start -= Vector2(1, 1);
  viewport_bounds.m_End += Vector2(1, 1);

  m_RenderState.EnableBlendMode();
  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), window_end - window_start);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));

  auto & paralax_manager = m_Editor->GetParalaxManager();
  auto & tile_manager = m_Editor->GetManualTileManager();
  auto & entity_manager = m_Editor->GetEntityManager();

  std::map<int, std::vector<Delegate<void>>> draw_callbacks;

  for (auto elem : m_Map.m_ParalaxLayers)
  {
    auto layer = paralax_manager.GetLayerManager(elem.first);
    if (layer == nullptr)
    {
      continue;
    }

    if (layer->IsHidden())
    {
      continue;
    }

    auto list_itr = draw_callbacks.find(elem.second.m_LayerOrder);
    if (list_itr == draw_callbacks.end())
    {
      auto result = draw_callbacks.emplace(std::make_pair(elem.second.m_LayerOrder, std::vector<Delegate<void>>{}));
      list_itr = result.first;
    }

    list_itr->second.emplace_back([&, l = layer] { l->Draw(m_DrawBuffer, viewport_bounds, m_Center); });
  }

  for (auto elem : m_Map.m_ManualTileLayers)
  {
    auto layer = tile_manager.GetLayerManager(elem.first);
    if (layer == nullptr)
    {
      continue;
    }

    if (layer->IsHidden())
    {
      continue;
    }

    auto list_itr = draw_callbacks.find(elem.second.m_LayerOrder);
    if (list_itr == draw_callbacks.end())
    {
      auto result = draw_callbacks.emplace(std::make_pair(elem.second.m_LayerOrder, std::vector<Delegate<void>>{}));
      list_itr = result.first;
    }

    list_itr->second.emplace_back([&, l=layer] { l->Draw(viewport_bounds, m_Center); });
  }

  for (auto elem : m_Map.m_EntityLayers)
  {
    auto layer = entity_manager.GetLayerManager(elem.first);
    if (layer == nullptr)
    {
      continue;
    }

    if (layer->IsHidden())
    {
      continue;
    }

    auto list_itr = draw_callbacks.find(elem.second.m_LayerOrder);
    if (list_itr == draw_callbacks.end())
    {
      auto result = draw_callbacks.emplace(std::make_pair(elem.second.m_LayerOrder, std::vector<Delegate<void>>{}));
      list_itr = result.first;
    }

    list_itr->second.emplace_back([&, l=layer] { l->Draw(viewport_bounds, m_Center); });
  }

  for (auto & list : draw_callbacks)
  {
    for (auto & cb : list.second)
    {
      cb();
    }
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 160));

  for (auto elem : m_Map.m_ManualTileLayers)
  {
    auto layer = tile_manager.GetLayerManager(elem.first);
    if (layer == nullptr)
    {
      continue;
    }

    if (layer->IsHidden())
    {
      continue;
    }

    if (layer != nullptr)
    {
      layer->DrawPreviewTiles(m_DrawBuffer, m_Center);
      layer->DrawSelectedTiles(m_DrawBuffer, m_Center, m_RenderUtil);
    }
  }

  for (auto elem : m_Map.m_EntityLayers)
  {
    auto layer = entity_manager.GetLayerManager(elem.first);
    if (layer == nullptr)
    {
      continue;
    }

    if (layer->IsHidden())
    {
      continue;
    }

    layer->DrawPreviewEntity(m_Center);
    layer->DrawSelection(m_DrawBuffer, viewport_bounds, m_Center, m_RenderUtil);
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));

  if (m_SelectionBox)
  {
    GeometryVertexBufferBuilder builder;
    builder.FilledRectangle(m_SelectionBox.Value(), Color(0.7, 0.9, 1.0f, 0.4f));
    builder.FillVertexBuffer(m_DrawBuffer);

    m_RenderUtil.GetDefaultTexture().BindTexture(0);

    shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), -m_Center);

    m_DrawBuffer.Bind();
    m_DrawBuffer.CreateDefaultBinding(shader);
    m_DrawBuffer.Draw();
  }

  shader.Unbind();

  if (m_GridWidth != 0 && m_GridHeight != 0 && m_DrawGrid)
  {
    GeometryVertexBufferBuilder vertex_builder;

    auto x_start = floorf(window_start.x / m_GridWidth) * m_GridWidth;
    auto x_end = (floorf(window_end.x / m_GridWidth) + 1) * m_GridWidth;
      
    auto y_start = floorf(window_start.y / m_GridHeight) * m_GridHeight;
    auto y_end = (floorf(window_end.y / m_GridHeight) + 1) * m_GridHeight;

    for (float x = x_start; x <= x_end; x += m_GridWidth)
    {
      auto start = TransformFromMapSpaceToClipSpace(RenderVec2{ x, y_start });
      auto end = TransformFromMapSpaceToClipSpace(RenderVec2{ x, y_end });

      int mx = (int)(x / m_GridHeight);
      int gx = mx % 10;
      int zx = mx % 50;

      vertex_builder.Line(start, end, (zx == 0 ? 8.0f : gx == 0 ? 4.0f : 2.0f) / width(), Color(1.0f, 0.5f, 0.6f, 0.3f));
    }

    for (float y = y_start; y < y_end; y += m_GridHeight)
    {
      auto start = TransformFromMapSpaceToClipSpace(RenderVec2{ x_start, y });
      auto end = TransformFromMapSpaceToClipSpace(RenderVec2{ x_end, y });

      int my = (int)(y / m_GridHeight);
      int gy = my % 10;
      int zy = my % 50;

      vertex_builder.Line(start, end, (zy == 0 ? 8.0f : gy == 0 ? 4.0f : 2.0f) / height(), Color(1.0f, 0.5f, 0.6f, 0.3f));
    }

    vertex_builder.FillVertexBuffer(m_GridBuffer);
    m_GridArray.CreateDefaultBinding(m_GridShader, m_GridBuffer);

    m_GridShader.Bind();
    m_GridArray.Bind();

    m_GridBuffer.Draw();

    m_GridShader.Unbind();
    m_GridArray.Unbind();
  }

  m_RenderState.DisableBlendMode();
}

void MapEditorViewer::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
  {
    if (m_Tool)
    {
      m_Tool->Delete();
    }
  }
  else if (event->key() == Qt::Key_G)
  {
    m_DrawGrid = !m_DrawGrid;
  }
  else if (event->key() == Qt::Key_H)
  {
    m_Editor->GetLayerList().ToggleSelectedLayer();
  }
}

void MapEditorViewer::mousePressEvent(QMouseEvent * event)
{
  m_CursorPos = QCursor::pos();

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (event->button() == Qt::LeftButton)
  {
    if (m_Tool)
    {
      if (m_Tool->DrawStart(GetCursorPos(), alt, shift, ctrl))
      {
        m_Dragging = true;

        SyncMouse();
      }
    }
  }
  else if (event->button() == Qt::RightButton)
  {
    if (m_Tool)
    {
      if (m_Dragging)
      {
        m_Tool->DrawCancel();
        m_Dragging = false;

        SyncMouse();
      }
      else
      {
        m_Tool->RightClick();
      }
    }
  }
  else if (event->button() == Qt::MiddleButton)
  {
    m_Panning = true;
    SyncMouse();
    return;
  }
}

void MapEditorViewer::mouseMoveEvent(QMouseEvent *event)
{
  auto p = QCursor::pos();

  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (m_Panning)
  {
    auto diff_pos = p - m_CursorPos;

    m_Center.x -= diff_pos.x() / m_Magnification.Get();
    m_Center.y += diff_pos.y() / m_Magnification.Get();
  }
  else if (m_Dragging)
  {
    if (m_Tool)
    {
      m_LastDrawPos = GetCursorPos();
      m_Tool->DrawMove(GetCursorPos(), alt, shift, ctrl);
    }
  }
  else
  {
    if (m_Tool)
    {
      m_LastDrawPos = GetCursorPos();
      m_Tool->DrawPreview(GetCursorPos(), alt, shift, ctrl);
    }
  }

  m_CursorPos = p;
}

void MapEditorViewer::mouseReleaseEvent(QMouseEvent * event)
{
  bool alt = (bool)(event->modifiers() & Qt::AltModifier);
  bool shift = (bool)(event->modifiers() & Qt::ShiftModifier);
  bool ctrl = (bool)(event->modifiers() & Qt::ControlModifier);

  if (event->button() == Qt::LeftButton)
  {
    if (m_Tool && m_Dragging)
    {
      m_Tool->DrawEnd(GetCursorPos(), alt, shift, ctrl);
      m_Dragging = false;
      
      SyncMouse();
    }
  }
  else if (event->button() == Qt::MiddleButton)
  {
    m_Panning = false;
    SyncMouse();
    return;
  }
}

void MapEditorViewer::wheelEvent(QWheelEvent *event)
{
  if (event->delta() < 0)
  {
    m_Magnification *= 0.8f;
  }
  else
  {
    m_Magnification *= 1.25f;
  }
}

void MapEditorViewer::tick()
{
  repaint();
}

