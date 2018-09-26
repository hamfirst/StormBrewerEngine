
#include <QLabel>
#include <Foundation/PropertyMeta/PropertyFieldMetaData.h>

#include "Runtime/Map/MapHandles.refl.meta.h"

#include "PropertyEditorWidget.h"
#include "PropertyEditorBool.h"
#include "PropertyEditorString.h"
#include "PropertyEditorFile.h"
#include "PropertyEditorEnum.h"
#include "PropertyEditorNumber.h"
#include "PropertyEditorStruct.h"
#include "PropertyEditorList.h"
#include "PropertyEditorPolymorphic.h"
#include "PropertyEditorHandle.h"

std::unique_ptr<QWidget> PropertyEditorCreate(NotNullPtr<DocumentEditorWidgetBase> editor, NotNullPtr<PropertyField> prop, bool create_callback,
  Delegate<void *> && data_ptr, const std::string & path, Delegate<void> && size_change_cb, czstr name, QWidget * parent)
{
  switch (prop->m_Type)
  {
  case PropertyFieldType::kBool:
    return std::make_unique<PropertyEditorBool>(editor, prop, create_callback, std::move(data_ptr), path, parent);
  case PropertyFieldType::kString:
    return std::make_unique<PropertyEditorString>(editor, prop, create_callback, std::move(data_ptr), path, parent);
  case PropertyFieldType::kFile:
    return std::make_unique<PropertyEditorFile>(editor, prop, create_callback, std::move(data_ptr), path, parent);
  case PropertyFieldType::kEnum:
    return std::make_unique<PropertyEditorEnum>(editor, prop, create_callback, std::move(data_ptr), path, parent);
  case PropertyFieldType::kSignedNumber:
  case PropertyFieldType::kUnsignedNumber:
  case PropertyFieldType::kFloatNumber:
  case PropertyFieldType::kFloatNumberDeterministic:
    return std::make_unique<PropertyEditorNumber>(editor, prop, create_callback, std::move(data_ptr), path, parent);
  case PropertyFieldType::kList:
    {
      auto widget = std::make_unique<PropertyEditorList>(editor, prop, create_callback, std::move(data_ptr), path, name, parent);
      widget->SetSizeChangeCallback(std::move(size_change_cb));
      return std::move(widget);
    }
  case PropertyFieldType::kPolymorphic:
    {
      auto widget = std::make_unique<PropertyEditorPolymorphic>(editor, prop, create_callback, std::move(data_ptr), path, parent);
      widget->SetSizeChangeCallback(std::move(size_change_cb));
      return std::move(widget);
    }
  case PropertyFieldType::kStruct:
    {
      auto handle_type = GetMapHandleForTypeNameHash(prop->m_Struct.m_StructData->m_TypeNameHash);

      if(handle_type != MapHandleType::kNone)
      {
        auto widget = std::make_unique<PropertyEditorHandle>(editor, prop, create_callback, std::move(data_ptr), path, parent);
        return widget;
      }
      else
      {
        auto widget = std::make_unique<PropertyEditorStruct>(editor, prop, create_callback, std::move(data_ptr), path, parent);
        widget->SetSizeChangeCallback(std::move(size_change_cb));
        return std::move(widget);
      }
    }
  default:
    {
      std::unique_ptr<QWidget> place_holder = std::make_unique<QLabel>("Not implemented", parent);
      place_holder->setMinimumHeight(22);
      return place_holder;
    }
  }
}
