
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
#include "Runtime/SpriteBase/SpriteBaseDef.refl.meta.h"

#include "AssetEditors/FrameEditor/FrameEditorAnchorManager.h"
#include "AssetEditors/FrameEditor/FrameEditorTypes.refl.meta.h"
#include "AssetEditors/SpriteEditor/SpriteEditor.h"
#include "Tools/Editor/UI/UtilityWidgets/TextInputDialog.h"

FrameEditorAnchorManager::FrameEditorAnchorManager(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  QWidget * parent) :
  FrameEditorBase(editor, sprite, texture_access, 0, parent),
  m_AnchorListWatcher(editor),
  m_LocalChange(false),
  m_Preview(false),
  m_IgnoreSelectionChange(false)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);

  m_AnchorSelect = std::make_unique<QComboBox>(this);
  connect(m_AnchorSelect.get(), &QComboBox::currentTextChanged, this, &FrameEditorAnchorManager::currentTextChanged);
  m_AnchorSelect->setGeometry(3, 3, 150, 20);

  m_AddButton = std::make_unique<QPushButton>("+", this);
  m_AddButton->setGeometry(3, 25, 35, 25);
  connect(m_AddButton.get(), &QPushButton::clicked, this, &FrameEditorAnchorManager::addAnchor);
  m_RemoveButton = std::make_unique<QPushButton>("-", this);
  m_RemoveButton->setGeometry(41, 25, 35, 25);
  connect(m_RemoveButton.get(), &QPushButton::clicked, this, &FrameEditorAnchorManager::removeAnchor);

  m_AnchorListWatcher.Emplace(m_Editor);
  m_AnchorListWatcher->SetPath(StormDataGetPath(m_Sprite.m_Anchors).data(), true, true, [] { return true; });
  m_AnchorListWatcher->SetChangeCallback([this](const ReflectionChangeNotification &) { RefreshOptions(); });
  m_AnchorListWatcher->SetParentChangeCallback([this] { RefreshOptions(); });
  m_AnchorListWatcher->SetChildChangeCallback([this] { RefreshOptions(); });

  RefreshWatcher();
  RefreshOptions();
}

void FrameEditorAnchorManager::currentTextChanged(const QString & currentText)
{
  if (m_IgnoreSelectionChange)
  {
    return;
  }

  m_SelectedAnchor = currentText.toStdString();
  repaint();
}

void FrameEditorAnchorManager::addAnchor()
{
  auto dialog = new TextInputDialog("Enter Anchor Name...");
  auto result = dialog->exec();

  if (result == QDialog::Rejected)
  {
    return;
  }

  SpriteBaseDefAnchor anchor;
  anchor.m_AnchorName = dialog->GetValue().toStdString();
  anchor.m_DefaultPosition = Vector2{};

  m_Sprite.m_Anchors.EmplaceBack(std::move(anchor));
}

void FrameEditorAnchorManager::removeAnchor()
{
  for (auto elem : m_Sprite.m_Anchors)
  {
    if (elem.second.m_AnchorName == m_SelectedAnchor)
    {
      m_Sprite.m_Anchors.RemoveAt(elem.first);
      return;
    }
  }
}

void FrameEditorAnchorManager::RefreshOptions()
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

void FrameEditorAnchorManager::WriteData(Vector2 & pos)
{
  if (m_SelectedAnchor.size() == 0)
  {
    return;
  }

  m_LocalChange = true;

  for (auto elem : m_Sprite.m_Anchors)
  {
    if (elem.second.m_AnchorName == m_SelectedAnchor)
    {
      elem.second.m_DefaultPosition = pos;
      break;
    }
  }

  m_LocalChange = false;
  repaint();
}

Vector2 FrameEditorAnchorManager::GetPreviewData()
{
  if (m_SelectedAnchor.size() == 0)
  {
    return {};
  }

  if (m_PreviewLocation)
  {
    return m_PreviewLocation.Value();
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

void FrameEditorAnchorManager::Copy()
{
  FrameCopyData data;
  data.m_Valid = true;
  data.m_Type = FrameDataDefType::kAnchor;
  data.m_Data = StormReflEncodeJson(GetPreviewData());

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(StormReflEncodeJson(data).data());
}

void FrameEditorAnchorManager::Paste()
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

void FrameEditorAnchorManager::DrawData()
{
  if (m_SelectedAnchor.size() == 0)
  {
    return;
  }

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

void FrameEditorAnchorManager::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  if (m_SelectedAnchor.size() == 0)
  {
    m_Preview = false;
    return;
  }

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

void FrameEditorAnchorManager::DrawLeave()
{
  if (m_Preview)
  {
    m_Preview = false;
    repaint();
  }
}

bool FrameEditorAnchorManager::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
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

void FrameEditorAnchorManager::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);
  m_PreviewLocation = frame_pos;

  repaint();
}

void FrameEditorAnchorManager::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if (m_PreviewLocation)
  {
    auto data = GetPreviewData();
    WriteData(data);
  }

  m_PreviewLocation.Clear();
  repaint();
}

void FrameEditorAnchorManager::DrawCancel()
{
  m_PreviewLocation.Clear();
  repaint();
}
