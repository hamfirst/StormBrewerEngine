#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

class DocumentEditorWidgetBase;

class PropertyEditorList : public QWidget
{
  Q_OBJECT;
public:
  PropertyEditorList(NotNullPtr<DocumentEditorWidgetBase> editor,
    NotNullPtr<PropertyField> prop, Delegate<void *> data_ptr, const std::string & path, czstr list_name, QWidget * parent = nullptr);

  ~PropertyEditorList();

  void SetSizeChangeCallback(Delegate<void> && size_change_cb);
  void SyncElements();
  void HandleChildSizeChanged(std::size_t child_index);
  void RespositionChildren();

  void AppendElement();
  void RemoveAtIndex(std::size_t index);

  void HandleServerChange(const ReflectionChangeNotification & notification);

public slots:

  void handleAddButtonClicked();
  void handleRemoveButtonClicked();

protected:

  virtual void resizeEvent(QResizeEvent * ev) override;

private:
  NotNullPtr<DocumentEditorWidgetBase> m_Editor;

  NotNullPtr<PropertyField> m_Property;
  Delegate<void *> m_PropertyPtr;

  std::string m_Path;
  uint64_t m_PathHash;
  uint64_t m_CallbackId;

  Delegate<void> m_SizeChangedCallback;

  std::unique_ptr<QGroupBox> m_Frame;
  std::unique_ptr<QPushButton> m_AddButton;

  struct ChildElement
  {
    std::unique_ptr<QGroupBox> m_FrameLabel;
    std::unique_ptr<QPushButton> m_RemoveButton;
    std::unique_ptr<QWidget> m_Widget;
  };

  std::map<std::size_t, ChildElement> m_ChildElements;
};

