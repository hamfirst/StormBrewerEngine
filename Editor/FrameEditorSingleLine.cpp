
#include <QPainter>
#include <QWheelEvent>

#include "StormData/StormDataPath.h"
#include "StormData/StormDataJson.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/Util.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"

#include "FrameEditorSingleLine.h"
#include "SpriteEditor.h"

FrameEditorSingleLine::FrameEditorSingleLine(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<ROpaque<FrameDataSingleLineInfo>>> && getter,
  Delegate<void, const FrameDataSingleLineInfo &> && new_element,
  uint64_t frame_id,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, frame_id, parent),
  m_Watcher(editor),
  m_Getter(std::move(getter)),
  m_NewElement(std::move(new_element)),
  m_LocalChange(false)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  RefreshWatcher();
}

void FrameEditorSingleLine::HandleDataUpdate()
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

void FrameEditorSingleLine::RefreshWatcher()
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

void FrameEditorSingleLine::WriteData(const FrameDataSingleLineInfo & data)
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
    *data_list = data;
  }

  repaint();
  m_LocalChange = false;
}

FrameDataSingleLineInfo FrameEditorSingleLine::GetPreviewData(Optional<Vector2> & preview_point)
{
  FrameDataSingleLineInfo data;

  auto data_list = m_Getter();

  if (m_PreviewData)
  {
    data = m_PreviewData.Value();
    if (m_PreviewPoint.Value() == 0)
    {
      data.m_Start += m_PreviewOffset;
    }
    else
    {
      data.m_End += m_PreviewOffset;
    }
  }
  else if (data_list)
  {
    data = data_list->Value();
  }
  else
  {
    data = SpriteResource::GetDefaultSingleLine();
  }

  if (m_PreviewPoint)
  {
    if (m_PreviewPoint.Value() == 0)
    {
      preview_point = data.m_Start;
    }
    else
    {
      preview_point = data.m_End;
    }
  }

  return data;
}

void FrameEditorSingleLine::DrawData()
{
  Optional<Vector2> preview_point;
  auto preview_data = GetPreviewData(preview_point);

  DrawLine(preview_data.m_Start, preview_data.m_End);
  DrawCornerControl(preview_data.m_Start);
  DrawCornerControl(preview_data.m_End);

  if (preview_point)
  {
    DrawHighlightedCornerControl(preview_point.Value());
  }
}

void FrameEditorSingleLine::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  Optional<std::size_t> best_index;
  float best_dist;

  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  Optional<Vector2> preview_point;
  auto preview_data = GetPreviewData(preview_point);

  auto start = TransformFrameToScreen(preview_data.m_Start);
  auto end = TransformFrameToScreen(preview_data.m_End);

  if (ManhattanDist(start, cursor_pos) < 20)
  {
    m_PreviewPoint = 0;
  }
  else if (ManhattanDist(end, cursor_pos) < 20)
  {
    m_PreviewPoint = 1;
  }
  else
  {
    m_PreviewPoint.Clear();
  }

  repaint();
}

void FrameEditorSingleLine::DrawLeave()
{
  if (m_Dragging == false)
  {
    m_PreviewPoint.Clear();
    repaint();
  }
}

bool FrameEditorSingleLine::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  if (m_PreviewPoint)
  {
    Optional<Vector2> preview_point;
    m_PreviewData = GetPreviewData(preview_point);
    m_DrawStart = frame_pos;
    m_PreviewOffset = {};
    return true;
  }

  return false;
}

void FrameEditorSingleLine::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);
  m_PreviewOffset = frame_pos - m_DrawStart.Value();

  repaint();
}

void FrameEditorSingleLine::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_PreviewOffset.x != 0 || m_PreviewOffset.x != 0)
  {
    Optional<Vector2> preview_point;
    auto data = GetPreviewData(preview_point);

    WriteData(data);
  }

  m_PreviewData.Clear();
  m_PreviewPoint.Clear();
  repaint();
}

void FrameEditorSingleLine::DrawCancel()
{
  m_PreviewData.Clear();
  m_PreviewPoint.Clear();
  repaint();
}
