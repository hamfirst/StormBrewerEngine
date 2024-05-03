#pragma once

#include <QWidget>

#include "Foundation/Common.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

std::unique_ptr<QWidget> PropertyEditorCreate(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, bool create_callback,
  Delegate<void *> && data_ptr, const std::string & path, Delegate<void> && size_change_cb, czstr name, QWidget * parent);
