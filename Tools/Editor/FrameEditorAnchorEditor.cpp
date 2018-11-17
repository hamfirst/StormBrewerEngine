
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QClipboard>

#include "StormData/StormDataPath.h"
#include "StormData/StormDataJson.h"

#include "Foundation/Math/Intersection.h"
#include "Foundation/Math/Util.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"

#include "FrameEditorAnchorEditor.h"
#include "FrameEditorTypes.refl.meta.h"
#include "SpriteEditor.h"

FrameEditorAnchorEditor::FrameEditorAnchorEditor(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>, uint64_t> && getter,
  Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>> && default_val,
  Delegate<void, uint64_t, const RMergeList<FrameDataAnchorElement> &> && new_element,
  uint64_t frame_id,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, frame_id, parent),
  m_Watcher(editor),
  m_AnchorListWatcher(editor),
  m_Getter(std::move(getter)),
  m_Default(std::move(default_val)),
  m_NewElement(std::move(new_element)),
  m_LocalChange(false),
  m_Preview(false),
  m_IgnoreSelectionChange(false)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  m_AnchorSelect = std::make_unique<QComboBox>(this);
  connect(m_AnchorSelect.get(), &QComboBox::currentTextChanged, this, &FrameEditorAnchorEditor::currentTextChanged);
  m_AnchorSelect->setGeometry(3, 3, 150, 20);

  m_AnchorListWatcher.Emplace(m_Editor);
  m_AnchorListWatcher->SetPath(StormDataGetPath(m_Sprite.m_Anchors).data(), true, true, [] { return true; });
  m_AnchorListWatcher->SetChangeCallback([this](const ReflectionChangeNotification &) { RefreshOptions(); });
  m_AnchorListWatcher->SetParentChangeCallback([this] { RefreshOptions(); });
  m_AnchorListWatcher->SetChildChangeCallback([this] { RefreshOptions(); });

  RefreshWatcher();
  RefreshOptions();
}

void FrameEditorAnchorEditor::currentTextChanged(const QString & currentText)
{
  if (m_IgnoreSelectionChange)
  {
    return;
  }

  m_SelectedAnchor = currentText.toStdString();
  repaint();
}

void FrameEditorAnchorEditor::HandleDataUpdate()
{
  auto data_list = m_Getter(m_FrameId);

  if (m_LocalChange)
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

void FrameEditorAnchorEditor::RefreshWatcher()
{
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

void FrameEditorAnchorEditor::RefreshOptions()
{
  m_IgnoreSelectionChange = true;

  int selected_index = -1;

  m_AnchorSelect->clear();
  for (auto elem : m_Sprite.m_Anchors)
  {
    m_AnchorSelect->addItem(elem.second.m_AnchorName.data());

    if (elem.second.m_AnchorName == m_SelectedAnchor)
    {
      selected_index = static_cast<int>(elem.first);
    }
  }

  if (selected_index == -1)
  {
    if (m_Sprite.m_Anchors.HighestIndex() == -1)
    {
      m_SelectedAnchor = "";
    }
    else
    {
      m_SelectedAnchor = m_Sprite.m_Anchors.begin()->second.m_AnchorName;
      m_AnchorSelect->setCurrentIndex(0);
    }
  }
  else
  {
    m_AnchorSelect->setCurrentIndex(selected_index);
  }

  m_IgnoreSelectionChange = false;
}

void FrameEditorAnchorEditor::WriteData(Vector2 & pos)
{
  if (m_SelectedAnchor.size() == 0)
  {
    return;
  }

  m_LocalChange = true;

  auto data_list = m_Getter(m_FrameId);
  if (data_list)
  {
    for (auto elem : *data_list)
    {
      if (elem.second.m_AnchorName == m_SelectedAnchor)
      {
        elem.second.m_Position = pos;

        m_LocalChange = false;
        repaint();
        return;
      }
    }

    FrameDataAnchorElement anchor_data;
    anchor_data.m_AnchorName = m_SelectedAnchor;
    anchor_data.m_Position = pos;
    data_list->EmplaceBack(std::move(anchor_data));

    m_LocalChange = false;
    repaint();
    return;
  }

  RMergeList<FrameDataAnchorElement> new_data_list;
  FrameDataAnchorElement anchor_data;
  anchor_data.m_AnchorName = m_SelectedAnchor;
  anchor_data.m_Position = pos;
  new_data_list.EmplaceBack(std::move(anchor_data));

  m_NewElement(m_FrameId, new_data_list);

  m_LocalChange = false;
  repaint();
}

Vector2 FrameEditorAnchorEditor::GetPreviewData()
{
  if (m_SelectedAnchor.size() == 0)
  {
    return {};
  }

  auto data_list = m_Getter(m_FrameId);

  if (m_PreviewLocation)
  {
    return m_PreviewLocation.Value();
  }
  else if (data_list)
  {
    for (auto elem : *data_list)
    {
      if (elem.second.m_AnchorName == m_SelectedAnchor)
      {
        return elem.second.m_Position.Value();
      }
    }
  }

  for (auto elem : m_Sprite.m_Anchors)
  {
    if (elem.second.m_AnchorName == m_SelectedAnchor)
    {
      return elem.second.m_DefaultPosition.Value();
    }
  }

  return {};
}

void FrameEditorAnchorEditor::Copy()
{
  FrameCopyData data;
  data.m_Valid = true;
  data.m_Type = FrameDataDefType::kAnchor;
  data.m_Data = StormReflEncodeJson(GetPreviewData());

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(StormReflEncodeJson(data).data());
}

void FrameEditorAnchorEditor::Paste()
{
  QClipboard *clipboard = QApplication::clipboard();
  auto clipboard_data = clipboard->text();

  FrameCopyData data;
  StormReflParseJson(data, clipboard_data.toStdString().data());

  if (data.m_Valid && data.m_Type == FrameDataDefType::kAnchor)
  {
    Vector2 frame_data;
    StormReflParseJson(frame_data, data.m_Data.data());

    WriteData(frame_data);
  }
}

void FrameEditorAnchorEditor::DrawData()
{
  auto preview_data = GetPreviewData();

  if (m_Preview)
  {
    DrawHighlightedCornerControl(preview_data);
  }
  else
  {
    DrawCornerControl(preview_data);
  }
}

void FrameEditorAnchorEditor::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  Optional<std::size_t> best_index;

  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  auto preview_point = GetPreviewData();

  auto screen_point = TransformFrameToScreen(preview_point);

  if (ManhattanDist(screen_point, cursor_pos) < 20)
  {
    m_Preview = true;
  }
  else
  {
    m_Preview = false;
  }

  repaint();
}

void FrameEditorAnchorEditor::DrawLeave()
{
  if (m_Preview)
  {
    m_Preview = false;
    repaint();
  }
}

bool FrameEditorAnchorEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);

  if (m_Preview)
  {
    m_PreviewLocation = GetPreviewData();
    m_Preview = true;
    return true;
  }

  return false;
}

void FrameEditorAnchorEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);
  m_PreviewLocation = frame_pos;

  repaint();
}

void FrameEditorAnchorEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_PreviewLocation)
  {
    auto data = GetPreviewData();
    WriteData(data);
  }

  m_PreviewLocation.Clear();
  repaint();
}

void FrameEditorAnchorEditor::DrawCancel()
{
  m_PreviewLocation.Clear();
  repaint();
}
