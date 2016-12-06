#pragma once

#include "Foundation/Common.h"

#include <string>


std::string BufferToString(const Buffer & buffer);

template <typename T>
Buffer MoveToBuffer(T && t)
{
  Buffer buffer(sizeof(T));
  new (buffer.Get()) T(std::move(t));
  return buffer;
}

template <typename T>
Buffer CopyToBuffer(const T & t)
{
  Buffer buffer(sizeof(T));
  new (buffer.Get()) T(t);
  return buffer;
}

template <typename T>
T MoveFromBuffer(Buffer & buffer)
{
  T t(std::move(*reinterpret_cast<T *>(buffer.Get())));
  buffer = Buffer();
  return t;
}
