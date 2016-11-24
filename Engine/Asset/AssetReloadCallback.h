#pragma once


class AssetReloadCallback
{
public:
  virtual void ReloadFile(const char * path) = 0;
};

struct AssetReloadInfo
{
  AssetReloadCallback * m_Callback;
  AssetReloadInfo * m_Next;
};