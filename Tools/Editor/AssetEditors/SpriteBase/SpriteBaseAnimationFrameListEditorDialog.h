#pragma once

#include <QDialog>

#include "Tools/Editor/UI/GenericWidgets/GenericListFrame.h"
#include "Tools/Editor/UI/GenericWidgets/GenericList.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "ui_AnimationFrameEditor.h"


class SpriteBaseEditor;
class SpriteBaseTextureLoadList;
class SpriteBaseTextureFrameList;
class SpriteBaseTimeline;

class SpriteBaseAnimationFrameListEditorDialog : public QDialog
{
  Q_OBJECT
public:
  SpriteBaseAnimationFrameListEditorDialog(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent = nullptr);
  ~SpriteBaseAnimationFrameListEditorDialog();

  void Finalize();

protected:
  virtual void closeEvent(QCloseEvent * ev) override;

signals:
  void closed();

private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  Ui::AnimationFrameEditor ui;

  std::unique_ptr<SpriteBaseTextureFrameList> m_FrameList;
  std::unique_ptr<SpriteBaseTimeline> m_Timeline;
};

