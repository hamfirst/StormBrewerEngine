
#include <string>
#include <string_view>

#include "Foundation/Delegate/Delegate.h"

class DocumentServerVCS
{
public:
  virtual void Init(const std::string_view & settings, Delegate<void, const std::string &> && error_callback) {}

  virtual void Add(const std::string_view & file_path) {}
  virtual void Checkout(const std::string_view & file_path) {}
  virtual void Remove(const std::string_view & file_path) {}
  virtual void Rename(const std::string_view & file_path) {}
  virtual void Revert(const std::string_view & file_path) {}
  virtual void Commit(const std::string_view & message) {}
};