#pragma once

#include <QWidget>
#include <QFrame>

#include "ScrollingPanel.h"
#include "DocumentEditorWidgetBase.h"

#include "Foundation/Common.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

#include <StormRefl/StormReflMetaInfoBase.h>
#include <StormData/StormDataPath.h>

class PropertyEditor : public ScrollingPanel
{
  Q_OBJECT;
public:
  PropertyEditor(QWidget * parent = nullptr);

  void LoadObject(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, 
    bool create_callback, Delegate<void *> && data_ptr, const std::string & base_path);

  template <typename T>
  void LoadStruct(NotNullPtr<DocumentEditorWidgetBase> editor, T & t, bool create_callback)
  {
    auto path = StormDataGetPath(t);
    auto prop = editor->GetPropertyFieldDatabase().FindStructData(StormReflTypeInfo<T>::GetNameHash());
    LoadObject(editor, prop, create_callback, [&]() -> void * { return &t; }, path);
  }

  template <typename T>
  void LoadStruct(NotNullPtr<DocumentEditorWidgetBase> editor, T & t, Delegate<void *> && data_ptr, bool create_callback)
  {
    auto path = StormDataGetPath(t);
    auto prop = editor->GetPropertyFieldDatabase().FindStructData(StormReflTypeInfo<T>::GetNameHash());
    LoadObject(editor, prop, create_callback, std::move(data_ptr), path);
  }

  void Unload();

protected:

  virtual void resizeEvent(QResizeEvent * ev) override;
};


