#pragma once

#include <QOpenGLWidget>

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "GeometryEditorBase.h"
#include "FrameEditorUtil.h"
#include "DocumentValueWatcher.h"

class AtlasEditor;
class AtlasTextureLoadList;

class AtlasElementEditor : public GeometryEditorBase
{
  Q_OBJECT;
public:
  AtlasElementEditor(
          NotNullPtr<AtlasEditor> editor,
          AtlasDef & atlas,
          AtlasTextureLoadList & texture_access,
          QWidget * parent = nullptr);

  void SetSelectedElement(int elem_index);

protected:

  void HandleDataUpdate();
  void RefreshWatcher();

  void WriteData(AtlasDefElementPosition & data);
  Optional<AtlasDefElementPosition> GetPreviewData();

  template <typename Visitor>
  void VisitPoints(Visitor && visitor, NotNullPtr<AtlasDefElementPosition> elem_ptr);

  template <typename Visitor>
  void VisitEdges(Visitor && visitor, NotNullPtr<AtlasDefElementPosition> elem_ptr);

protected:
  virtual void DrawData() override;
  virtual void DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl) override;
  virtual void DrawLeave() override;
  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl) override;
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl) override;
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl) override;
  virtual void DrawCancel() override;


  virtual NullOptPtr<TextureAsset> GetTexture() override;
protected:

  NotNullPtr<AtlasEditor> m_Editor;
  AtlasDef & m_Atlas;
  AtlasTextureLoadList & m_TextureAccess;

  Optional<DocumentValueWatcher> m_Watcher;
  Optional<int> m_PreviewPoint;
  Optional<Vector2> m_DrawStart;
  Optional<Vector2> m_PreviewOffset;

  bool m_LocalChange;

  Optional<AtlasDefElementPosition> m_PreviewData;

  int m_SelectedElementIndex;
};

