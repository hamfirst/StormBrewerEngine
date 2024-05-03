
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QClipboard>

#include "StormData/StormDataPath.h"
#include "StormData/StormDataJson.h"

#include "Foundation/Math/Intersection.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"

#include "AssetEditors/FrameEditor/FrameEditorSingleBox.h"
#include "AssetEditors/FrameEditor/FrameEditorTypes.refl.meta.h"
#include "AssetEditors/SpriteEditor/SpriteEditor.h"

FrameEditorSingleBox::FrameEditorSingleBox(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<ROpaque<Box>>, uint64_t> && getter,
  Delegate<NullOptPtr<ROpaque<Box>>> && default_val,
  Delegate<void, uint64_t, const Box &> && new_element,
  uint64_t frame_id,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, frame_id, parent),
  m_Watcher(editor),
  m_Getter(std::move(getter)),
  m_Default(std::move(default_val)),
  m_NewElement(std::move(new_element)),
  m_LocalChange(false)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  RefreshWatcher();
}

void FrameEditorSingleBox::HandleDataUpdate()
{
  auto data_list = m_Getter(m_FrameId);

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

void FrameEditorSingleBox::RefreshWatcher()
{
  m_Watcher.Clear();

  auto data_list = m_Getter(m_FrameId);
  if (data_list)
  {
    m_Watcher.Emplace(m_Editor);
    m_Watcher->SetPath(StormDataGetPath(*data_list).data(), true, true, [this] { return m_Getter(m_FrameId); });
    m_Watcher->SetChangeCallback([this](const ReflectionChangeNotification &) { HandleDataUpdate(); });
    m_Watcher->SetParentChangeCallback([this] { HandleDataUpdate(); });
    m_Watcher->SetChildChangeCallback([this] { HandleDataUpdate(); });
  }
}

void FrameEditorSingleBox::WriteData(Box & box)
{
  m_LocalChange = true;

  auto data_list = m_Getter(m_FrameId);
  if (data_list == nullptr)
  {
    m_NewElement(m_FrameId, box);
    RefreshWatcher();
  }
  else
  {
    (*data_list) = box;
  }

  repaint();
  m_LocalChange = false;
}

Box FrameEditorSingleBox::GetPreviewData(Optional<FrameEditorEdge> & preview_edge)
{
  Box box;

  auto data_list = m_Getter(m_FrameId);

  if (m_PreviewBox)
  {
    box = m_PreviewBox.Value();
    FrameEditorByteArray byte_array(box);

    FrameEditorEdge edge = m_PreviewEdge.Value();

    Optional<Box> new_box;
    byte_array.OffsetEdge(edge, m_PreviewOffset, new_box);

    preview_edge = edge;

    if (new_box)
    {
      std::vector<Box> new_box_list = { box, new_box.Value() };
      FrameEditorByteArray new_byte_array(new_box_list);

      auto box_list = new_byte_array.ConvertToMaximalBoxes();
      box = box_list[0];
    }
    else
    {
      auto box_list = byte_array.ConvertToMaximalBoxes();
      box = box_list[0];
    }
  }
  else if (data_list)
  {
    box = data_list->Value();
    preview_edge = m_PreviewEdge;
  }
  else
  {
    data_list = m_Default();
    if (data_list)
    {
      data_list = m_Default();
    }
    else
    {
      box = SpriteResource::GetDefaultSingleBox();
      preview_edge = m_PreviewEdge;
    }
  }

  return box;
}

void FrameEditorSingleBox::Copy()
{
  Optional<FrameEditorEdge> preview_point;

  FrameCopyData data;
  data.m_Valid = true;
  data.m_Type = FrameDataDefType::kSingleBox;
  data.m_Data = StormReflEncodeJson(GetPreviewData(preview_point));

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(StormReflEncodeJson(data).data());
}

void FrameEditorSingleBox::Paste()
{
  QClipboard *clipboard = QApplication::clipboard();
  auto clipboard_data = clipboard->text();

  FrameCopyData data;
  StormReflParseJson(data, clipboard_data.toStdString().data());

  if (data.m_Valid && data.m_Type == FrameDataDefType::kSingleBox)
  {
    Box frame_data;
    StormReflParseJson(frame_data, data.m_Data.data());

    WriteData(frame_data);
  }
}

void FrameEditorSingleBox::DrawData()
{
  Optional<FrameEditorEdge> preview_edge;
  Box box = GetPreviewData(preview_edge);

  FrameEditorByteArray byte_array(box);
  auto edge_list = byte_array.ConvertToEdges();

  DrawBox(box);

  for(std::size_t index = 0, end = edge_list.size(); index < end; ++index)
  {
    DrawEdge(edge_list[index]);
  }

  if (preview_edge)
  {
    DrawHighlightedEdge(preview_edge.Value());
  }
}

void FrameEditorSingleBox::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  Optional<std::size_t> best_index;
  float best_dist;

  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  Optional<FrameEditorEdge> preview_edge;
  Box box = GetPreviewData(preview_edge);

  FrameEditorByteArray byte_array(box);
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

void FrameEditorSingleBox::DrawLeave()
{
  if (m_Dragging == false)
  {
    m_PreviewEdge.Clear();
    repaint();
  }
}

bool FrameEditorSingleBox::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  if (m_PreviewEdge)
  {
    Optional<FrameEditorEdge> preview_edge;
    m_PreviewBox = GetPreviewData(preview_edge);
    m_DrawStart = frame_pos;
    m_PreviewOffset = 0;
    return true;
  }

  return false;
}

void FrameEditorSingleBox::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  auto & edge = m_PreviewEdge.Value();
  m_PreviewOffset = FrameEditorByteArray::GetOffsetForEdgeMove(edge.m_Type, m_DrawStart.Value(), frame_pos);

  repaint();
}

void FrameEditorSingleBox::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_PreviewOffset != 0)
  {
    Optional<FrameEditorEdge> preview_edge;
    auto box = GetPreviewData(preview_edge);

    WriteData(box);
  }

  m_PreviewEdge.Clear();
  m_PreviewBox.Clear();
  repaint();
}

void FrameEditorSingleBox::DrawCancel()
{
  m_PreviewEdge.Clear();
  m_PreviewBox.Clear();
  repaint();
}
