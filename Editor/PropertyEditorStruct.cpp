
#include "PropertyEditorStruct.h"
#include "PropertyEditorWidget.h"


PropertyEditorStruct::PropertyEditorStruct(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr))
{
  int child_index = -1;
  for (auto & member : prop->m_Struct.m_StructData->m_Members)
  {
    child_index++;
    if (member.m_FieldData->m_Type == PropertyFieldType::kUnknown)
    {
      continue;
    }

    Delegate<void> size_change_cb = [=]()
    {
      HandleChildSizeChanged(child_index);
    };

    bool single_line = true;

    ChildElement child_element;

    if(member.m_FieldData->m_Type == PropertyFieldType::kPolymorphic ||
       member.m_FieldData->m_Type == PropertyFieldType::kList ||
       member.m_FieldData->m_Type == PropertyFieldType::kStruct)
    {
      single_line = false;
    }

    std::string name;
    auto name_src = member.m_Name.data();

    if (member.m_Name.size() > 2 && name_src[0] == 'm' && name_src[1] == '_')
    {
      name_src += 2;
    }

    bool first_char = true;
    while (*name_src != 0)
    {
      if (first_char == false && *name_src >= 'A' && *name_src <= 'Z')
      {
        name += ' ';
      }
      
      first_char = false;
      name += *name_src;
      name_src++;
    }

    auto get_child_ptr = [parent_del = &m_PropertyPtr, mem_ptr = &member]() -> void *
    {
      auto parent_val = parent_del->Call();
      if (parent_val == nullptr)
      {
        return nullptr;
      }

      return mem_ptr->GetMember(parent_val);
    };

    if (single_line)
    {
      child_element.m_NormalLabel = std::make_unique<QLabel>(this);
      child_element.m_NormalLabel->setText(name.data());
      child_element.m_NormalLabel->setAlignment(Qt::AlignLeft);
      child_element.m_NormalLabel->show();
      child_element.m_Widget = PropertyEditorCreate(editor, member.m_FieldData, create_callback, get_child_ptr,
        path + "." + member.m_Name, std::move(size_change_cb), member.m_Name.data(), this);
    }
    else if(member.m_FieldData->m_Type != PropertyFieldType::kList)
    {
      child_element.m_FrameLabel = std::make_unique<QGroupBox>(this);
      child_element.m_FrameLabel->setTitle(name.data());
      child_element.m_FrameLabel->show();
      child_element.m_Widget = PropertyEditorCreate(editor, member.m_FieldData, create_callback, get_child_ptr,
        path + "." + member.m_Name, std::move(size_change_cb), member.m_Name.data(), this);
    }
    else
    {
      child_element.m_Widget = PropertyEditorCreate(editor, member.m_FieldData, create_callback, get_child_ptr,
        path + "." + member.m_Name, std::move(size_change_cb), name.data(), this);
    }

    child_element.m_Widget->show();
    m_ChildElements.emplace_back(std::move(child_element));
  }

  RespositionChildren();
}

PropertyEditorStruct::~PropertyEditorStruct()
{
  m_ChildElements.clear();
}

void PropertyEditorStruct::resizeEvent(QResizeEvent * ev)
{
  RespositionChildren();
}

void PropertyEditorStruct::SetSizeChangeCallback(Delegate<void> && size_change_cb)
{
  m_SizeChangedCallback = std::move(size_change_cb);
}

void PropertyEditorStruct::HandleChildSizeChanged(int child_index)
{
  RespositionChildren();
  m_SizeChangedCallback();
}

void PropertyEditorStruct::RespositionChildren()
{
  int y = 5;
  for (auto & child : m_ChildElements)
  {
    if (child.m_NormalLabel)
    {
      int w = width();
      int split = (w / 3) - 1;
      int min_height = child.m_Widget->minimumHeight();

      int label_height = child.m_NormalLabel->fontMetrics().height();
      int label_offset = min_height / 2 - label_height / 2;

      child.m_NormalLabel->setGeometry(12, y + label_offset, split - 12, min_height);
      child.m_Widget->setGeometry(split + 1, y, w - split - 3, min_height);
      y += min_height;
    }
    else if(child.m_FrameLabel)
    {
      child.m_FrameLabel->setGeometry(3, y + 3, width(), child.m_Widget->minimumHeight() + 23);
      child.m_Widget->setGeometry(6, y + 20, width() - 12, child.m_Widget->minimumHeight());
      y += child.m_Widget->minimumHeight() + 23;
    }
    else
    {
      child.m_Widget->setGeometry(3, y + 3, width() - 3, child.m_Widget->minimumHeight());
      y += child.m_Widget->minimumHeight() + 6;
    }
  }

  setMinimumHeight(y);
}

