#pragma once

#include "GenericListFrame.h"
#include "GenericList.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class SpriteBaseEditor;
class SpriteBaseTextureLoadList;
class SpriteBaseAnimationFrameListEditorDialog;

class SpriteBaseAnimationEditor : public GenericListFrame
{
  Q_OBJECT
public:
  SpriteBaseAnimationEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent = nullptr);
  ~SpriteBaseAnimationEditor();

protected:

  void OpenAnimEditorDialog(int animation_index = -1);

public slots:

  void handleAnimDialogAccepted();
  void handleAnimDialogClosed();

private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  std::vector<std::unique_ptr<SpriteBaseAnimationFrameListEditorDialog>> m_EditorDialogs;
};

