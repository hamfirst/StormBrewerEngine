#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

#include <functional>

class StormBootstrap
{
public:
  StormBootstrap();
  StormBootstrap(int argc, const char ** argv);
  StormBootstrap(const StormBootstrap & rhs) = delete;
  StormBootstrap(StormBootstrap && rhs) = delete;
  ~StormBootstrap();

  StormBootstrap & operator = (const StormBootstrap & rhs) = delete;
  StormBootstrap & operator = (StormBootstrap && rhs) = delete;

  void LoadConfigFile(const std::string_view & path, std::function<void(const std::string &)> && callback);
  void RequestUrl(const std::string_view & url, const std::string_view & headers, std::function<void(const std::string &)> && callback);
  void PostUrl(const std::string_view & url, const std::string_view & headers, const std::string_view & body, std::function<void(const std::string &)> && callback);

  void Run();
  void PrintDebug() const;

  void Set(const std::string_view & name, const std::string_view & value);
  std::string Get(const std::string_view & name) const;
  bool HasValue(const std::string_view & name) const;

  std::size_t GetNumArgs() const;
  const std::string & GetArg(int index) const;

  const std::string & GetExecutablePath() const;
  const std::string & GetExecutableDirectory() const;

private:

  void InitNetwork();
  void Cleanup();


  enum class Priority
  {
    kDefault,
    kFileConfig,
    kWebConfig,
    kCommandLine,
    kPostRun,
  };

  struct Value
  {
    Priority m_Priority;
    std::string m_Data;
  };

  Priority m_CurrentPriority = Priority::kDefault;
  std::unordered_map<std::string, Value> m_Values;

  std::string m_ExecutablePath;
  std::string m_ExecutableDirectory;

  std::vector<std::string> m_Args;

  void * m_Backend = nullptr;
  void * m_Frontend = nullptr;

  std::unordered_map<unsigned int, std::function<void(const std::string &)>> m_Jobs;
};