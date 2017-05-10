#pragma once

#include <QWidget>
#include <QPushButton>

#include "GenericInput.h"

class RString;

class PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorFile : public QWidget
{
  Q_OBJECT;

public:
  PropertyEditorFile(DocumentEditorWidgetBase * editor, PropertyField * prop, Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);
  ~PropertyEditorFile();

  virtual void resizeEvent(QResizeEvent * ev) override;

  void HandleTextUpdate();
  void HandleServerUpdate(const ReflectionChangeNotification & change);

public slots:

  void handleFileButtonPress();

signals:

  void changed();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  uint64_t m_PathHash;
  uint64_t m_CallbackId;

  std::unique_ptr<GenericInput> m_Input;
  std::unique_ptr<QPushButton> m_FileButton;
  bool m_LocalChange;
};

