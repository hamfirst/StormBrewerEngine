#pragma once

#include <memory>

#include <QTabWidget>
#include <QLayout>

#include <Editor/DocumentEditorWidgetBase.h>

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "SpriteBaseAnimationEditor.h"
#include "SpriteBaseTextureEditor.h"
#include "SpriteBaseSkinEditor.h"
#include "SpriteBaseTextureFrameList.h"
#include "SpriteBaseTextureLoadList.h"
#include "SpriteBaseTextureImportDialog.h"

class SpriteBaseEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  SpriteBaseEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, SpriteBaseDef & sprite, 
    DocumentChangeLinkDelegate && change_link_callback,  DocumentBeginTransactionDelegate && begin_transaction_callback, 
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

  virtual bool IsTileSheet() const = 0;
protected:

  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList m_TextureAccess;

  std::unique_ptr<QTabWidget> m_TabWidget;
  std::unique_ptr<QHBoxLayout> m_Layout;

  std::unique_ptr<SpriteBaseTextureEditor> m_TextureEditor;
  std::unique_ptr<SpriteBaseSkinEditor> m_SkinEditor;
  std::unique_ptr<SpriteBaseTextureFrameList> m_FrameList;
  std::unique_ptr<SpriteBaseAnimationEditor> m_AnimationEditor;

  Delegate<NullOptPtr<FrameData>, uint64_t> m_GlobalFrameDataCallback;
  Delegate<NullOptPtr<FrameData>> m_EmptyFrameDataCallback;
};
