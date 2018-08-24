#pragma once

#include <QWidget>

#include <Foundation/Delegate/Delegate.h>

#include <StormData/StormDataPath.h>

#include "DocumentEditorWidgetBase.h"
#include "ScrollingPanel.h"

class GenericList;
class GenericFrame;
class GenericListFrame;

using GenericListInitDelegate = Delegate<std::vector<std::size_t>, void *>;
using GenericListAppendDelegate = Delegate<std::size_t, void *, void *>;
using GenericListRemoveDelegate = Delegate<void, void *, std::size_t>;
using GenericListAdapterDelegate = Delegate<std::unique_ptr<QWidget>, GenericList *, void *, std::size_t>;
using GenericListUpdateDelegate = Delegate<void, QWidget *, void *, std::size_t>;
using GenericListSetSelectionDelegate = Delegate<void, QWidget *, bool>;
using GenericListSelectionDelegate = Delegate<void, int>;
using GenericListSizeChangeDelegate = Delegate<void>;
using GenericListCountChangeDelegate = Delegate<void>;

class GenericList : public QWidget
{
  Q_OBJECT
public:
  GenericList(
    DocumentEditorWidgetBase * editor,
    const std::string & path,
    Delegate<void *> && list_ptr,
    GenericListInitDelegate && init_delegate,
    GenericListAppendDelegate && append_delegate,
    GenericListRemoveDelegate && remove_delegate,
    GenericListAdapterDelegate && adapter_delegate,
    GenericListUpdateDelegate && update_delegate,
    QWidget * parent = nullptr);

  ~GenericList();

  void SetSelectElementCallback(GenericListSetSelectionDelegate && callback);
  void SetSelectionCallback(GenericListSelectionDelegate && callback);
  void SetSizeChangeCallback(GenericListSizeChangeDelegate && size_change_cb);
  void SetCountChangeCallback(GenericListCountChangeDelegate && count_change_cb);
  void SetAllowSelection(bool allow);

  void AppendElement(void * elem);
  void RemoveElement(std::size_t index);

  void SetSelection(int index);
  int GetSelection() const;

  void BindToFrame(GenericListFrame * frame);
  void ChildSizeChanged(int index);

  void UpdateElement(int index);
  std::size_t GetNumElements() const;

protected:

  void HandleParentUpdate(const ReflectionChangeNotification & change);
  void HandleDirectUpdate(const ReflectionChangeNotification & change);

  void SyncNewElement(std::size_t index);
  void DesyncElement(std::size_t index);
  void ResyncAllElements();
  void RepositionChildren();

protected:

  void resizeEvent(QResizeEvent * ev) override;

private:
  DocumentEditorWidgetBase * m_Editor;
  std::string m_BasePath;

  Delegate<void *> m_ListPtr;
  int m_SelectedIndex;
  bool m_AllowSelection;

  uint64_t m_ChangeCallbackId;
  uint64_t m_ParentCallbackId;

  GenericListInitDelegate m_InitDelegate;
  GenericListAppendDelegate m_AppendDelegate;
  GenericListRemoveDelegate m_RemoveDelegate;
  GenericListAdapterDelegate m_AdapterDelegate;
  GenericListUpdateDelegate m_UpdateDelegate;
  GenericListSetSelectionDelegate m_SelectElementDelegate;
  GenericListSelectionDelegate m_SelectionDelegate;
  GenericListSizeChangeDelegate m_SizeChangedDelegate;
  GenericListCountChangeDelegate m_CountChangeDelegate;

  struct ElementData
  {
    std::unique_ptr<QWidget> m_Widget;
    uint64_t m_CallbackId;
  };

  std::map<std::size_t, ElementData> m_Elements;
};
