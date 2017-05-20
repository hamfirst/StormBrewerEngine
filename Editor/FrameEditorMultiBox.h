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
    Delegate<NullOptPtr<RMergeList<FrameDataMultiBox>>> && getter,
    uint64_t frame_id, 
    czstr data_name,
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();

  void FindDataIndex();
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
  Delegate<NullOptPtr<RMergeList<FrameDataMultiBox>>> m_Getter;

  std::string m_FrameDataName;
  int m_FrameDataIndex;
  bool m_LocalChange;

  Vector2 m_DrawStart;
  Vector2 m_DrawEnd;

  Optional<FrameEditorEdge> m_PreviewEdge;
  int m_PreviewOffset;

  FrameEditorMultiBoxMode m_EditMode;
};


