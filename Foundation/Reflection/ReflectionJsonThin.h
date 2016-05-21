#pragma once

#include "Foundation\Common.h"
#include "Foundation\Reflection\ReflectionCommon.h"

std::string ReflectValue(const RByte & value);
std::string ReflectValue(const RShort & value);
std::string ReflectValue(const RInt & value);
std::string ReflectValue(const RLong & value);
std::string ReflectValue(const RUByte & value);
std::string ReflectValue(const RUShort & value);
std::string ReflectValue(const RUInt & value);
std::string ReflectValue(const RULong & value);
std::string ReflectValue(const RFloat & value);
std::string ReflectValue(const RString & value);

template <class EnumType>
std::string ReflectValue(const REnum<EnumType> & value)
{
  char buffer[2048];
  snprintf(buffer, sizeof(buffer), "\"%s\"", value._to_string());
  return buffer;
}

std::string ReflectValue(const void * value, uint32_t type_name_hash);

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
std::string ReflectValue(const T & value)
{
  return ReflectValue(&value, value.GetTypeNameHash());
}


std::string ReflectValuePolymorphic(const void * value, uint32_t type_name_hash);

template <class T>
std::string ReflectValue(RPolymorphic<T> & value)
{
  ReflectValuePolymorphic(value.GetValue(), value.GetTypeNameHash());
}

template <class T>
std::string ReflectValue(const RArrayList<T> & value)
{
  std::stringstream outp;
  outp << "[ ";
  
  auto itr = value.begin();
  auto end = value.end();

  if(itr != end)
  {
    outp << ReflectValue(*itr);

    ++itr;
    while (itr != end)
    {
      outp << ", ";
      outp << ReflectValue(*itr);
      ++itr;
    }
  }

  outp << " ]";
  return outp;
}

template <class T>
std::string ReflectValue(const RMergeList<T> & value)
{
  std::stringstream outp;
  outp << "{ ";

  auto itr = value.begin();
  auto end = value.end();

  if (itr != end)
  {
    outp << "\"";
    outp << std::to_string(itr->first);
    outp << "\": ";
    outp << ReflectValue(itr->second);

    ++itr;
    while (itr != end)
    {
      outp << "\"";
      outp << std::to_string(itr->first);
      outp << "\": ";
      outp << ReflectValue(itr->second);
      ++itr;
    }
  }

  outp << "}";
  return outp;
}

template <class T>
std::string ReflectValue(const RSparseList<T> & value)
{
  std::stringstream outp;
  outp << "{ ";

  auto itr = value.begin();
  auto end = value.end();

  if (itr != end)
  {
    outp << "\"";
    outp << std::to_string(itr->first);
    outp << "\": ";
    outp << ReflectValue(itr->second);

    ++itr;
    while (itr != end)
    {
      outp << "\"";
      outp << std::to_string(itr->first);
      outp << "\": ";
      outp << ReflectValue(itr->second);
      ++itr;
    }
  }

  outp << "}";
  return outp;
}
