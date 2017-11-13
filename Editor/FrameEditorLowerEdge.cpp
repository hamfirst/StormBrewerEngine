
#include <QPainter>
#include <QWheelEvent>

#include "StormData/StormDataPath.h"
#include "StormData/StormDataJson.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/Util.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"

#include "FrameEditorLowerEdge.h"
#include "SpriteEditor.h"

FrameEditorLowerEdge::FrameEditorLowerEdge(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>> && getter,
  Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>> && default_val,
  Delegate<void, const FrameDataLowerEdgeInfo &> && new_element,
  uint64_t frame_id,
  czstr data_name,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, frame_id, parent),
  m_Watcher(editor),
  m_Getter(std::move(getter)),
  m_Default(std::move(default_val)),
  m_NewElement(std::move(new_element)),
  m_LocalChange(false),
  m_Preview(false)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  RefreshWatcher();
}

void FrameEditorLowerEdge::HandleDataUpdate()
{
  auto data_list = m_Getter();

  if(m_LocalChange)
  {
    return;
  }

  RefreshWatcher();

  if (data_list == nullptr)
  {
    return;
  }

  if (m_Dragging)
  {
    StopDrawing();
  }

  repaint();
}

void FrameEditorLowerEdge::RefreshWatcher()
{
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

void FrameEditorLowerEdge::WriteData(const FrameDataLowerEdgeInfo & data)
{
  m_LocalChange = true;

  auto data_list = m_Getter();
  if (data_list == nullptr)
  {
    m_NewElement(data);
    RefreshWatcher();
  }
  else
  {
    (*data_list) = data;
  }

  repaint();
  m_LocalChange = false;
}

FrameDataLowerEdgeInfo FrameEditorLowerEdge::GetPreviewData()
{
  FrameDataLowerEdgeInfo data;

  auto data_list = m_Getter();

  if (m_PreviewData)
  {
    data = m_PreviewData.Value();
    data.m_OffsetPixels += m_PreviewOffset;
  }
  else if (data_list)
  {
    data = (*data_list).Value();
  }
  else
  {
    data_list = m_Default();
    if (data_list)
    {
      data = (*data_list).Value();
    }
    else
    {
      data.m_OffsetPixels = 0;
    }
  }

  return data;
}


int FrameEditorLowerEdge::GetEdgePos(FrameDataLowerEdgeInfo & info)
{
  auto frame = Box::FromFrameCenterAndSize(Vector2{}, Vector2(m_FrameWidth, m_FrameHeight));
  int y = m_Editor->IsTileSheet() ? frame.m_End.y + 1 + info.m_OffsetPixels : frame.m_Start.y + info.m_OffsetPixels;
  return y;
}

void FrameEditorLowerEdge::DrawData()
{
  auto preview_data = GetPreviewData();

  auto frame = Box::FromFrameCenterAndSize(Vector2{}, Vector2(m_FrameWidth, m_FrameHeight));
  auto y = GetEdgePos(preview_data);

  if (m_Preview)
  {
    DrawHighlightedLine(Vector2(frame.m_Start.x, y), Vector2(frame.m_End.x + 1, y));
    DrawHighlightedCornerControl(Vector2(frame.m_Start.x, y));
    DrawHighlightedCornerControl(Vector2(frame.m_End.x + 1, y));
  }
  else
  {
    DrawLine(Vector2(frame.m_Start.x, y), Vector2(frame.m_End.x + 1, y));
    DrawCornerControl(Vector2(frame.m_Start.x, y));
    DrawCornerControl(Vector2(frame.m_End.x + 1, y));
  }
}

void FrameEditorLowerEdge::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  Optional<std::size_t> best_index;
  float best_dist;

  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  Optional<Vector2> preview_point;
  auto preview_data = GetPreviewData();

  auto frame = Box::FromFrameCenterAndSize(Vector2{}, Vector2(m_FrameWidth, m_FrameHeight));
  auto y = GetEdgePos(preview_data);

  auto edge_pos = TransformFrameToScreen(Vector2(0, y));

  if (abs(edge_pos.y - cursor_pos.y) < 20)
  {
    m_Preview = true;
  }
  else
  {
    m_Preview = false;
  }

  repaint();
}

void FrameEditorLowerEdge::DrawLeave()
{
  if (m_Preview)
  {
    m_Preview = false;
    repaint();
  }
}

bool FrameEditorLowerEdge::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  if (m_Preview)
  {
    Optional<Vector2> preview_point;
    m_PreviewData = GetPreviewData();
    m_DrawStart = frame_pos;
    m_PreviewOffset = {};
    return true;
  }

  return false;
}

void FrameEditorLowerEdge::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);
  m_PreviewOffset = frame_pos.y - m_DrawStart.Value().y;

  repaint();
}

void FrameEditorLowerEdge::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_PreviewOffset != 0)
  {
    auto data = GetPreviewData();

    WriteData(data);
  }

  m_PreviewData.Clear();
  m_Preview = false;
  repaint();
}

void FrameEditorLowerEdge::DrawCancel()
{
  m_PreviewData.Clear();
  m_Preview = false;
  repaint();
}
