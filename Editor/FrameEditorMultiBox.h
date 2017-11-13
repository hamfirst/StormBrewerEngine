#pragma once

#include <QObject>

#include "FrameEditorBase.h"
#include "DocumentValueWatcher.h"

enum class FrameEditorMultiBoxMode
{
  kNone,
  kEdge,
  kAdd,
  kRemove,
};

class FrameEditorMultiBox : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorMultiBox(
    NotNullPtr<SpriteBaseEditor> editor, 
    SpriteBaseDef & sprite, 
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> && getter,
    Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> && default_val,
    Delegate<void, std::vector<Box> &&> && new_element,
    uint64_t frame_id, 
    bool use_default_data,
    QWidget * parent = nullptr);

  void ChangeFrame(uint64_t frame_id,
    Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> && getter,
    Delegate<void, std::vector<Box> &&> && new_element);

protected:

  void HandleDataUpdate();
  void RefreshWatcher();

  void WriteData(const std::vector<Box> & box);
  std::vector<Box> GetPreviewData(Optional<FrameEditorEdge> & preview_edge);

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
  Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> m_Getter;
  Delegate<NullOptPtr<ROpaque<std::vector<Box>>>> m_Default;
  Delegate<void, std::vector<Box> &&> m_NewElement;

  bool m_UseDefault;
  bool m_LocalChange;

  Vector2 m_DrawStart;
  Vector2 m_DrawEnd;

  Optional<FrameEditorEdge> m_PreviewEdge;
  int m_PreviewOffset;

  FrameEditorMultiBoxMode m_EditMode;
};


