
#include "PropertyEditorPolymorphic.h"
#include "PropertyEditorWidget.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"


#include "StormTech/StormRefl/StormReflJson.h"

PropertyEditorPolymorphic::PropertyEditorPolymorphic(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_ChildPath(path + ".D"),
  m_BasePathHash(crc64(path)),
  m_CreateCallback(create_callback),
  m_TypePathHash(crc64(path + ".T")),
  m_LocalChange(false),
  m_WriteBack(false)
{
  m_Input = std::make_unique<QComboBox>(this);
  m_Input->setEditable(true);
  m_Input->show();

  QStringList potential_options;
  for (auto & poly_option : prop->m_Poly.m_PolyData->m_PossibleValues)
  {
    potential_options.append(poly_option.m_Name.data());
  }

  potential_options.append("None");

  potential_options.sort();
  m_Input->addItems(potential_options);

  connect(m_Input.get(), &QComboBox::currentTextChanged, this, &PropertyEditorPolymorphic::typeChanged);

  UpdateType();
  UpdateTypeWidget();

  if (create_callback)
  {
    m_BaseCallbackId = m_Editor->AddChangeCallback(m_BasePathHash, DocumentExternalChangeCallback(&PropertyEditorPolymorphic::HandleServerUpdate, this));
    m_TypeCallbackId = m_Editor->AddChangeCallback(m_TypePathHash, DocumentExternalChangeCallback(&PropertyEditorPolymorphic::HandleServerUpdate, this));
  }
  else
  {
    m_BaseCallbackId = 0;
    m_TypeCallbackId = 0;
  }
}

PropertyEditorPolymorphic::~PropertyEditorPolymorphic()
{
  m_Editor->RemoveChangeCallback(m_BasePathHash, m_BaseCallbackId);
  m_Editor->RemoveChangeCallback(m_TypePathHash, m_TypeCallbackId);
}

void PropertyEditorPolymorphic::SetSizeChangeCallback(Delegate<void> && size_change_cb)
{
  m_SizeChangedCallback = std::move(size_change_cb);
}

void PropertyEditorPolymorphic::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  UpdateType();
  UpdateTypeWidget();
}

void PropertyEditorPolymorphic::HandleChildSizeChanged()
{
  UpdateChildPosition();
  m_SizeChangedCallback();
}

void PropertyEditorPolymorphic::UpdateType()
{
  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    return;
  }

  m_WriteBack = true;

  bool found_type = false;

  auto type_hash = m_Property->m_Poly.GetType(property_ptr);
  for (auto & poly_option : m_Property->m_Poly.m_PolyData->m_PossibleValues)
  {
    if (poly_option.m_NameHash == type_hash)
    {
      m_Input->setCurrentText(poly_option.m_Name.data());
      found_type = true;
      break;
    }
  }

  if (found_type == false)
  {
    m_Input->setCurrentText("None");
  }

  m_WriteBack = false;
}

void PropertyEditorPolymorphic::UpdateTypeWidget()
{
  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    return;
  }

  auto type_hash = m_Property->m_Poly.GetType(property_ptr);
  if (type_hash == 0)
  {
    m_ChildWidget.reset();

    UpdateChildPosition();
    m_SizeChangedCallback();
    return;
  }

  for (auto & poly_option : m_Property->m_Poly.m_PolyData->m_PossibleValues)
  {
    if (poly_option.m_NameHash == type_hash)
    {
      auto get_child_ptr = [parent_del = &m_PropertyPtr, prop = m_Property]() -> void *
      {
        auto parent_val = parent_del->Call();
        if (parent_val == nullptr)
        {
          return nullptr;
        }

        return prop->m_Poly.GetValue(parent_val);
      };

      m_ChildWidget = PropertyEditorCreate(m_Editor, poly_option.m_FieldData, m_CreateCallback, get_child_ptr, m_ChildPath,
        Delegate<void>(&PropertyEditorPolymorphic::HandleChildSizeChanged, this), nullptr, this);

      UpdateChildPosition();

      m_ChildWidget->show();
      m_SizeChangedCallback();
      break;
    }
  }
}

void PropertyEditorPolymorphic::UpdateChildPosition()
{
  int input_height = m_Input->sizeHint().height();
  m_Input->setGeometry(0, 0, width(), input_height);

  if (m_ChildWidget)
  {
    auto child_height = m_ChildWidget->minimumHeight();
    m_ChildWidget->setGeometry(0, input_height, width(), child_height);
    setMinimumHeight(input_height + child_height);
  }
  else
  {
    setMinimumHeight(input_height);
  }
}

void PropertyEditorPolymorphic::resizeEvent(QResizeEvent * ev)
{
  UpdateChildPosition();
}

void PropertyEditorPolymorphic::typeChanged()
{
  if (m_WriteBack)
  {
    return;
  }

  if (m_Input->currentText() == "None")
  {
    m_LocalChange = true;
    auto property_ptr = m_PropertyPtr();
    if (property_ptr != nullptr)
    {
      m_Property->m_Poly.SetType(m_PropertyPtr(), 0);
    }
    m_LocalChange = false;

    UpdateTypeWidget();
    return;
  }

  auto hash = crc32(m_Input->currentText().toStdString());
  for (auto & poly_option : m_Property->m_Poly.m_PolyData->m_PossibleValues)
  {
    if (poly_option.m_NameHash == hash)
    {
      m_LocalChange = true;
      auto property_ptr = m_PropertyPtr();
      if (property_ptr != nullptr)
      {
        m_Property->m_Poly.SetType(m_PropertyPtr(), hash);
      }
      m_LocalChange = false;

      UpdateTypeWidget();
      return;
    }
  }
}
