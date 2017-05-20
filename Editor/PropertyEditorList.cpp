
#include "PropertyEditorList.h"
#include "PropertyEditorWidget.h"

PropertyEditorList::PropertyEditorList(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, bool create_callback, 
  Delegate<void *> data_ptr, const std::string & path, czstr list_name, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_Path(path),
  m_PathHash(crc64(path)),
  m_CreateCallback(create_callback),
  m_Frame(std::make_unique<QGroupBox>(list_name ? list_name : "List", this)),
  m_AddButton(std::make_unique<QPushButton>(m_Frame.get()))
{
  SyncElements();

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorList::HandleServerChange, this));
  }
  else
  {
    m_CallbackId = 0;
  }

  connect(m_AddButton.get(), &QPushButton::pressed, this, &PropertyEditorList::handleAddButtonClicked);
  m_AddButton->setText("+");

  RespositionChildren();

  m_AddButton->show();
  m_Frame->show();
}

PropertyEditorList::~PropertyEditorList()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
}

void PropertyEditorList::SetSizeChangeCallback(Delegate<void> && size_change_cb)
{
  m_SizeChangedCallback = std::move(size_change_cb);
}

void PropertyEditorList::SyncElements()
{
  auto list_ptr = m_PropertyPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto indices = m_Property->m_List.GetElementIndices(list_ptr);
  for (auto & index : indices)
  {
    auto get_child_delegate = [parent_del = &m_PropertyPtr, index, prop = m_Property]()
    {
      return prop->m_List.GetElement(parent_del->Call(), index);
    };

    auto child_path = m_Path + "[" + std::to_string(index) + "]";

    ChildElement elem;
    elem.m_FrameLabel = std::make_unique<QGroupBox>(m_Frame.get());
    elem.m_FrameLabel->setTitle(QString("Element " + QString::number(index)));
    elem.m_FrameLabel->show();
    elem.m_RemoveButton = std::make_unique<QPushButton>(elem.m_FrameLabel.get());
    elem.m_RemoveButton->setText("-");
    elem.m_RemoveButton->show();
    elem.m_Widget = PropertyEditorCreate(m_Editor, m_Property->m_List.m_ListData, m_CreateCallback, 
      get_child_delegate, child_path, [=] { HandleChildSizeChanged(index); }, nullptr, elem.m_FrameLabel.get());
    elem.m_Widget->show();

    connect(elem.m_RemoveButton.get(), &QPushButton::pressed, this, &PropertyEditorList::handleRemoveButtonClicked);

    m_ChildElements.emplace(std::make_pair(index, std::move(elem)));
  }
}

void PropertyEditorList::HandleChildSizeChanged(std::size_t child_index)
{
  RespositionChildren();
  m_SizeChangedCallback();
}

void PropertyEditorList::RespositionChildren()
{
  m_Frame->setGeometry(0, 0, width() - 1, height() - 1);

  auto title_width = m_Frame->fontMetrics().width(m_Frame->title());
  m_AddButton->setGeometry(title_width + 20, 0, 20, 15);

  int y = 17;

  for (auto & elem : m_ChildElements)
  {
    auto frame = elem.second.m_FrameLabel.get();
    auto child_height = elem.second.m_Widget->minimumHeight();
    auto title_width = frame->fontMetrics().width(frame->title());

    elem.second.m_FrameLabel->setGeometry(3, y, width() - 6, elem.second.m_Widget->minimumHeight() + 19);
    elem.second.m_RemoveButton->setGeometry(title_width + 20, 0, 20, 15);
    elem.second.m_Widget->setGeometry(3, 17, elem.second.m_FrameLabel->width() - 6, child_height);
    y += child_height + 20;
  }

  y += 2;
  setMinimumHeight(y);
}

void PropertyEditorList::AppendElement()
{
  auto list_ptr = m_PropertyPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  m_Property->m_List.Append(list_ptr);
}

void PropertyEditorList::RemoveAtIndex(std::size_t index)
{
  auto list_ptr = m_PropertyPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  m_Property->m_List.Remove(list_ptr, index);
}

void PropertyEditorList::HandleServerChange(const ReflectionChangeNotification & notification)
{
  if (notification.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    ChildElement elem;

    auto index = notification.m_SubIndex;

    auto child_path = m_Path + "[" + std::to_string(index) + "]";

    auto get_child_delegate = [parent_del = &m_PropertyPtr, index, prop = m_Property]() -> void *
    {
      auto parent_val = parent_del->Call();
      if (parent_val == nullptr)
      {
        return nullptr;
      }

      return prop->m_List.GetElement(parent_val, index);
    };

    elem.m_FrameLabel = std::make_unique<QGroupBox>(m_Frame.get());
    elem.m_FrameLabel->setTitle(QString("Element " + QString::number(index)));
    elem.m_FrameLabel->show();
    elem.m_RemoveButton = std::make_unique<QPushButton>(elem.m_FrameLabel.get());
    elem.m_RemoveButton->setText("-");
    elem.m_RemoveButton->show();
    elem.m_Widget = PropertyEditorCreate(m_Editor, m_Property->m_List.m_ListData, m_CreateCallback, 
      get_child_delegate, child_path, [=] { HandleChildSizeChanged(index); }, nullptr, elem.m_FrameLabel.get());
    elem.m_Widget->show();

    m_ChildElements.emplace(std::make_pair(index, std::move(elem)));
    RespositionChildren();
    m_SizeChangedCallback();
  }
  else if (notification.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    m_ChildElements.erase(notification.m_SubIndex);
    RespositionChildren();
    m_SizeChangedCallback();
  }
  else if (notification.m_Type == ReflectionNotifyChangeType::kSet)
  {
    m_ChildElements.clear();
    SyncElements();

    RespositionChildren();
    m_SizeChangedCallback();
  }
}

void PropertyEditorList::resizeEvent(QResizeEvent * ev)
{
  RespositionChildren();
}

void PropertyEditorList::handleAddButtonClicked()
{
  AppendElement();
}

void PropertyEditorList::handleRemoveButtonClicked()
{
  auto sender = QObject::sender();
  for (auto & elem : m_ChildElements)
  {
    if (sender == elem.second.m_RemoveButton.get())
    {
      RemoveAtIndex(elem.first);
      return;
    }
  }
}
