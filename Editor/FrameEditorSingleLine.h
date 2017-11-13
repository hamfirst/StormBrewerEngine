#pragma once

#include "FrameEditorBase.h"
#include "DocumentValueWatcher.h"

class FrameEditorSingleLine : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorSingleLine(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<ROpaque<FrameDataSingleLineInfo>>> && getter,
    Delegate<NullOptPtr<ROpaque<FrameDataSingleLineInfo>>> && default_val,
    Delegate<void, const FrameDataSingleLineInfo &> && new_element,
    uint64_t frame_id,
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();
  void RefreshWatcher();

  void WriteData(const FrameDataSingleLineInfo & data);
  FrameDataSingleLineInfo GetPreviewData(Optional<Vector2> & preview_point);

protected:

  virtual void DrawData();
  virtual void DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl);
  virtual void DrawLeave();
  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

protected:

  Optional<DocumentValueWatcher> m_Watcher;
  Delegate<NullOptPtr<ROpaque<FrameDataSingleLineInfo>>> m_Getter;
  Delegate<NullOptPtr<ROpaque<FrameDataSingleLineInfo>>> m_Default;
  Delegate<void, const FrameDataSingleLineInfo &> m_NewElement;

  bool m_LocalChange;

  Optional<FrameDataSingleLineInfo> m_PreviewData;
  Optional<Vector2> m_DrawStart;

  Optional<int> m_PreviewPoint;
  Vector2 m_PreviewOffset;
};

