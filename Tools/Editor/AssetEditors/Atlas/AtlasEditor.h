#pragma once

#include <memory>

#include <QTabWidget>
#include <QLayout>

#include "AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "AssetEditors/Atlas/AtlasTextureEditor.h"
#include "AssetEditors/Atlas/AtlasElementEditorContainer.h"
#include "AssetEditors/Atlas/AtlasTextureLoadList.h"

class AtlasEditor : public DocumentEditorWidgetBase
{
Q_OBJECT;
public:
  AtlasEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, AtlasDef & atlas,
              DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback,
              DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

protected:

  void AddNewElement(int texture_index);

protected:

  AtlasDef & m_Atlas;
  AtlasTextureLoadList m_TextureAccess;

  std::unique_ptr<QTabWidget> m_TabWidget;
  std::unique_ptr<QHBoxLayout> m_Layout;

  std::unique_ptr<AtlasTextureEditor> m_TextureEditor;
  std::unique_ptr<AtlasElementEditorContainer> m_ElementEditor;
};
