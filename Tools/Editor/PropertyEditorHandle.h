#pragma once

#include <QWidget>
#include <QComboBox>

#include "Editor/GenericComboBox.h"

struct PropertyField;
class DocumentEditorWidgetBase;

class PropertyEditorHandle : public QWidget
{
Q_OBJECT;

public:
  PropertyEditorHandle(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
                       Delegate<void *> && data_ptr, const std::string & path, QWidget * parent = nullptr);

  ~PropertyEditorHandle();

  virtual void resizeEvent(QResizeEvent * ev) override;

  void HandleServerUpdate(const ReflectionChangeNotification & change);
  void HandleListUpdate(const ReflectionChangeNotification & change);
  void HandleCurrentIndexUpdate();
  void UpdateOptions();

signals:

  void changed();

private:
  DocumentEditorWidgetBase * m_Editor;

  PropertyField * m_Property;
  Delegate<void *> m_PropertyPtr;

  uint64_t m_PathHash;
  uint64_t m_CallbackId;

  uint64_t m_ListPathHash;
  uint64_t m_ListCallbackId;

  std::unique_ptr<GenericComboBox> m_Input;
  std::vector<std::string> m_ItemNames;
  std::vector<uint32_t> m_ItemGUIDS;
  bool m_LocalChange;
};

