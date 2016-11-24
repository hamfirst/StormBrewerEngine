#pragma once

#include "Foundation/Json/Json.h"

#include <StormData/StormDataChangePacket.h>

using DocumentChangeList = std::vector<ReflectionChangeNotification>;

class Document
{
public:
  Document(const std::string & file_name, const std::string & file_type, const std::string & data);
  Document(const Document & rhs) = default;
  Document(Document && rhs) = default;

  Document & operator = (const Document & rhs) = default;
  Document & operator = (Document && rhs) = default;

  void ApplyChanges(const DocumentChangeList & changes);
  void Undo(DocumentChangeList & applied_changes);
  void Redo(DocumentChangeList & applied_changes);

  bool HasUndo() const;
  bool HasRedo() const;
  bool IsModified() const;
  void ResetModified();

  const std::string & GetFileName() const { return m_Filename; }
  const std::string & GetFileType() const { return m_FileType; }

  std::string SerializeFull();
  void ReplaceData(std::string & data);

private:

  bool ApplyChangeNotification(const ReflectionChangeNotification & change_notification, DocumentChangeList & reverse_ops);

private:

  std::string m_Filename;
  std::string m_FileType;

  std::vector<DocumentChangeList> m_AllChanges;
  std::vector<DocumentChangeList> m_UndoList;
  std::vector<DocumentChangeList> m_RedoList;

  bool m_Modified = false;

  Json m_Json;
};

