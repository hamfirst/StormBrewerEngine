#pragma once

#include <QLayout>

#include "StormTech/StormData/StormDataJson.h"
#include "StormTech/StormData/StormDataChangePacket.h"
#include "StormTech/StormData/StormDataSync.h"
#include "StormTech/StormData/StormDataParent.h"

#include "Foundation/Any/Any.h"
#include "Runtime/Config/ConfigManager.h"

#include "AssetEditors/DocumentEditor/DocumentEditorBase.h"
#include "AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"
#include "AssetEditors/Config/ConfigEditor.h"

class DocumentEditorConfig : public DocumentEditorBase
{
public:
  DocumentEditorConfig(EditorContainer & editor_container, ConfigRegistrationInfo & config_info, 
    PropertyFieldDatabase & property_db, const std::string & root_path, DocumentOutputDelegate && output_delegate, QWidget *parent = nullptr);
  virtual ~DocumentEditorConfig();

  virtual void GotDocumentChange(ReflectionChangeNotification & change) override;
  virtual void GotDocumentStateChange(DocumentState state, const std::string & document_data) override;

  virtual void ApplyServerChange(const ReflectionChangeNotification & change) override;
  virtual void ApplyLocalChange(const ReflectionChangeNotification & change) override;

  virtual void UpdateLinks() override;

  virtual void SyncHotSpots() override;
  virtual void ClearExistingContent() override;

private:

  ConfigRegistrationInfo & m_ConfigInfo;

  ConfigEditor * m_Widget;
  QHBoxLayout * m_Layout;

  Any m_ClientCopy;
  Any m_ServerCopy;
};
