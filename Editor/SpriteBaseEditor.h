#pragma once

#include <memory>

#include <QTabWidget>
#include <QLayout>

#include <Editor/DocumentEditorWidgetBase.h>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "SpriteBaseAnimationEditor.h"
#include "SpriteBaseTextureEditor.h"
#include "SpriteBaseTextureFrameList.h"
#include "SpriteBaseTextureLoadList.h"

class SpriteBaseEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  SpriteBaseEditor(PropertyFieldDatabase & property_db, const std::string & root_path, SpriteBaseDef & sprite, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

protected:

  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList m_TextureAccess;

  std::unique_ptr<QTabWidget> m_TabWidget;
  std::unique_ptr<QHBoxLayout> m_Layout;

  std::unique_ptr<SpriteBaseTextureEditor> m_TextureEditor;
  std::unique_ptr<SpriteBaseTextureFrameList> m_FrameList;
  std::unique_ptr<SpriteBaseAnimationEditor> m_AnimationEditor;

  Delegate<NullOptPtr<FrameData>> m_GlobalFrameDataCallback;
};
