

#include "DocumentServerVCS.refl.h"


struct DocumentServerVCSPerforceInitData : public DocumentServerVCSInitData
{
  STORM_REFL;

  std::string RootPath;
  std::string User;
  std::string Password;
  std::string Port;
  std::string Client;
};

#ifdef ENABLE_PERFORCE
class ClientApi;

class DocumentServerVCSPerforce : public DocumentServerVCS
{
public:
  DocumentServerVCSPerforce();
  ~DocumentServerVCSPerforce();

  bool Init(const std::string_view & settings, const std::string_view & project_dir,
      const std::string & self_path, Delegate<void, const std::string &> && error_callback) override;

  void GetStatus(std::vector<DocumentServerVCSQuery> & queries) override;
  void Add(std::vector<DocumentServerVCSOperation> & files) override;
  void Remove(const std::string_view & file_path) override;
  void Revert(const std::string_view & file_path) override;

private:
  template <typename Visitor, typename ErrorCb>
  void WithClient(Visitor && visitor, ErrorCb && errorcb);

  template <typename Visitor, typename ErrorCb, typename InfoCb>
  void WithClient(Visitor && visitor, ErrorCb && errorcb, InfoCb && infocb);

  template <typename Visitor, typename ErrorCb, typename InfoCb, typename StatCb>
  void WithClient(Visitor && visitor, ErrorCb && errorcb, InfoCb && infocb, StatCb && statcb);

  bool ConvertPath(std::string & path);

private:
  Delegate<void, const std::string &> m_ErrorCallback;
  std::string m_RootPath;
  std::string m_SelfPath;
  std::string m_User;
  std::string m_Pass;
  std::string m_Port;
  std::string m_Client;
};

#endif
