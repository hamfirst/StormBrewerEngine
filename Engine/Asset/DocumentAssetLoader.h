#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/DocumentResource/DocumentResourceLoader.h"

class DocumentAssetLoader : public DocumentResourceLoader
{
public:
  virtual Any LoadResource(czstr path, DocumentResourceLoaderCallback load_callback, void * user_ptr) override;
  virtual void UnloadResource(uint32_t path_hash, Any && load_data) override;
};

