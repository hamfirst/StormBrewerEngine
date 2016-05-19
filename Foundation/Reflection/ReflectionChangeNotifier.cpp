
#include "Foundation\Common.h"
#include "Foundation\Reflection\ReflectionChangeNotifier.h"
#include "Foundation\Reflection\ReflectionJsonThin.h"
#include "Foundation\Reflection\TypeDatabase.h"
#include "Foundation\Document\Document.h"
#include "Foundation\Document\DocumentModification.h"
#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Document\DocumentPathElement.h"

thread_local void(*g_ChangeNotifier)(const DocumentModification & mod) = nullptr;

void BeginChangeNotification(void(*change_notifier)(const DocumentModification & mod))
{
  g_ChangeNotifier = change_notifier;
}

void EndChangeNotification()
{
  g_ChangeNotifier = nullptr;
}

DocumentPath CreateDocumentPath(const ReflectionParentInfo & parent_info)
{
  std::vector<DocumentPathElement> path;
  const ReflectionParentInfo * info = &parent_info;

  while (info)
  {
    if (info->m_ParentInfo == nullptr)
    {
      break;
    }

    if (info->m_ParentType == 0)
    {
      path.emplace_back(info->m_ParentIndex);
    }
    else if (info->m_ParentType == 0xFFFFFFFF)
    {
      if (info->m_ParentIndex == 0)
      {
        path.emplace_back("Obj");
      }
      else if (info->m_ParentIndex == 1)
      {
        path.emplace_back("TypeNameHash");
      }
      else
      {
        throw std::exception("invalid parent info");
      }
    }
    else
    {
      Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(info->m_ParentType);
      if (type_info)
      {
        path.emplace_back(type_info->m_GetFieldName(info->m_ParentIndex));
      }
      else
      {
        throw std::exception("invalid parent info");
      }
    }

    info = info->m_ParentInfo;
  }
  
  return path;
}

void NodifyDocumentModification(const DocumentModification & mod)
{
  g_ChangeNotifier(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, bool value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int8_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int16_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int32_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, int64_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint8_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint16_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint32_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, uint64_t value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, float value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, const char * value)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::string("\"") + Json::escape_string(value) + std::string("\""),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(const ReflectionParentInfo & parent_info, void * value, uint32_t type_name_hash)
{
  if (g_ChangeNotifier == nullptr) return;

  Optional<TypeInfo> type_info = g_TypeDatabase->GetTypeInfo(type_name_hash);
  if (type_info)
  {
    Json json;
    type_info->m_EncodeJson(value, &json);

    DocumentModification mod
    {
      CreateDocumentPath(parent_info),
      json.dump(),
      DocumentModificationType::kSet,
      0
    };

    NodifyDocumentModification(mod);
  }
  else
  {
    throw std::exception("invalid polymorphic type");
  }
}

void ReflectionNotifyClearArray(const ReflectionParentInfo & parent_info)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kClearArray,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyClearObject(const ReflectionParentInfo & parent_info)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kClearObject,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyAppendArray(const ReflectionParentInfo & parent_info, const std::string & data)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kAppendArray,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyCompress(const ReflectionParentInfo & parent_info)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kCompress,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyInsertArray(const ReflectionParentInfo & parent_info, std::size_t index, const std::string & data)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kInsertArray,
    index
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyInsertObject(const ReflectionParentInfo & parent_info, std::size_t index, const std::string & data)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kInsertObject,
    index
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyRemoveArray(const ReflectionParentInfo & parent_info, std::size_t index)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kRemoveArray,
    index
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyRemoveObject(const ReflectionParentInfo & parent_info, std::size_t index)
{
  if (g_ChangeNotifier == nullptr) return;

  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kRemoveObject,
    index
  };

  NodifyDocumentModification(mod);
}
