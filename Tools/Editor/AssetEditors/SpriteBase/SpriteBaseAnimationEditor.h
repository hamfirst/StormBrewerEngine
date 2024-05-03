#pragma once

#include "Tools/Editor/UI/GenericWidgets/GenericListFrame.h"
#include "Tools/Editor/UI/GenericWidgets/GenericList.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class SpriteBaseEditor;
class SpriteBaseTextureLoadList;
class SpriteBaseAnimationFrameListEditorDialog;
class SpriteBaseAnimationEventEditorDialog;

class SpriteBaseAnimationEditor : public GenericListFrame
{
  Q_OBJECT
public:
  SpriteBaseAnimationEditor(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, QWidget * parent = nullptr);
  ~SpriteBaseAnimationEditor();

protected:

  void closeEvent(QCloseEvent * ev) override;

  void closeChildWidgets();

  void OpenAnimEditorDialog(int animation_index = -1);
  void OpenAnimEventDialog(int animation_index);

public slots:

  void handleAnimDialogAccepted();
  void handleAnimDialogClosed();

  void handleEventDialogClosed();

private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  std::vector<SpriteBaseAnimationFrameListEditorDialog *> m_EditorDialogs;
  std::vector<SpriteBaseAnimationEventEditorDialog *> m_EventDialogs;
};

