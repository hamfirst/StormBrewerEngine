
#include <QLabel>

#include "PropertyEditorWidget.h"
#include "PropertyEditorBool.h"
#include "PropertyEditorString.h"
#include "PropertyEditorFile.h"
#include "PropertyEditorNumber.h"
#include "PropertyEditorStruct.h"
#include "PropertyEditorList.h"
#include "PropertyEditorPolymorphic.h"

std::unique_ptr<QWidget> PropertyEditorCreate(NotNullPtr<DocumentEditorWidgetBase> editor, 
  NotNullPtr<PropertyField> prop, Delegate<void *> && data_ptr, const std::string & path, Delegate<void> && size_change_cb, czstr name, QWidget * parent)
{
  switch (prop->m_Type)
  {
  case PropertyFieldType::kBool:
    return std::make_unique<PropertyEditorBool>(editor, prop, std::move(data_ptr), path, parent);
  case PropertyFieldType::kString:
    return std::make_unique<PropertyEditorString>(editor, prop, std::move(data_ptr), path, parent);
  case PropertyFieldType::kFile:
    return std::make_unique<PropertyEditorFile>(editor, prop, std::move(data_ptr), path, parent);
  case PropertyFieldType::kSignedNumber:
  case PropertyFieldType::kUnsignedNumber:
  case PropertyFieldType::kFloatNumber:
    return std::make_unique<PropertyEditorNumber>(editor, prop, std::move(data_ptr), path, parent);
  case PropertyFieldType::kList:
    {
      auto widget = std::make_unique<PropertyEditorList>(editor, prop, std::move(data_ptr), path, name, parent);
      widget->SetSizeChangeCallback(std::move(size_change_cb));
      return std::move(widget);
    }
  case PropertyFieldType::kPolymorphic:
    {
      auto widget = std::make_unique<PropertyEditorPolymorphic>(editor, prop, std::move(data_ptr), path, parent);
      widget->SetSizeChangeCallback(std::move(size_change_cb));
      return std::move(widget);
    }
  case PropertyFieldType::kStruct:
    {
      auto widget = std::make_unique<PropertyEditorStruct>(editor, prop, std::move(data_ptr), path, parent);
      widget->SetSizeChangeCallback(std::move(size_change_cb));
      return std::move(widget);
    }
  default:
    {
      std::unique_ptr<QWidget> place_holder = std::make_unique<QLabel>("Not implemented", parent);
      place_holder->setMinimumHeight(22);
      return place_holder;
    }
  }
}
