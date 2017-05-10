#pragma once


#include <QWidget>

#include <Foundation/Delegate/Delegate.h>

#include <StormData/StormDataPath.h>

#include "DocumentEditorWidgetBase.h"

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

template <template <typename> typename ListType, typename T>
GenericList * CreateGenericList(DocumentEditorWidgetBase * editor, ListType<T> & list, 
  std::unique_ptr<QWidget>(*adapter)(GenericList * list, T & elem, std::size_t index, void * user_data), void * adapter_user_ptr,
  void(*updater)(QWidget * widget, T & elem, void * user_data), void * updater_user_ptr,
  NotNullPtr<GenericListFrame> frame, Delegate<void *> data_ptr = {}, bool create_scroll_panel = true)
{
  GenericListInitDelegate init_del = [](void * ptr) -> std::vector<std::size_t>
  {
    ListType<T> * list = static_cast<ListType<T> *>(ptr);

    std::vector<std::size_t> indices;
    for (auto elem : (*list))
    {
      indices.push_back(elem.first);
    }

    return indices;
  };

  GenericListAppendDelegate append_del = [](void * ptr, void * obj) -> std::size_t
  {
    ListType<T> * list = static_cast<ListType<T> *>(ptr);

    T * elem = static_cast<T *>(obj);
    list->EmplaceBack(*elem);

    return (std::size_t)list->HighestIndex();
  };

  GenericListRemoveDelegate remove_del = [](void * ptr, std::size_t index)
  {
    ListType<T> * list = static_cast<ListType<T> *>(ptr);
    list->RemoveAt(index);
  };

  GenericListAdapterDelegate adapter_del = [=](GenericList * list_container, void * ptr, std::size_t index)
  {
    ListType<T> * list = static_cast<ListType<T> *>(ptr);
    if (list->HasAt(index) == false)
    {
      return std::unique_ptr<QWidget>();
    }

    return adapter(list_container, (*list)[index], index, adapter_user_ptr);
  };

  GenericListUpdateDelegate update_del = [=](QWidget * widget, void * ptr, std::size_t index)
  {
    ListType<T> * list = static_cast<ListType<T> *>(ptr);
    if (list->HasAt(index) == false)
    {
      return;
    }

    updater(widget, (*list)[index], updater_user_ptr);
  };

  if (data_ptr.IsValid() == false)
  {
    data_ptr = [&]() -> void * { return &list; };
  }

  auto widget = std::make_unique<GenericList>(editor, StormDataGetPath(list), std::move(data_ptr),
    std::move(init_del), std::move(append_del), std::move(remove_del), std::move(adapter_del), std::move(update_del), frame);

  GenericList * list_ptr = widget.get();

  widget->BindToFrame(frame);

  if (create_scroll_panel)
  {
    auto panel = std::make_unique<ScrollingPanel>();
    auto panel_ptr = panel.get();
    frame->SetChildWidget(std::move(panel));

    panel_ptr->SetChildWidget(std::move(widget));
    list_ptr->SetSizeChangeCallback([=] { panel_ptr->recalculate(); });
  }
  else
  {
    frame->SetChildWidget(std::move(widget));
  }

  return list_ptr;
}

