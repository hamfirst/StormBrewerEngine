
#include "Foundation/Common.h"

std::string BufferToString(const Buffer & buffer)
{
  const char * buffer_data = (char *)buffer.Get();
  return std::string(buffer_data, buffer_data + buffer.GetSize());
}
