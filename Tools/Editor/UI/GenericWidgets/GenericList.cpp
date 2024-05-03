
#include "GenericList.h"
#include "GenericListFrame.h"

#include <QPainter>
#include <QPushButton>

GenericList::GenericList(
  DocumentEditorWidgetBase * editor,
  const std::string & path,
  Delegate<void *> && list_ptr,
  GenericListInitDelegate && init_delegate,
  GenericListAppendDelegate && append_delegate,
  GenericListRemoveDelegate && remove_delegate,
  GenericListAdapterDelegate && adapter_delegate,
  GenericListUpdateDelegate && update_delegate,
  QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_BasePath(path),
  m_ListPtr(std::move(list_ptr)),
  m_SelectedIndex(-1),
  m_AllowSelection(true),
  m_InitDelegate(std::move(init_delegate)),
  m_AppendDelegate(std::move(append_delegate)),
  m_RemoveDelegate(std::move(remove_delegate)),
  m_AdapterDelegate(std::move(adapter_delegate)),
  m_UpdateDelegate(std::move(update_delegate))
{
  if (m_Editor)
  {
    m_ChangeCallbackId = m_Editor->AddChangeCallback(crc64(m_BasePath), DocumentExternalChangeCallback(&GenericList::HandleDirectUpdate, this));
    m_ParentCallbackId = m_Editor->AddParentChangeCallback(m_BasePath.data(), DocumentExternalChangeCallback(&GenericList::HandleParentUpdate, this));
  }

  auto indices = m_InitDelegate(m_ListPtr());
  for (auto index : indices)
  {
    SyncNewElement(index);
  }

  if (m_Elements.size() > 0)
  {
    SetSelection(static_cast<int>(m_Elements.begin()->first));
  }

  RepositionChildren();
}

GenericList::~GenericList()
{
  if (m_Editor)
  {
    m_Editor->RemoveChangeCallback(crc64(m_BasePath), m_ChangeCallbackId);
    m_Editor->RemoveParentChangeCallback(m_ParentCallbackId);

    for (auto & elem : m_Elements)
    {
      m_Editor->RemoveChildChangeCallback(elem.second.m_CallbackId);
    }
  }
}

void GenericList::SetSelectElementCallback(GenericListSetSelectionDelegate && callback)
{
  m_SelectElementDelegate = std::move(callback);

  auto itr = m_Elements.find(m_SelectedIndex);
  if (itr != m_Elements.end())
  {
    m_SelectElementDelegate(itr->second.m_Widget.get(), true);
  }
}

void GenericList::SetSelectionCallback(GenericListSelectionDelegate && callback)
{
  m_SelectionDelegate = std::move(callback);
  m_SelectionDelegate(m_SelectedIndex);
}

void GenericList::SetSizeChangeCallback(GenericListSizeChangeDelegate && size_change_cb)
{
  m_SizeChangedDelegate = std::move(size_change_cb);
}

void GenericList::SetCountChangeCallback(GenericListCountChangeDelegate && count_change_cb)
{
  m_CountChangeDelegate = std::move(count_change_cb);
}

void GenericList::SetAllowSelection(bool allow)
{
  m_AllowSelection = allow;
  if (m_AllowSelection)
  {
    if (m_SelectedIndex == -1 && m_Elements.size() > 0)
    {
      SetSelection(static_cast<int>(m_Elements.begin()->first));
    }
  }
  else
  {
    SetSelection(-1);
  }
}

void GenericList::AppendElement(void * elem)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto index = m_AppendDelegate(list_ptr, elem);

  if (m_Editor == nullptr)
  {
    SyncNewElement(index);

    RepositionChildren();
    m_SizeChangedDelegate();

    SetSelection(static_cast<int>(index));
  }
}

void GenericList::RemoveElement(std::size_t index)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto itr = m_Elements.find(index);
  if (itr == m_Elements.end())
  {
    return;
  }

  m_RemoveDelegate(list_ptr, index);

  if (m_Editor == nullptr)
  {

    DesyncElement(index);

    RepositionChildren();
    m_SizeChangedDelegate();
  }
}

void GenericList::SyncNewElement(std::size_t index)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto widget = m_AdapterDelegate(this, list_ptr, index);
  m_UpdateDelegate(widget.get(), list_ptr, index);

  ElementData new_elem;
  new_elem.m_Widget = std::move(widget);
  new_elem.m_Widget->setParent(this);
  new_elem.m_Widget->show();

  if (m_Editor)
  {
    std::string element_path = m_BasePath + '[' + std::to_string(index) + ']';
    new_elem.m_CallbackId = m_Editor->AddChildChangeCallback(element_path.data(),
      DocumentExternalChangeCallback([=](const ReflectionChangeNotification &) { UpdateElement(static_cast<int>(index)); }));
  }
  else
  {
    new_elem.m_CallbackId = 0;
  }

  m_Elements.emplace(std::make_pair(index, std::move(new_elem)));
  m_CountChangeDelegate();
}

void GenericList::DesyncElement(std::size_t index)
{
  auto itr = m_Elements.find(index);
  if (itr != m_Elements.end())
  {
    if (m_SelectedIndex == (int)index)
    {
      m_SelectedIndex = -1;
      if (m_Elements.size() <= 1)
      {
        SetSelection(-1);
      }
      else
      {
        auto next_itr = itr;
        ++next_itr;

        if (next_itr == m_Elements.end())
        {
          auto prev_itr = itr;
          --prev_itr;

          SetSelection((int)prev_itr->first);
        }
        else
        {
          SetSelection((int)next_itr->first);
        }
      }
    }

    if (m_Editor)
    {
      m_Editor->RemoveChildChangeCallback(itr->second.m_CallbackId);
    }

    m_Elements.erase(itr);
    m_CountChangeDelegate();
  }
}

void GenericList::ResyncAllElements()
{
  if (m_Editor)
  {
    for (auto & elem : m_Elements)
    {
      m_Editor->RemoveChildChangeCallback(elem.second.m_CallbackId);
    }
  }

  m_Elements.clear();

  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto indices = m_InitDelegate(list_ptr);
  for (auto index : indices)
  {
    SyncNewElement(index);
  }

  if (m_Elements.size() > 0)
  {
    m_SelectedIndex = -1;
    SetSelection(static_cast<int>(m_Elements.begin()->first));
  }
  else
  {
    m_SelectedIndex = -1;
    SetSelection(-1);
  }

  m_CountChangeDelegate();

  RepositionChildren();
  m_SizeChangedDelegate();
}

void GenericList::RepositionChildren()
{
  for (auto & elem : m_Elements)
  {
    elem.second.m_Widget->resize(width() - 1, elem.second.m_Widget->height());
  }

  int y = 0;
  for (auto & elem : m_Elements)
  {
    auto min_height = elem.second.m_Widget->minimumHeight();
    elem.second.m_Widget->setGeometry(0, y, width() - 1, min_height);
    y += min_height;
  }

  setMinimumHeight(y + 15);
}

void GenericList::resizeEvent(QResizeEvent * ev)
{
  RepositionChildren();
}

void GenericList::SetSelection(int index)
{
  if (m_AllowSelection == false)
  {
    return;
  }

  if (m_SelectedIndex != -1)
  {
    auto itr = m_Elements.find(m_SelectedIndex);
    if (itr != m_Elements.end())
    {
      m_SelectElementDelegate(itr->second.m_Widget.get(), false);
    }
  }

  m_SelectedIndex = index;
  if (m_SelectedIndex != -1)
  {
    auto itr = m_Elements.find(m_SelectedIndex);
    if (itr != m_Elements.end())
    {
      m_SelectElementDelegate(itr->second.m_Widget.get(), true);
    }
  }

  m_SelectionDelegate(m_SelectedIndex);
}

int GenericList::GetSelection() const
{
  return m_SelectedIndex;
}

void GenericList::BindToFrame(GenericListFrame * frame)
{
  frame->SetRemoveDelegate([=] {
    if (GetSelection() != -1)
    {
      RemoveElement((std::size_t)GetSelection());
    }
  });

  SetSizeChangeCallback([=] {
    frame->SetRemoveButtonEnabled(GetNumElements() > 0);
  });

  frame->SetRemoveButtonEnabled(GetNumElements() > 0);
}

void GenericList::ChildSizeChanged(int index)
{
  RepositionChildren();
  m_SizeChangedDelegate();
}

void GenericList::UpdateElement(int index)
{
  auto itr = m_Elements.find((std::size_t)index);
  if (itr == m_Elements.end())
  {
    return;
  }

  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  m_UpdateDelegate(itr->second.m_Widget.get(), list_ptr, (std::size_t)index);
}

std::size_t GenericList::GetNumElements() const
{
  return m_Elements.size();
}

void GenericList::HandleParentUpdate(const ReflectionChangeNotification & change)
{
  ResyncAllElements();
}

void GenericList::HandleDirectUpdate(const ReflectionChangeNotification & change)
{
  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    SyncNewElement(change.m_SubIndex);

    RepositionChildren();
    m_SizeChangedDelegate();

    SetSelection(change.m_SubIndex);
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    DesyncElement(change.m_SubIndex);

    RepositionChildren();
    m_SizeChangedDelegate();
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kSet)
  {
    ResyncAllElements();
  }
}
