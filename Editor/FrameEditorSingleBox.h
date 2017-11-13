#pragma once

#include "FrameEditorBase.h"
#include "DocumentValueWatcher.h"

class FrameEditorSingleBox : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorSingleBox(
    NotNullPtr<SpriteBaseEditor> editor, 
    SpriteBaseDef & sprite, 
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<ROpaque<Box>>> && getter,
    Delegate<NullOptPtr<ROpaque<Box>>> && default_val,
    Delegate<void, const Box &> && new_element,
    uint64_t frame_id, 
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();
  void RefreshWatcher();

  void WriteData(Box & box);
  Box GetPreviewData(Optional<FrameEditorEdge> & preview_edge);

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
  Delegate<NullOptPtr<ROpaque<Box>>> m_Getter;
  Delegate<NullOptPtr<ROpaque<Box>>> m_Default;
  Delegate<void, const Box &> m_NewElement;

  bool m_LocalChange;

  Optional<Box> m_PreviewBox;
  Optional<Vector2> m_DrawStart;

  Optional<FrameEditorEdge> m_PreviewEdge;
  int m_PreviewOffset;
};

