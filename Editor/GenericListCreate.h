#pragma once

#include "GenericList.h"
#include "GenericListFrame.h"

template <template <typename> class ListType, typename T>
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



