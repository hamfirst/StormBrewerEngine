#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/Entity/EntityDef.refl.h"

#include "AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"
#include "UI/GenericWidgets/GenericFrame.h"
#include "UI/PropertyEditors/PropertyEditor.h"

class EntityEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  EntityEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, EntityDef & entity, DocumentChangeLinkDelegate && change_link_callback,
    DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

private:

  EntityDef & m_Entity;

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_EntityProperties;

  PropertyEditor * m_PropertyEditor;
};
