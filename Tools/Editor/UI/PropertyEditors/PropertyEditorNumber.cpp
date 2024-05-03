
#include "PropertyEditorNumber.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

#include "StormTech/StormRefl/StormReflJson.h"

PropertyEditorNumber::PropertyEditorNumber(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback, 
  Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Property(prop),
  m_PropertyPtr(std::move(data_ptr)),
  m_PathHash(crc64(path)),
  m_LocalChange(false)
{
  m_Input = std::make_unique<GenericInput>(this);
  m_Input->SetUpdateCallback(Delegate<void>(&PropertyEditorNumber::HandleTextUpdate, this));

  UpdateText();

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorNumber::HandleServerUpdate, this));
    m_ParentCallbackId = m_Editor->AddParentChangeCallback(path.data(), DocumentExternalChangeCallback(&PropertyEditorNumber::HandleServerUpdate, this));
  }
  else
  {
    m_CallbackId = 0;
    m_ParentCallbackId = 0;
  }

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
}

PropertyEditorNumber::~PropertyEditorNumber()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);
  m_Editor->RemoveParentChangeCallback(m_ParentCallbackId);
}

void PropertyEditorNumber::resizeEvent(QResizeEvent * ev)
{
  m_Input->setGeometry(0, 0, width() - 1, height());
}

void PropertyEditorNumber::HandleTextUpdate()
{
  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    return;
  }

  m_LocalChange = true;
  switch (m_Property->m_Type)
  {
  case PropertyFieldType::kSignedNumber:
    {
      int64_t val;
      if (StormReflParseJson(val, m_Input->text().toStdString().data()))
      {
        auto original_val = val;

        if (val < m_Property->m_SignedNumber.m_Min)
        {
          val = m_Property->m_SignedNumber.m_Min;
        }
        else if (val > m_Property->m_SignedNumber.m_Max)
        {
          val = m_Property->m_SignedNumber.m_Max;
        }

        if (val != original_val)
        {
          m_Input->RemoteUpdate(std::to_string(val).data());
        }

        m_Property->m_SignedNumber.Set(property_ptr, val);
      }
    }
    break;
  case PropertyFieldType::kUnsignedNumber:
    {
      uint64_t val;
      if (StormReflParseJson(val, m_Input->text().toStdString().data()))
      {
        auto original_val = val;

        if (val < m_Property->m_UnsignedNumber.m_Min)
        {
          val = m_Property->m_UnsignedNumber.m_Min;
        }
        else if (val > m_Property->m_UnsignedNumber.m_Max)
        {
          val = m_Property->m_UnsignedNumber.m_Max;
        }

        if (val != original_val)
        {
          m_Input->RemoteUpdate(std::to_string(val).data());
        }

        m_Property->m_UnsignedNumber.Set(property_ptr, val);
      }
    }
    break;
  case PropertyFieldType::kFloatNumber:
    {
      float val;
      auto str = m_Input->text().toStdString();

      if (StormReflParseJson(val, str.data()))
      {
        auto original_val = val;

        if (val < m_Property->m_FloatNumber.m_Min)
        {
          val = m_Property->m_FloatNumber.m_Min;
        }
        else if (val > m_Property->m_FloatNumber.m_Max)
        {
          val = m_Property->m_FloatNumber.m_Max;
        }

        if (val != original_val)
        {
          m_Input->RemoteUpdate(std::to_string(val).data());
        }

        m_Property->m_FloatNumber.Set(property_ptr, val);
      }
    }
    break;
  case PropertyFieldType::kFloatNumberDeterministic:
    {
      float val;
      auto str = m_Input->text().toStdString();

      if (StormReflParseJson(val, str.data()))
      {
        auto original_val = val;

        if (val < m_Property->m_FloatNumber.m_Min)
        {
          val = m_Property->m_FloatNumber.m_Min;
        }
        else if (val > m_Property->m_FloatNumber.m_Max)
        {
          val = m_Property->m_FloatNumber.m_Max;
        }

        if (val != original_val)
        {
          m_Input->RemoteUpdate(std::to_string(val).data());
        }

        m_Property->m_FloatNumberDeterministic.Set(property_ptr, std::to_string(val).data());
      }
    }
    break;
  }

  m_LocalChange = false;
}

void PropertyEditorNumber::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  UpdateText();
}

void PropertyEditorNumber::UpdateText()
{
  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    return;
  }

  switch (m_Property->m_Type)
  {
  case PropertyFieldType::kSignedNumber:
    {
      auto val = m_Property->m_SignedNumber.Get(property_ptr);
      m_Input->RemoteUpdate(std::to_string(val).data());
    }
    break;
  case PropertyFieldType::kUnsignedNumber:
    {
      auto val = m_Property->m_UnsignedNumber.Get(property_ptr);
      m_Input->RemoteUpdate(std::to_string(val).data());
    }
    break;
  case PropertyFieldType::kFloatNumber:
    {
      auto val = m_Property->m_FloatNumber.Get(property_ptr);
      m_Input->RemoteUpdate(std::to_string(val).data());
    }
    break;
  case PropertyFieldType::kFloatNumberDeterministic:
    {
      auto val = m_Property->m_FloatNumberDeterministic.Get(property_ptr);
      m_Input->RemoteUpdate(val);
    }
    break;
  }
}
