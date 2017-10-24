
#include <QPainter>
#include <QWheelEvent>

#include "StormData/StormDataPath.h"
#include "StormData/StormDataJson.h"

#include "Foundation/Math/Intersection.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"

#include "FrameEditorMultiBox.h"
#include "SpriteEditor.h"

FrameEditorMultiBox::FrameEditorMultiBox(
  NotNullPtr<SpriteBaseEditor> editor, 
  SpriteBaseDef & sprite, 
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> && getter,
  Delegate<void, std::vector<Box> &&> && new_element,
  uint64_t frame_id, 
  bool use_default_data,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, frame_id, parent),
  m_Watcher(editor),
  m_Getter(std::move(getter)),
  m_NewElement(std::move(new_element)),
  m_LocalChange(false),
  m_UseDefault(use_default_data),
  m_EditMode(FrameEditorMultiBoxMode::kNone)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  RefreshWatcher();
}

void FrameEditorMultiBox::ChangeFrame(uint64_t frame_id, Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> && getter, Delegate<void, std::vector<Box> &&> && new_element)
{
  m_Getter = std::move(getter);
  m_NewElement = std::move(new_element);
  SetFrame(frame_id);
}

void FrameEditorMultiBox::HandleDataUpdate()
{
  auto data_list = m_Getter();
  if (data_list == nullptr)
  {
    return;
  }

  if (m_LocalChange)
  {
    return;
  }

  RefreshWatcher();

  if (m_Dragging)
  {
    StopDrawing();
  }

  repaint();
}

void FrameEditorMultiBox::RefreshWatcher()
{
  m_Watcher.Clear();

  auto data_list = m_Getter();
  if (data_list)
  {
    m_Watcher.Emplace(m_Editor);
    m_Watcher->SetPath(StormDataGetPath(*data_list).data(), true, true, [this] { return m_Getter(); });
    m_Watcher->SetChangeCallback([this](const ReflectionChangeNotification &) { HandleDataUpdate(); });
    m_Watcher->SetParentChangeCallback([this] { HandleDataUpdate(); });
    m_Watcher->SetChildChangeCallback([this] { HandleDataUpdate(); });
  }
}

void FrameEditorMultiBox::WriteData(const std::vector<Box> & boxes)
{
  FrameEditorByteArray byte_array(boxes);
  auto new_box_list = byte_array.ConvertToMaximalBoxes();

  m_LocalChange = true;

  auto data_list = m_Getter();
  if (data_list == nullptr)
  {
    m_NewElement(std::move(new_box_list));
    RefreshWatcher();
  }
  else
  {
    *data_list = std::move(new_box_list);
  }

  repaint();
  m_LocalChange = false;
}

std::vector<Box> FrameEditorMultiBox::GetPreviewData(Optional<FrameEditorEdge> & preview_edge)
{
  std::vector<Box> boxes;

  auto data_list = m_Getter();
  if (data_list)
  {
    boxes = data_list->Value();
  }
  else if(m_UseDefault)
  {
    boxes.push_back(SpriteResource::GetDefaultSingleBox());
  }

  preview_edge = m_PreviewEdge;

  if (m_EditMode == FrameEditorMultiBoxMode::kEdge)
  {
    FrameEditorByteArray byte_array(boxes);
    FrameEditorEdge edge = m_PreviewEdge.Value();

    Optional<Box> new_box;
    byte_array.OffsetEdge(edge, m_PreviewOffset, new_box);

    preview_edge = edge;

    if (new_box)
    {
      boxes.push_back(new_box.Value());
      FrameEditorByteArray new_byte_array(boxes);

      boxes = new_byte_array.ConvertToMinimalBoxes();
    }
    else
    {
      boxes = byte_array.ConvertToMaximalBoxes();
    }
  }
  else if (m_EditMode == FrameEditorMultiBoxMode::kAdd)
  {
    FrameEditorByteArray byte_array(boxes);
    byte_array.AddBox(Box::FromPoints(m_DrawStart, m_DrawEnd));
    return byte_array.ConvertToMinimalBoxes();
  }
  else if (m_EditMode == FrameEditorMultiBoxMode::kRemove)
  {
    FrameEditorByteArray byte_array(boxes);
    byte_array.RemoveBox(Box::FromPoints(m_DrawStart, m_DrawEnd));
    return byte_array.ConvertToMinimalBoxes();
  }

  FrameEditorByteArray byte_array(boxes);
  return byte_array.ConvertToMinimalBoxes();
}

void FrameEditorMultiBox::DrawData()
{
  Optional<FrameEditorEdge> preview_edge;
  auto boxes = GetPreviewData(preview_edge);

  FrameEditorByteArray byte_array(boxes);
  auto edge_list = byte_array.ConvertToEdges();

  for (auto box : boxes)
  {
    DrawBox(box);
  }

  if (m_EditMode == FrameEditorMultiBoxMode::kAdd)
  {
    DrawActionBox(Box::FromPoints(m_DrawStart, m_DrawEnd));
  }
  else if (m_EditMode == FrameEditorMultiBoxMode::kRemove)
  {
    DrawActionBox(Box::FromPoints(m_DrawStart, m_DrawEnd));
  }

  for(std::size_t index = 0, end = edge_list.size(); index < end; ++index)
  {
    DrawEdge(edge_list[index]);
  }

  if (preview_edge)
  {
    DrawHighlightedEdge(preview_edge.Value());
  }
}

void FrameEditorMultiBox::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  Optional<std::size_t> best_index;
  float best_dist;

  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  Optional<FrameEditorEdge> preview_edge;
  auto boxes = GetPreviewData(preview_edge);

  FrameEditorByteArray byte_array(boxes);
  auto edge_list = byte_array.ConvertToEdges();

  if (pos.x() >= 0 && pos.y() >= 0 && pos.x() < width() && pos.y() < height())
  {
    for (std::size_t index = 0, end = edge_list.size(); index < end; ++index)
    {
      auto & edge = edge_list[index];

      auto p1 = TransformFrameToScreen(edge.m_P1 + FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type));
      auto p2 = TransformFrameToScreen(edge.m_P2 + FrameEditorByteArray::GetOffsetForEdgeType(edge.m_Type));
      auto dist = LineToPointDistance(p1, p2, cursor_pos);

      if (dist < 20)
      {
        if (best_index == false || dist < best_dist)
        {
          best_index = index;
          best_dist = dist;
        }
      }
    }
  }

  if (best_index)
  {
    m_PreviewEdge = edge_list[best_index.Value()];
  }
  else
  {
    m_PreviewEdge.Clear();
  }

  repaint();
}

void FrameEditorMultiBox::DrawLeave()
{
  if (m_Dragging == false)
  {
    m_PreviewEdge.Clear();
    repaint();
  }
}

bool FrameEditorMultiBox::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  if (alt)
  {
    m_DrawStart = frame_pos;
    m_DrawEnd = frame_pos;

    m_EditMode = FrameEditorMultiBoxMode::kRemove;
    return true;
  }
  else if (ctrl || m_PreviewEdge == false)
  {
    m_DrawStart = frame_pos;
    m_DrawEnd = frame_pos;

    m_EditMode = FrameEditorMultiBoxMode::kAdd;
    return true;
  }
  else if (m_PreviewEdge)
  {
    Optional<FrameEditorEdge> preview_edge;
    m_DrawStart = frame_pos;
    m_PreviewOffset = 0;

    m_EditMode = FrameEditorMultiBoxMode::kEdge;
    return true;
  }

  return false;
}

void FrameEditorMultiBox::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  m_DrawEnd = frame_pos;

  if (m_EditMode == FrameEditorMultiBoxMode::kEdge)
  {
    auto & edge = m_PreviewEdge.Value();
    m_PreviewOffset = FrameEditorByteArray::GetOffsetForEdgeMove(edge.m_Type, m_DrawStart, frame_pos);
  }

  repaint();
}

void FrameEditorMultiBox::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_EditMode != FrameEditorMultiBoxMode::kEdge || m_PreviewOffset != 0)
  {
    Optional<FrameEditorEdge> preview_edge;
    auto boxes = GetPreviewData(preview_edge);

    WriteData(boxes);
  }

  m_PreviewEdge.Clear();

  m_EditMode = FrameEditorMultiBoxMode::kNone;
  repaint();
}

void FrameEditorMultiBox::DrawCancel()
{
  m_PreviewEdge.Clear();

  m_EditMode = FrameEditorMultiBoxMode::kNone;
  repaint();
}
