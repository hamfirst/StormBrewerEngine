#pragma once

#include <functional>

#include "Foundation/Json/Json.h"
#include "Foundation/Delegate/Delegate.h"
#include "Foundation/Document/DocumentTypes.refl.h"

#include <StormData/StormDataChangeNotifier.h>

class DocumentCompiler;

enum class DocumentState
{
  kLoading,
  kLoaded,
  kLoadFailure,
  kDependentError,
};

class Document
{
public:

  using DocumentChangeHandler = Delegate<void, uint64_t, Document *, const ReflectionChangeNotification &>;
  using DocumentStateChangeHandler = Delegate<void, uint64_t, Document *, DocumentState, DocumentState>;
  using DocumentLinksChangeHandler = Delegate<void, uint64_t, Document *>;

  Document(NotNullPtr<DocumentCompiler> compiler, czstr path);

  Document(const Document & rhs) = delete;
  Document(Document && rhs) = delete;

  Document & operator = (const Document & rhs) = delete;
  Document & operator = (Document && rhs) = delete;

  ~Document();

  const std::string & GetPath() const;
  uint64_t GetFileId() const;
  DocumentState GetState() const;

  std::string GetDocumentJson();

  void ParseFull(const char * file_data);
  void FileError();
  void Save();

  void SetChangeHandler(DocumentChangeHandler && change_handler);
  void SetStateChangeHandler(DocumentStateChangeHandler && change_handler);
  void SetLinksChangeHandler(DocumentLinksChangeHandler && change_handler);

  void ApplyChange(const ReflectionChangeNotification & change, bool as_redo = false);
  void AddLink(const char * source_document, const char * source_path, const char * dest_path, bool as_redo = false);
  bool RemoveLink(uint64_t file_id, const char * source_path, const char * dest_path, bool as_redo = false);

  std::vector<std::tuple<std::string, std::string, std::string>> GetLinks();

  bool Undo();
  bool Redo();

  void CommitUndo();
  void CommitRedo();
  void CleanRedoList();

  void AddRef();
  void DecRef();

  static std::string CreateEmptyFile();

  static const uint32_t kInvalidChanerId = 0xFFFFFFFF;

private:

  struct DocumentDependency
  {
    Document * m_Document;
    std::string m_Path;
  };

  struct DocumentLinkData
  {
    Document * m_Document;
    uint64_t m_FileId;
    bool m_Loaded;
    bool m_Error;
    DocumentLink m_Link;
  };

  bool RecompileAtPath(czstr path, Json & outp_json);

  void CheckForCompleteLoad();
  void CheckForFixedLoad();
  void ProcessLinkLoad(DocumentLinkData & link);

  void SetUnloaded();
  void SetCompletedLoad();
  void SetDependentError();
  void SetFileError();

  void HandleLinkLoaded(Document * source_document, const char * path, NullOptPtr<Json> json);
  void HandleLinkFailed(Document * source_document, const char * path);
  void HandleLinkChanged(Document * source_document, const ReflectionChangeNotification & change);

  void AddDependency(Document * dependent, const char * path);
  void RemoveDependency(Document * dependent, const char * path);

private:

  NotNullPtr<DocumentCompiler> m_Compiler;
  std::string m_Path;
  uint64_t m_FileId;
  DocumentState m_State;

  int m_RefCount;

  std::vector<DocumentLinkData> m_Links;
  std::vector<DocumentDependency> m_Dependencies;

  std::vector<std::function<void()>> m_Undo;
  std::vector<std::function<void()>> m_Redo;

  std::vector<std::function<void()>> m_CurrentUndo;
  std::vector<std::function<void()>> m_CurrentRedo;

  DocumentChangeHandler m_ChangeHandler;
  DocumentStateChangeHandler m_StateChangeHandler;
  DocumentLinksChangeHandler m_LinksChangedHandler;

  Json m_FileJson;
  Json m_Compiled;
};


