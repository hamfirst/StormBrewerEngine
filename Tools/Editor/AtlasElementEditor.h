#pragma once

#include <QOpenGLWidget>

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "GeometryEditorBase.h"
#include "FrameEditorUtil.h"

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

protected:

  virtual NullOptPtr<TextureAsset> GetTexture() override;
protected:

  NotNullPtr<AtlasEditor> m_Editor;
  AtlasDef & m_Atlas;
  AtlasTextureLoadList & m_TextureAccess;

  uint32_t m_SelectedName;
};

