
#pragma once
#pragma pack(push, 1)

enum class MessageType
{
  kUpload,
  kUploadSuccess,
  kDownloadList,
  kDownload,
  kDownloadLatest,
};

enum class DistPlatform
{
  kUnknown,
  kWindows,
  kLinux,
  kMac,
};

struct DownloadListReqHeader
{
  int32_t m_Type;
};

struct DownloadBuildReqHeader
{
  int32_t m_Type;
  int32_t m_Id;
};

struct UploadRequest
{
  uint32_t m_FileSize;
  uint32_t m_Platform;
  char m_Name[16];
};

struct DownloadList
{
  uint32_t m_Id;
  char m_Name[64];
};

#ifdef _WINDOWS
#define CUR_PLATFORM DistPlatform::kWindows
#endif

#ifdef _LINUX
#define CUR_PLATFORM DistPlatform::kLinux
#endif

#ifdef _MACOS
#define CUR_PLATFORM DistPlatform::kMac
#endif

#pragma pack(pop)