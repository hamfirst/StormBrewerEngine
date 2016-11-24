
#include "Document.h"


Document::Document(const std::string & file_name, const std::string & file_type, const std::string & data) :
  m_Filename(file_name),
  m_FileType(file_type),
  m_Json(Json::parse(data))
{

}

void Document::ApplyChanges(const DocumentChangeList & changes)
{
  m_AllChanges.push_back(changes);
  
  DocumentChangeList reverse_list;
  for (auto & change : changes)
  {
    ApplyChangeNotification(change, reverse_list);
  }

  m_UndoList.emplace_back(std::move(reverse_list));
  m_RedoList.clear();

  m_Modified = true;
}

void Document::Undo(DocumentChangeList & applied_changes)
{
  DocumentChangeList reverse_list;
  applied_changes = std::move(m_UndoList.back());
  m_UndoList.pop_back();

  for (auto & change : applied_changes)
  {
    ApplyChangeNotification(change, reverse_list);
  }

  m_RedoList.emplace_back(std::move(m_AllChanges.back()));
  m_AllChanges.pop_back();
}

void Document::Redo(DocumentChangeList & applied_changes)
{
  DocumentChangeList reverse_list;
  applied_changes = std::move(m_RedoList.back());
  m_RedoList.pop_back();

  for (auto & change : applied_changes)
  {
    ApplyChangeNotification(change, reverse_list);
  }

  m_UndoList.emplace_back(std::move(reverse_list));
}

bool Document::HasUndo() const
{
  return m_UndoList.size() != 0;
}

bool Document::HasRedo() const
{
  return m_RedoList.size() != 0;
}

bool Document::IsModified() const
{
  return m_Modified;
}

void Document::ResetModified()
{
  m_Modified = false;
}

std::string Document::SerializeFull()
{
  return m_Json.dump(2);
}

void Document::ReplaceData(std::string & data)
{
  m_Json = Json::parse(data);
}

bool Document::ApplyChangeNotification(const ReflectionChangeNotification & change_notification, DocumentChangeList & reverse_ops)
{
  Json & json = m_Json;
  const char * path = change_notification.m_Path.c_str();

  while (*path != 0)
  {
    if (*path == '.')
    {
      std::string path_elem;
      path++;

      while (*path != '.' && *path != '[' && *path != 0)
      {
        if (*path == ' ')
        {
          return false;
        }

        path_elem += *path;
      }

      json = json.at(path_elem);
    }
    else if (*path == '[')
    {
      uint64_t index = 0;
      path++;

      if (*path < '0' || *path > '9')
      {
        return false;
      }

      while (*path != ']')
      {
        if (*path < '0' || *path > '9')
        {
          return false;
        }

        index *= 10;
        index += *path - '0';

        path++;
      }
      
      path++;
      json = json.at(index);
    }
    else
    {
      return false;
    }
  }

  ReflectionChangeNotification return_notificaiton;
  Json compressed_json;
  int compressed_index;

  switch (change_notification.m_Type)
  {
  case ReflectionNotifyChangeType::kSet:
    return_notificaiton.m_Type = ReflectionNotifyChangeType::kSet;
    return_notificaiton.m_Path = change_notification.m_Path;
    return_notificaiton.m_Data = json.dump();
    reverse_ops.emplace_back(std::move(return_notificaiton));

    json = Json::parse(change_notification.m_Data);
    break;
  case ReflectionNotifyChangeType::kClear:
    return_notificaiton.m_Type = ReflectionNotifyChangeType::kSet;
    return_notificaiton.m_Path = change_notification.m_Path;
    return_notificaiton.m_Data = json.dump();
    reverse_ops.emplace_back(std::move(return_notificaiton));

    json.clear();
    break;
  case ReflectionNotifyChangeType::kCompress:
    return_notificaiton.m_Type = ReflectionNotifyChangeType::kSet;
    return_notificaiton.m_Path = change_notification.m_Path;
    return_notificaiton.m_Data = json.dump();
    reverse_ops.emplace_back(std::move(return_notificaiton));

    compressed_index = 0;

    for (auto itr = json.begin(); itr != json.end(); ++itr)
    {
      compressed_json[std::to_string(compressed_index)] = itr.value();
      compressed_index++;
    }

    json = compressed_json;
    break;
  case ReflectionNotifyChangeType::kInsert:
    return_notificaiton.m_Type = ReflectionNotifyChangeType::kRemove;
    return_notificaiton.m_Path = change_notification.m_Path;
    return_notificaiton.m_SubIndex = change_notification.m_SubIndex;
    reverse_ops.emplace_back(std::move(return_notificaiton));

    json[std::to_string(change_notification.m_SubIndex)] = Json::parse(change_notification.m_Data);
    break;
  case ReflectionNotifyChangeType::kRemove:
    return_notificaiton.m_Type = ReflectionNotifyChangeType::kInsert;
    return_notificaiton.m_Path = change_notification.m_Path;
    return_notificaiton.m_SubIndex = change_notification.m_SubIndex;
    return_notificaiton.m_Data = json.at(std::to_string(change_notification.m_SubIndex)).dump();
    reverse_ops.emplace_back(std::move(return_notificaiton));

    json[std::to_string(change_notification.m_SubIndex)] = Json::parse(change_notification.m_Data);
    break;
  default:
    return false;
  }

  return true;
}

