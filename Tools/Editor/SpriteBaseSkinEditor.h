#pragma once

#include "GenericListFrame.h"
#include "GenericList.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class SpriteBaseEditor;
class SpriteBaseTextureLoadList;
class SpriteBaseAnimationFrameListEditorDialog;
class SpriteBaseAnimationEventEditorDialog;

class SpriteBaseSkinEditor : public GenericListFrame
{
  Q_OBJECT
public:
  SpriteBaseSkinEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent = nullptr);
  ~SpriteBaseSkinEditor();

protected:


public slots:


private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
};

