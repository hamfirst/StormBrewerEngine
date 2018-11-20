#pragma once

#include <QOpenGLWidget>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "GeometryEditorBase.h"
#include "FrameEditorUtil.h"

class SpriteBaseEditor;
class SpriteBaseTextureLoadList;

class FrameEditorBase : public GeometryEditorBase
{
  Q_OBJECT;
public:
  FrameEditorBase(
    NotNullPtr<SpriteBaseEditor> editor,
    SpriteBaseDef & sprite,
    SpriteBaseTextureLoadList & texture_access,
    uint64_t frame_id,
    QWidget * parent = nullptr);

  void SetFrame(uint64_t frame_id);

protected:

  virtual Optional<Vector2> GetFrameSize() override;
  virtual uint64_t GetFrameId() override;
  virtual NullOptPtr<TextureAsset> GetTexture() override;

  virtual void RefreshWatcher();
  void UpdateFrameSize();

protected:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  uint64_t m_FrameId;
  int m_FrameWidth;
  int m_FrameHeight;
};

