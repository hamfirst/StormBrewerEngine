
#include "Shared/Foundation/PropertyMeta/PropertyFieldMetaData.h"
#include "PropertyEditorHandle.h"
#include "Tools/Editor/AssetEditors/DocumentEditor/DocumentEditorWidgetBase.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Map/MapHandles.refl.h"

#include "StormRefl/StormReflJson.h"
#include "StormData/StormDataPath.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaData.h"

PropertyEditorHandle::PropertyEditorHandle(DocumentEditorWidgetBase * editor, PropertyField * prop, bool create_callback,
                                           Delegate<void *> && data_ptr, const std::string & path, QWidget * parent) :
        QWidget(parent),
        m_Editor(editor),
        m_Property(prop),
        m_PropertyPtr(std::move(data_ptr)),
        m_PathHash(crc64(path)),
        m_LocalChange(false)
{
  m_Input = std::make_unique<GenericComboBox>(this);
  m_Input->SetUpdateCallback(Delegate<void>(&PropertyEditorHandle::HandleCurrentIndexUpdate, this));
  m_Input->SetItemCallback([this]() -> const std::vector<std::string> & { return m_ItemNames; });

  if (create_callback)
  {
    m_CallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&PropertyEditorHandle::HandleServerUpdate, this));
  }
  else
  {
    m_CallbackId = 0;
  }

  auto map = editor->GetMap();
  m_ListPathHash = 0;
  m_ListCallbackId = 0;

  if(map)
  {
    switch (GetMapHandleForTypeNameHash(m_Property->m_Struct.m_StructData->m_TypeNameHash))
    {
      case MapHandleType::kEntity:
        m_ListPathHash = crc64(StormDataGetPath(map->m_EntityLayers));
        break;
      case MapHandleType::kEffectLayer:
        m_ListPathHash = crc64(StormDataGetPath(map->m_EffectLayers));
        break;
      case MapHandleType::kServerObject:
        m_ListPathHash = crc64(StormDataGetPath(map->m_ServerObjectLayers));
        break;
      case MapHandleType::kAnchor:
        m_ListPathHash = crc64(StormDataGetPath(map->m_Anchors));
        break;
      case MapHandleType::kPath:
        m_ListPathHash = crc64(StormDataGetPath(map->m_Paths));
        break;
      case MapHandleType::kVolume:
        m_ListPathHash = crc64(StormDataGetPath(map->m_Volumes));
        break;
      default:
        break;
    }

    if(m_ListPathHash == 0)
    {
      m_ListCallbackId = m_Editor->AddChangeCallback(m_ListPathHash, DocumentExternalChangeCallback(
              &PropertyEditorHandle::HandleListUpdate, this));
    }
  }

  setMinimumHeight(std::max(m_Input->minimumHeight(), 20));
  UpdateOptions();
}

PropertyEditorHandle::~PropertyEditorHandle()
{
  m_Editor->RemoveChangeCallback(m_PathHash, m_CallbackId);

  if(m_ListCallbackId != 0)
  {
    m_Editor->RemoveChangeCallback(m_ListPathHash, m_ListCallbackId);
  }
}

void PropertyEditorHandle::resizeEvent(QResizeEvent * ev)
{
  m_Input->setGeometry(0, 0, width() - 1, height());
}

void PropertyEditorHandle::HandleCurrentIndexUpdate()
{
  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    return;
  }

  m_LocalChange = true;
  auto handle = static_cast<MapHandleBase *>(property_ptr);
  handle->m_GUID = m_ItemGUIDS[m_Input->currentIndex()];
  m_LocalChange = false;
}

void PropertyEditorHandle::HandleServerUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  UpdateOptions();
}

void PropertyEditorHandle::HandleListUpdate(const ReflectionChangeNotification & change)
{
  if (m_LocalChange)
  {
    return;
  }

  UpdateOptions();
}

void PropertyEditorHandle::UpdateOptions()
{
  m_ItemNames.clear();
  m_ItemGUIDS.clear();

  m_ItemNames.push_back("None");
  m_ItemGUIDS.push_back(0);

  auto property_ptr = m_PropertyPtr();
  if (property_ptr == nullptr)
  {
    m_Input->UpdateItems(0);
    return;
  }

  auto handle = static_cast<MapHandleBase *>(property_ptr);

  auto map = m_Editor->GetMap();
  if(map == nullptr)
  {
    m_Input->UpdateItems(0);
    return;
  }

  switch(GetMapHandleForTypeNameHash(m_Property->m_Struct.m_StructData->m_TypeNameHash))
  {
    case MapHandleType::kEntity:
      for(auto layer : map->m_EntityLayers)
      {
        for(auto elem : layer.second.m_Entities)
        {
          m_ItemGUIDS.push_back(elem.second.m_GUID);
          m_ItemNames.push_back(elem.second.m_Name);
        }
      }
      break;
    case MapHandleType::kEffectLayer:
      for(auto elem : map->m_EffectLayers)
      {
        m_ItemGUIDS.push_back(elem.second.m_GUID);
        m_ItemNames.push_back(elem.second.m_Name);
      }
      break;
    case MapHandleType::kServerObject:
      for(auto layer : map->m_ServerObjectLayers)
      {
        for(auto elem : layer.second.m_Objects)
        {
          m_ItemGUIDS.push_back(elem.second.m_GUID);
          m_ItemNames.push_back(elem.second.m_Name);
        }
      }
      break;
    case MapHandleType::kAnchor:
      for(auto elem : map->m_Anchors)
      {
        m_ItemGUIDS.push_back(elem.second.m_GUID);
        m_ItemNames.push_back(elem.second.m_Name);
      }
      break;
    case MapHandleType::kPath:
      for(auto elem : map->m_Paths)
      {
        m_ItemGUIDS.push_back(elem.second.m_GUID);
        m_ItemNames.push_back(elem.second.m_Name);
      }
      break;
    case MapHandleType::kVolume:
      for(auto elem : map->m_Volumes)
      {
        m_ItemGUIDS.push_back(elem.second.m_GUID);
        m_ItemNames.push_back(elem.second.m_Name);
      }
      break;
    case MapHandleType::kNone:
      ASSERT(false, "Handle editor created for type that is not a handle");
      break;
  }

  int current_index = 0;
  for(int index = 0; index < static_cast<int>(m_ItemGUIDS.size()); ++index)
  {
    if(m_ItemGUIDS[index] == handle->m_GUID)
    {
      current_index = index;
      break;
    }
  }

  m_Input->UpdateItems(current_index);
}
