#pragma once

#include "Foundation/Any/Any.h"

#include "Runtime/RuntimeCommon.h"


typedef void(*DocumentResourceLoaderCallback)(uint64_t path_hash, NullOptPtr<std::string> resource_data, void * user_ptr);

class DocumentResourceLoader 
{
public:
  virtual Any LoadResource(czstr path, DocumentResourceLoaderCallback load_callback, void * user_ptr) = 0;
  virtual void UnloadResource(uint64_t path_hash, Any && load_data) = 0;
};
