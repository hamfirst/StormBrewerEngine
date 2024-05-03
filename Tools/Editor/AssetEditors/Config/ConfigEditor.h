#pragma once

#include <memory>

#include <QTabWidget>
#include <QGridLayout>

#include "Runtime/Config/ConfigManager.h"

#include "AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"
#include "UI/GenericWidgets/GenericFrame.h"
#include "UI/PropertyEditors/PropertyEditor.h"

class ConfigEditor : public DocumentEditorWidgetBase
{
  Q_OBJECT;
public:
  ConfigEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, void * config_ptr, ConfigRegistrationInfo & config_info,
    DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback, 
    DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent = nullptr);

private:

  std::unique_ptr<QGridLayout> m_Layout;
  std::unique_ptr<GenericFrame> m_ConfigProperties;

  PropertyEditor * m_PropertyEditor;
  void * m_ConfigPtr;
  ConfigRegistrationInfo & m_ConfigInfo;
};
