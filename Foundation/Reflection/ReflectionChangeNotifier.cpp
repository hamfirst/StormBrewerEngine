
#include "Foundation\Common.h"
#include "Foundation\Reflection\ReflectionChangeNotifier.h"
#include "Foundation\Reflection\ReflectionJsonThin.h"
#include "Foundation\Reflection\TypeDatabase.h"
#include "Foundation\Document\Document.h"
#include "Foundation\Document\DocumentModification.h"
#include "Foundation\Document\DocumentPath.h"
#include "Foundation\Document\DocumentPathElement.h"

int g_DisableChangeNotification = 0;

void EnableChangeNotification()
{
  if (g_DisableChangeNotification > 0)
  {
    g_DisableChangeNotification--;
  }
}

void DisableChangeNotification()
{
  g_DisableChangeNotification++;
}

DocumentPath CreateDocumentPath(ReflectionParentInfo & parent_info)
{
  std::vector<DocumentPathElement> path;
  ReflectionParentInfo * info = &parent_info;

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
        throw std::runtime_error("invalid parent info");
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
        throw std::runtime_error("invalid parent info");
      }
    }

    info = info->m_ParentInfo;
  }
  
  return path;
}


void SetModifiedBits(ReflectionParentInfo & parent_info)
{
  if (parent_info.m_Modified != 1)
  {
    parent_info.m_Modified = 1;
    if (parent_info.m_ParentInfo)
    {
      SetModifiedBits(*parent_info.m_ParentInfo);
    }
  }
}

void NodifyDocumentModification(const DocumentModification & mod)
{
  
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, bool value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, int8_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, int16_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, int32_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, int64_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint8_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint16_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint32_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, uint64_t value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, float value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::to_string(value),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, czstr value)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    std::string("\"") + Json::escape_string(value) + std::string("\""),
    DocumentModificationType::kSet,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifySet(ReflectionParentInfo & parent_info, void * value, Hash type_name_hash)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
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
    throw std::runtime_error("invalid polymorphic type");
  }
}

void ReflectionNotifyClearArray(ReflectionParentInfo & parent_info)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kClearArray,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyClearObject(ReflectionParentInfo & parent_info)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kClearObject,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyAppendArray(ReflectionParentInfo & parent_info, const std::string & data)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kAppendArray,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyCompress(ReflectionParentInfo & parent_info)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kCompress,
    0
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyInsertArray(ReflectionParentInfo & parent_info, std::size_t index, const std::string & data)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kInsertArray,
    static_cast<uint32_t>(index)
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyInsertObject(ReflectionParentInfo & parent_info, std::size_t index, const std::string & data)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    data,
    DocumentModificationType::kInsertObject,
    static_cast<uint32_t>(index)
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyRemoveArray(ReflectionParentInfo & parent_info, std::size_t index)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kRemoveArray,
    static_cast<uint32_t>(index)
  };

  NodifyDocumentModification(mod);
}

void ReflectionNotifyRemoveObject(ReflectionParentInfo & parent_info, std::size_t index)
{
  if (g_DisableChangeNotification > 0)
  {
    return;
  }

  SetModifiedBits(parent_info);
  DocumentModification mod
  {
    CreateDocumentPath(parent_info),
    "",
    DocumentModificationType::kRemoveObject,
    static_cast<uint32_t>(index)
  };

  NodifyDocumentModification(mod);
}
