#pragma once

#include "FrameEditorBase.h"
#include "DocumentValueWatcher.h"

class FrameEditorLowerEdge : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorLowerEdge(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<RMergeList<FrameDataLowerEdge>>> && getter,
    uint64_t frame_id,
    czstr data_name,
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();

  void FindDataIndex();
  void WriteData(const FrameDataLowerEdgeInfo & data);
  FrameDataLowerEdgeInfo GetPreviewData();

  int GetEdgePos(FrameDataLowerEdgeInfo & info);

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
  Delegate<NullOptPtr<RMergeList<FrameDataLowerEdge>>> m_Getter;

  std::string m_FrameDataName;
  int m_FrameDataIndex;
  bool m_LocalChange;

  Optional<FrameDataLowerEdgeInfo> m_PreviewData;
  Optional<Vector2> m_DrawStart;

  int m_PreviewOffset;
  bool m_Preview;
};

