#pragma once

#include <QWidget>

#include "Tools/Editor/UI/GenericWidgets/GenericInput.h"

class RString;

struct PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorNumber : public QWidget
{
  Q_OBJECT;

public:
  PropertyEditorNumber(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
    Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);

  ~PropertyEditorNumber();

  virtual void resizeEvent(QResizeEvent * ev) override;

  void HandleTextUpdate();
  void HandleServerUpdate(const ReflectionChangeNotification & change);
  void UpdateText();

signals:

  void changed();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  uint64_t m_PathHash;
  uint64_t m_CallbackId;
  uint64_t m_ParentCallbackId;

  std::unique_ptr<GenericInput> m_Input;
  bool m_LocalChange;
};

