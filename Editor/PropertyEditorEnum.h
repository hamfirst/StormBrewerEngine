#pragma once

#include <QWidget>
#include <QComboBox>

#include "GenericInput.h"

class RString;

class PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorEnum : public QWidget
{
  Q_OBJECT;

public:
  PropertyEditorEnum(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
    Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);

  ~PropertyEditorEnum();


  void HandleServerUpdate(const ReflectionChangeNotification & change);

  void UpdateValue();
  void UpdateChildPosition();

protected:
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:
  void valueChanged();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  uint64_t m_PathHash;
  uint64_t m_CallbackId;

  std::unique_ptr<QComboBox> m_Input;
  bool m_LocalChange;
  bool m_WriteBack;
};

