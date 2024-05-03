#pragma once

#include "AssetEditors/FrameEditor/FrameEditorBase.h"
#include "Tools/Editor/Utility/DocumentValueWatcher.h"

class FrameEditorLowerEdge : public FrameEditorBase
{
  Q_OBJECT;
public:
  FrameEditorLowerEdge(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>, uint64_t> && getter,
    Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>> && default_val,
    Delegate<void, uint64_t, const FrameDataLowerEdgeInfo &> && new_element,
    uint64_t frame_id,
    czstr data_name,
    QWidget * parent = nullptr);

protected:

  void HandleDataUpdate();
  virtual void RefreshWatcher();

  void WriteData(const FrameDataLowerEdgeInfo & data);
  FrameDataLowerEdgeInfo GetPreviewData();

  int GetEdgePos(FrameDataLowerEdgeInfo & info);

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
  Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>, uint64_t> m_Getter;
  Delegate<NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>> m_Default;
  Delegate<void, uint64_t, const FrameDataLowerEdgeInfo &> m_NewElement;

  bool m_LocalChange;

  Optional<FrameDataLowerEdgeInfo> m_PreviewData;
  Optional<Vector2> m_DrawStart;

  int m_PreviewOffset;
  bool m_Preview;
};

