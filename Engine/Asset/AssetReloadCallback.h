#pragma once


class AssetReloadCallback
{
public:
  virtual void ReloadFile(const char * path) = 0;
};

struct AssetReloadInfo
{
  NotNullPtr<AssetReloadCallback> m_Callback;
  NullOptPtr<AssetReloadInfo> m_Next;
};