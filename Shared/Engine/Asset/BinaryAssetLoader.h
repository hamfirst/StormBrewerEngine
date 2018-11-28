#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/BinaryResource/BinaryResourceLoader.h"

class BinaryAssetLoader : public BinaryResourceLoader
{
public:
  virtual Any LoadResource(czstr path, BinaryResourceLoaderCallback load_callback, void * user_ptr) override;
  virtual void UnloadResource(uint32_t path_hash, Any && load_data) override;
};

