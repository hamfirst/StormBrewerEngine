#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/FrameData/FrameDataExtract.h"
#include "Runtime/Event/Event.h"
#include "Runtime/BinaryResource/BinaryResourceBase.h"
#include "Runtime/BinaryResource/BinaryResourcePtr.h"

class GenericBinaryResource;

using GenericBinaryResourcePtr = BinaryResourcePtr<GenericBinaryResource>;
using GenericBinaryResourceLoadLink = BinaryResourceLoadCallbackLink<GenericBinaryResource>;

class GenericBinaryResource : public BinaryResourceBase
{
public:
  GenericBinaryResource(Any && load_data, uint32_t path_hash, czstr path);

  const void * GetData() const;
  std::size_t GetLength() const;

  GenericBinaryResourceLoadLink AddLoadCallback(Delegate<void, NotNullPtr<GenericBinaryResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<GenericBinaryResource>> && callback, BinaryResourceLoadCallbackLink<GenericBinaryResource> & load_link);

  static GenericBinaryResourcePtr Find(uint32_t file_path_hash);
  static GenericBinaryResourcePtr Load(czstr file_path);
  static GenericBinaryResourceLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<GenericBinaryResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<GenericBinaryResource>> && callback, GenericBinaryResourceLoadLink & load_link);

protected:
  virtual void OnDataLoadComplete(const void * data, std::size_t length) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  const void * m_Data;
  std::size_t m_Length;

  DelegateList<void, NotNullPtr<GenericBinaryResource>> m_LoadCallbacks;
};
