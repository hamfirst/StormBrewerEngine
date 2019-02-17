

#include "DocumentServerVCS.refl.h"

struct DocumentServerVCSGitInitData : public DocumentServerVCSInitData
{
  STORM_REFL;

  std::string RootPath;
};

class DocumentServerVCSGit : public DocumentServerVCS
{
public:
  DocumentServerVCSGit();
  ~DocumentServerVCSGit();

  bool Init(const std::string_view & settings, const std::string_view & project_dir,
      const std::string & self_path, Delegate<void, const std::string &> && error_callback) override;

  void GetStatus(std::vector<DocumentServerVCSQuery> & queries) override;
  void Add(std::vector<DocumentServerVCSOperation> & files) override;
  void Remove(const std::string_view & file_path) override;
  void Revert(const std::string_view & file_path) override;

private:
  bool ConvertPath(std::string & path);

private:
  Delegate<void, const std::string &> m_ErrorCallback;
  std::string m_RootPath;
  std::string m_SelfPath;
};

