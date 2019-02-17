
#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "Foundation/Delegate/Delegate.h"

#include "StormRefl/StormRefl.h"

enum class VCSStatus
{
  kUnknown,
  kCurrent,
  kNew,
  kAdded,
  kModified,
};

enum STORM_REFL_ENUM DocumentServerVCSType
{
  Git,
#ifdef ENABLE_PERFORCE
  Perforce,
#endif
};


struct DocumentServerVCSInitData
{
  STORM_REFL;

  DocumentServerVCSType Type = DocumentServerVCSType::Git;
};

struct DocumentServerVCSQuery
{
  std::string m_FilePath;
  VCSStatus m_Status = VCSStatus::kUnknown;
};

struct DocumentServerVCSOperation
{
  std::string m_FilePath;
  bool m_Success = false;
};


class DocumentServerVCS
{
public:
  virtual ~DocumentServerVCS() {}

  virtual bool Init(const std::string_view & settings, const std::string_view & project_dir,
                    const std::string & self_path, Delegate<void, const std::string &> && error_callback) { return false; }

  virtual void GetStatus(std::vector<DocumentServerVCSQuery> & queries) {}

  virtual void Add(std::vector<DocumentServerVCSOperation> & files) {}
  virtual bool Checkout(const std::string_view & file_path) { return true; }
  virtual void Remove(const std::string_view & file_path) {}
  virtual void Revert(const std::string_view & file_path) {}
};