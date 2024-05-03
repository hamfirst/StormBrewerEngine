#pragma once

#include "Tools/Editor/UI/GenericWidgets/GenericListCreate.h"
#include "SimpleLabelListElement.h"


template <template <typename> class ListType, typename T>
GenericList * CreateSimpleLabelList(DocumentEditorWidgetBase * editor, ListType<T> & list, std::string(*adapter)(T &),
  NotNullPtr<GenericListFrame> frame, Delegate<void *> && data_ptr = {})
{
  auto simple_list_adapter = [](GenericList * list, T & elem, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
  {
    auto list_elem = std::make_unique<SimpleLabelListElement>();
    list_elem->SetClickedCallback(Delegate<void>([=] { list->SetSelection(index); }));
    return list_elem;
  };

  typedef std::string(*SimpleStringAdapterFunc)(T &);
  auto simple_list_updater = [](QWidget * widget, T & elem, void * user_data)
  {
    auto adapter = reinterpret_cast<SimpleStringAdapterFunc>(user_data);
    auto list_elem = static_cast<SimpleLabelListElement *>(widget);

    list_elem->SetText(adapter(elem).data());
  };

  auto simple_list_select_element = [](QWidget * widget, bool selected)
  {
    auto list_elem = static_cast<SimpleLabelListElement *>(widget);
    list_elem->SetSelected(selected);
  };

  if (data_ptr.IsValid() == false)
  {
    data_ptr = [&]() -> void * { return &list; };
  }

  auto widget = CreateGenericList<ListType, T>(editor, list, simple_list_adapter, nullptr, simple_list_updater, 
                                               reinterpret_cast<void *>(adapter), frame, std::move(data_ptr));
                                               
  widget->SetSelectElementCallback(simple_list_select_element);
  return widget;
}


