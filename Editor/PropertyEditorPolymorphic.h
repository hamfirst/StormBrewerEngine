#pragma once

#include <QWidget>
#include <QComboBox>

#include "GenericInput.h"

class RString;

struct PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorPolymorphic : public QWidget
{
  Q_OBJECT;

public:
  PropertyEditorPolymorphic(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
    Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);

  ~PropertyEditorPolymorphic();

  void SetSizeChangeCallback(Delegate<void> && size_change_cb);
  void HandleServerUpdate(const ReflectionChangeNotification & change);
  void HandleChildSizeChanged();
  void UpdateType();
  void UpdateTypeWidget();
  void UpdateChildPosition();

protected:
  virtual void resizeEvent(QResizeEvent * ev) override;

public slots:
  void typeChanged();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  std::string m_ChildPath;
  uint64_t m_BasePathHash;
  uint64_t m_BaseCallbackId;

  bool m_CreateCallback;

  uint64_t m_TypePathHash;
  uint64_t m_TypeCallbackId;

  Delegate<void> m_SizeChangedCallback;

  std::unique_ptr<QComboBox> m_Input;
  std::unique_ptr<QWidget> m_ChildWidget;
  bool m_LocalChange;
  bool m_WriteBack;
};

