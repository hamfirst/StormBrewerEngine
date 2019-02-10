#pragma once

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <optional>

#include "Packets.h"

struct DistFetcherInternal;

struct BuildInfo
{
  int m_BuildId;
  std::string m_Name;
  std::string m_Date;
  DistPlatform m_Platform;
};

enum class DistFetcherResult
{
  kDone,
  kProjectDirNotFound,
  kProjectSettingsNotFound,
  kProjectSettingsInvalid,
  kConnectionFailed,
  kDisconnected,
  kDownloadListFailed,
  kInvalidBuildId
};

class DistFetcher
{
public:
  DistFetcher();
  DistFetcher(int build_id);

  DistFetcher(const DistFetcher & rhs) = delete;
  DistFetcher(DistFetcher && rhs) = delete;

  DistFetcher & operator =(const DistFetcher & rhs) = delete;
  DistFetcher & operator =(DistFetcher && rhs) = delete;

  ~DistFetcher();

  bool Update();
  void Sync();

  std::optional<std::vector<BuildInfo>> GetBuildInfo();
  std::optional<std::pair<const void *, std::size_t>> GetDownloadData();
  std::optional<DistFetcherResult> GetResult();

private:

  bool ReadProjectSettings();
  void StartConnection();
  bool SetResult(DistFetcherResult result);

private:
  std::unique_ptr<DistFetcherInternal> m_Data;
};