
#include "StormData/StormDataParent.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/FrameData/FrameData.refl.h"

#include "SpriteBaseEditor.h"
#include "SpriteBaseTextureFrameElement.h"
#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "FrameEditorContainer.h"

SpriteBaseEditor::SpriteBaseEditor(PropertyFieldDatabase & property_db, const std::string & root_path, SpriteBaseDef & sprite, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_Sprite(sprite),
  m_TextureAccess(this, m_Sprite),
  m_TabWidget(std::make_unique<QTabWidget>()),
  m_Layout(std::make_unique<QHBoxLayout>()),
  m_TextureEditor(std::make_unique<SpriteBaseTextureEditor>(this, sprite)),
  m_FrameList(std::make_unique<SpriteBaseTextureFrameList>(this, sprite)),
  m_AnimationEditor(std::make_unique<SpriteBaseAnimationEditor>(this, sprite, m_TextureAccess))
{
  m_TabWidget->addTab(m_TextureEditor.get(), "Textures");
  m_TabWidget->addTab(m_FrameList.get(), "Frames");
  m_TabWidget->addTab(m_AnimationEditor.get(), "Animations");
  m_TabWidget->setTabPosition(QTabWidget::West);

  m_Layout->addWidget(m_TabWidget.get());
  setLayout(m_Layout.get());

  m_GlobalFrameDataCallback = [this] { return &m_Sprite.m_GlobalData; };
}

