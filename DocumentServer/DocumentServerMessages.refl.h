#pragma once

#include <StormRefl/StormRefl.h>

#include <string>
#include <vector>

static const int kDocumentServerVersion = 1;

enum STORM_REFL_ENUM class DocumentServerMessageType
{
  kUnknown,
  kInitComplete,
  kCreateRequest,
  kCreateError,
  kOpenRequest,
  kOpenError,
  kOpenData,
  kOpenFinalizeRequest,
  kOpenFinalizeReponse,
  kSetEditorData,
  kChangeRequest,
  kApplyChange,
  kChangeState,
  kUndo,
  kRedo,
  kSave,
  kSaveError,
  kClose,
};


struct DocumentServerMessageState
{
  STORM_REFL;
  bool m_HasUndo = false;
  bool m_HasRedo = false;
  bool m_IsModified = false;
};

struct DocumentServerMessageInitComplete
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kInitComplete;
  int m_Version;
};

struct DocumentServerMessageCreateRequest
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kCreateRequest;

  std::string m_FileType;
  std::string m_FileName;
  std::string m_Data;
};


struct DocumentServerMessageCreateError
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kCreateError;

  std::string m_FileType;
  std::string m_FileName;
  std::string m_Error;
};

struct DocumentServerMessageOpenRequest
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kOpenRequest;

  std::string m_FileType;
  std::string m_FileName;
};

struct DocumentServerMessageOpenError
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kOpenError;

  std::string m_FileType;
  std::string m_FileName;
  std::string m_Error;
};

struct DocumentServerMessageOpen
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kOpenData;

  int m_DocumentId;
  std::string m_FileType;
  std::string m_FileName;
  std::string m_Data;
  std::string m_EditorData;
  DocumentServerMessageState m_State;
};

struct DocumentServerMessageFinalizeRequest
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kOpenFinalizeRequest;

  std::string m_FileType;
  std::string m_FileName;
  std::string m_Data;
};

struct DocumentServerMessageFinalizeResponse
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kOpenFinalizeReponse;

  std::string m_FileType;
  std::string m_FileName;
  std::string m_Data;
};

struct DocumentServerMessageSetEditorData
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kSetEditorData;

  int m_DocumentId;
  std::string m_EditorData;
};

struct DocumentServerMessageChangeRequest
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kChangeRequest;

  int m_DocumentId;
  std::vector<std::string> m_Changes;
};

struct DocumentServerMessageApplyChange
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kApplyChange;

  int m_DocumentId;
  std::vector<std::string> m_Changes;
  DocumentServerMessageState m_State;
};

struct DocumentServerMessageChangeState
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kChangeState;

  int m_DocumentId;
  DocumentServerMessageState m_State;
};

struct DocumentServerMessageUndo
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kUndo;

  int m_DocumentId;
};

struct DocumentServerMessageRedo
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kRedo;

  int m_DocumentId;
};

struct DocumentServerMessageSave
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kSave;

  int m_DocumentId;
};

struct DocumentServerMessageSaveError
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kSaveError;

  int m_DocumentId;
  std::string m_Error;
};

struct DocumentServerMessageClose
{
  STORM_REFL;
  static const DocumentServerMessageType Type = DocumentServerMessageType::kClose;

  int m_DocumentId;
};
