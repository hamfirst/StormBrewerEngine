#pragma once

#include "AssetEditors/FrameEditor/FrameEditorBase.h"
#include "Tools/Editor/Utility/DocumentValueWatcher.h"

#include <QComboBox>
#include <QPushButton>

class FrameEditorAnchorManager : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorAnchorManager(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    QWidget * parent = nullptr);

public slots:

  void currentTextChanged(const QString & currentText);
  void addAnchor();
  void removeAnchor();

protected:

  void RefreshOptions();

  void WriteData(Vector2 & pos);
  Vector2 GetPreviewData();

protected:

  virtual void Copy();
  virtual void Paste();

  virtual void DrawData();
  virtual void DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl);
  virtual void DrawLeave();
  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

protected:

  Optional<DocumentValueWatcher> m_AnchorListWatcher;

  bool m_LocalChange;
  bool m_Preview;
  bool m_IgnoreSelectionChange;

  std::string m_SelectedAnchor;

  Optional<Vector2> m_PreviewLocation;

  std::unique_ptr<QComboBox> m_AnchorSelect;
  std::unique_ptr<QPushButton> m_AddButton;
  std::unique_ptr<QPushButton> m_RemoveButton;
};

