#pragma once

#include "Foundation/Any/Any.h"
#include "Foundation/Buffer/Buffer.h"

#include "Runtime/RuntimeCommon.h"


typedef void(*BinaryResourceLoaderCallback)(uint32_t path_hash, const void * resource_data, std::size_t length, void * user_ptr);

class BinaryResourceLoader 
{
public:
  virtual Any LoadResource(czstr path, BinaryResourceLoaderCallback load_callback, void * user_ptr) = 0;
  virtual void UnloadResource(uint32_t path_hash, Any && load_data) = 0;
};
