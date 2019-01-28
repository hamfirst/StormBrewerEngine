
#pragma once
#pragma pack(push, 1)

enum class MessageType
{
  kUpload,
  kUploadSuccess,
  kDownloadList,
  kDownload
};

struct UploadRequest
{
  uint32_t m_FileSize;
  char m_Name[16];
};

struct DownloadList
{
  int m_Id;
  char m_Name[64];
};


#pragma pack(pop)