
#include "PropertyEditorEnum.h"
#include "PropertyEditorWidget.h"
#include "DocumentEditorWidgetBase.h"


#include <StormRefl/StormReflJson.h>

PropertyEditorEnum::PropertyEditorEnum(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_PathHash(crc64(path)),
  m_LocalChange(false),
  m_WriteBack(false)
{
  m_Input = std::make_unique<QComboBox>(this);
  m_Input->show();

  QStringList potential_options;
  for (auto & enum_option : prop->m_Enum.m_EnumData->m_PossibleValues)
  {
    potential_options.append(enum_option.second.data());
  }

  potential_options.sort();
  m_Input->addItems(potential_options);

  connect(m_Input.get(), &QComboBox::currentTextChanged, this, &PropertyEditorEnum::valueChanged);

  UpdateValue();

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorEnum::HandleServerUpdate, this));
  }
  else
  {
    m_CallbackId = 0;
  }

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
}

PropertyEditorEnum::~PropertyEditorEnum()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
}

void PropertyEditorEnum::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  UpdateValue();
}

void PropertyEditorEnum::UpdateValue()
{
  m_WriteBack = true;

  auto ptr = m_PropertyPtr();
  if (ptr != nullptr)
  {
    auto value = m_Property->m_Enum.Get(m_PropertyPtr());
    m_Input->setCurrentText(value);
  }

  m_WriteBack = false;
}

void PropertyEditorEnum::UpdateChildPosition()
{
  auto input_height = std::max(m_Input->minimumHeight(), 20);

  m_Input->setGeometry(0, 0, width(), input_height);
  setMinimumHeight(input_height);
}

void PropertyEditorEnum::resizeEvent(QResizeEvent * ev)
{
  UpdateChildPosition();
}

void PropertyEditorEnum::valueChanged()
{
  if (m_WriteBack)
  {
    return;
  }

  auto current_text = m_Input->currentText().toStdString();
  for (auto & enum_option : m_Property->m_Enum.m_EnumData->m_PossibleValues)
  {
    if (enum_option.second == current_text)
    {
      m_LocalChange = true;
      m_Property->m_Enum.Set(m_PropertyPtr(), current_text.data());
      m_LocalChange = false;
      return;
    }
  }
}
