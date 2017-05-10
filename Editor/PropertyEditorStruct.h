#pragma once

#include <QWidget>
#include <QLabel>
#include <QGroupBox>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

class DocumentEditorWidgetBase;

class PropertyEditorStruct : public QWidget
{
  Q_OBJECT;
public:
  PropertyEditorStruct(NotNullPtr<DocumentEditorWidgetBase> editor, 
    NotNullPtr<PropertyField> prop, Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);

  ~PropertyEditorStruct();

  virtual void resizeEvent(QResizeEvent * ev) override;

  void SetSizeChangeCallback(Delegate<void> && size_change_cb);
  void HandleChildSizeChanged(int child_index);
  void RespositionChildren();

private:
  NotNullPtr<DocumentEditorWidgetBase> m_Editor;

  struct ChildElement
  {
    std::unique_ptr<QWidget> m_Widget;
    std::unique_ptr<QLabel> m_NormalLabel;
    std::unique_ptr<QGroupBox> m_FrameLabel;
  };

  std::vector<ChildElement> m_ChildElements;

  NotNullPtr<PropertyField> m_Property;
  Delegate<void *> m_PropertyPtr;

  Delegate<void> m_SizeChangedCallback;
};

