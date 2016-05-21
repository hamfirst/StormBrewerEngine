
#include "Foundation\Common.h"

#include <cstdlib>

#include "Document.h"
#include "DocumentModification.h"

Document::Document()
{

}

Document::Document(const std::string & json_data)
{
  m_Root = Json::parse(json_data);
}

Document::Document(const char * json_data)
{
  m_Root = Json::parse(json_data);
}

void Document::ApplyDocumentModification(const DocumentModification & mod, std::vector<DocumentModification> & reverse_operations)
{
  Json * cur_val = &m_Root;
  
  for (int index = 0; index < mod.m_Path.GetSize(); index++)
  {
    if (mod.m_Path[index].m_Type == DocumentPathElement::kIntIndex)
    {
      if (cur_val->is_array() == false)
      {
        throw std::exception("invalid modification path");
      }

      cur_val = &(*cur_val)[mod.m_Path[index].m_IntIndex];
    }
    else if (mod.m_Path[index].m_Type == DocumentPathElement::kStringIndex)
    {
      if (cur_val->is_object() == false || cur_val->find(mod.m_Path[index].m_StringIndex) == cur_val->end())
      {
        throw std::exception("invalid modification path");
      }

      cur_val = &(*cur_val)[mod.m_Path[index].m_StringIndex];
    }
    else
    {
      throw std::exception("invalid modification path");
    }
  }

  switch (mod.m_Type)
  {
  case DocumentModificationType::kSet:
    {
      DocumentModification reverse_mod
      {
        mod.m_Path,
        cur_val->dump(),
        DocumentModificationType::kSet,
        0
      };

      reverse_operations.push_back(reverse_mod);
      *cur_val = Json::parse(mod.m_Data);
    }
    break;
  case DocumentModificationType::kClearArray:
    {
      uint32_t index = 0;
      for (auto elem : *cur_val)
      {
        DocumentModification reverse_mod
        {
          mod.m_Path,
          elem.dump(),
          DocumentModificationType::kInsertArray,
          index
        };

        reverse_operations.push_back(reverse_mod);
        index++;
      }

      *cur_val = Json::array();
    }
    break;
  case DocumentModificationType::kClearObject:
    {
      for (Json::const_iterator itr = cur_val->begin(); itr != cur_val->end(); ++itr)
      {
        DocumentModification reverse_mod
        {
          mod.m_Path,
          itr.value().dump(),
          DocumentModificationType::kInsertArray,
          std::stoul(itr.key())
        };

        reverse_operations.push_back(reverse_mod);
      }

      *cur_val = Json::object();
    }
    break;
  case DocumentModificationType::kAppendArray:
    {
      DocumentModification reverse_mod
      {
        mod.m_Path,
        "",
        DocumentModificationType::kRemoveArray,
        (uint32_t)cur_val->size()
      };

      reverse_operations.push_back(reverse_mod);
      cur_val->push_back(Json::parse(mod.m_Data));
    }
    break;
  case DocumentModificationType::kCompress:
    {
      throw std::exception("compress is not allowed during serialization");
    }
    break;
  case DocumentModificationType::kInsertArray:
    {
      DocumentModification reverse_mod
      {
        mod.m_Path,
        "",
        DocumentModificationType::kRemoveArray,
        mod.m_Index
      };

      reverse_operations.push_back(reverse_mod);
      auto pos = cur_val->begin() + mod.m_Index;

      cur_val->insert(pos, Json::parse(mod.m_Data));
    }
    break;
  case DocumentModificationType::kInsertObject:
    {
      DocumentModification reverse_mod
      {
        mod.m_Path,
        "",
        DocumentModificationType::kRemoveObject,
        mod.m_Index
      };

      cur_val->operator[](std::to_string(mod.m_Index)) = Json::parse(mod.m_Data);
    }
    break;
  case DocumentModificationType::kRemoveArray:
    {
      auto pos = cur_val->begin() + mod.m_Index;
      DocumentModification reverse_mod
      {
        mod.m_Path,
        (*pos).dump(),
        DocumentModificationType::kInsertArray,
        mod.m_Index
      };

      reverse_operations.push_back(reverse_mod);
      cur_val->erase(mod.m_Index);
    }
    break;
  case DocumentModificationType::kRemoveObject:
    {
      std::string index = std::to_string(mod.m_Index);
      Json & sub_val = cur_val->at(index);
      DocumentModification reverse_mod
      {
        mod.m_Path,
        sub_val.dump(),
        DocumentModificationType::kInsertObject,
        mod.m_Index
      };

      reverse_operations.push_back(reverse_mod);
      cur_val->erase(index);
    }
    break;
  }
}
