
#include "SpriteBaseAnimationFrameListEditorDialog.h"
#include "SpriteBaseTextureFrameList.h"
#include "SpriteBaseTimeline.h"

SpriteBaseAnimationFrameListEditorDialog::SpriteBaseAnimationFrameListEditorDialog(NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent) :
  QDialog(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_FrameList(std::make_unique<SpriteBaseTextureFrameList>(m_Editor, m_Sprite, this)),
  m_Timeline(std::make_unique<SpriteBaseTimeline>(m_Editor, m_Sprite, m_TextureAccess, animation_index, this))
{
  ui.setupUi(this);

  m_FrameList->setGeometry(0, 0, width(), height() - 200);
  m_FrameList->SetFrameSelectionCallback([this](uint64_t frame_id) { m_Timeline->AddFrame(frame_id); });
  m_FrameList->show();

  m_Timeline->setGeometry(0, height() - 200, width(), 150);
  m_Timeline->show();
}

SpriteBaseAnimationFrameListEditorDialog::~SpriteBaseAnimationFrameListEditorDialog()
{

}

void SpriteBaseAnimationFrameListEditorDialog::Finalize()
{
  m_Timeline->Finalize();
}

void SpriteBaseAnimationFrameListEditorDialog::closeEvent(QCloseEvent * ev)
{
  emit closed();
}
