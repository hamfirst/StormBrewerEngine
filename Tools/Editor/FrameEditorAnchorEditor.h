#pragma once

#include "FrameEditorBase.h"
#include "DocumentValueWatcher.h"

#include <QComboBox>

class FrameEditorAnchorEditor : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorAnchorEditor(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>, uint64_t> && getter,
    Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>> && default_val,
    Delegate<void, uint64_t, const RMergeList<FrameDataAnchorElement> &> && new_element,
    uint64_t frame_id,
    QWidget * parent = nullptr);

public slots:

  void currentTextChanged(const QString & currentText);

protected:

  void HandleDataUpdate();
  virtual void RefreshWatcher();

  void RefreshOptions();

  void WriteData(Vector2 & pos);
  Optional<Vector2> GetPreviewData();

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

  Optional<DocumentValueWatcher> m_Watcher;
  Optional<DocumentValueWatcher> m_AnchorListWatcher;

  Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>, uint64_t> m_Getter;
  Delegate<NullOptPtr<RMergeList<FrameDataAnchorElement>>> m_Default;
  Delegate<void, uint64_t, const RMergeList<FrameDataAnchorElement> &> m_NewElement;

  bool m_LocalChange;
  bool m_Preview;
  bool m_IgnoreSelectionChange;

  std::string m_SelectedAnchor;

  Optional<Vector2> m_PreviewLocation;

  std::unique_ptr<QComboBox> m_AnchorSelect;
};

