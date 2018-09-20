#pragma once

#include <QWidget>

#include "GenericCheckbox.h"

class RBool;

struct PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorBool : public QWidget
{
  Q_OBJECT;

public:
  PropertyEditorBool(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
    Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);
  ~PropertyEditorBool();

  virtual void resizeEvent(QResizeEvent * ev) override;

  void HandleTextUpdate();
  void HandleServerUpdate(const ReflectionChangeNotification & change);

signals:

  void changed();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  uint64_t m_PathHash;
  uint64_t m_CallbackId;

  std::unique_ptr<GenericCheckbox> m_Input;
  bool m_LocalChange;
};

