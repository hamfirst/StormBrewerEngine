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
    Delegate<NullOptPtr<RMergeList<FrameDataSingleLine>>> && getter,
    uint64_t frame_id,
    czstr data_name,
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();

  void FindDataIndex();
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
  Delegate<NullOptPtr<RMergeList<FrameDataSingleLine>>> m_Getter;

  std::string m_FrameDataName;
  int m_FrameDataIndex;
  bool m_LocalChange;

  Optional<FrameDataSingleLineInfo> m_PreviewData;
  Optional<Vector2> m_DrawStart;

  Optional<int> m_PreviewPoint;
  Vector2 m_PreviewOffset;
};

