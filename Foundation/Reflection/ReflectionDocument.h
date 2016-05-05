#pragma once

#include "Foundation\Common.h"

#include "Foundation\Document\Document.h"
#include "Foundation\Reflection\ReflectionJson.h"

template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, RString>::value
>::type * = 0>
void DecodeDocumentModification(T & value, DocumentModification  & doc, int path_index)
{
  if (path_index != doc.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  value = j;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void DecodeDocumentModification(T & value, Json & j, int path_index)
{
  if (path_index != doc.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  MemberJsonDecoderVisitor decoder(j);
  VisitEach(value, decoder);
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
void DecodeDocumentModification(T & value, Json & j, int path_index)
{
  if (path_index != doc.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  value = T::_from_string(j.get<std::string>().data());
}

template <class T>
void DecodeDocumentModification(RArrayList<T> & value, Json & j, int path_index)
{



  for (auto t : j)
  {
    T new_val;
    DecodeDocumentModification(new_val, t);

    value.PushBack(new_val);
  }
}

template <class T>
void DecodeDocumentModification(RSparseList<T> & value, Json & j, int path_index)
{

  for (auto t : j)
  {
    T new_val;
    DecodeDocumentModification(new_val, t);

    value.PushBack(new_val);
  }
}

template <class T>
void DecodeDocumentModification(RMergeList<T> & value, Json & j, int path_index)
{

  for (Json::iterator it = j.begin(); it != j.end(); ++it)
  {
    T new_val;
    DecodeDocumentModification(new_val, it.value());

    int index = std::stoi(it.key());
    value.InsertAt(new_val, index);
  }
}

template <class T>
void DecodeDocumentModification(RHashMapy<T> & value, Json & j, int path_index)
{
  for (Json::iterator it = j.begin(); it != j.end(); it++)
  {
    T new_val;
    DecodeDocumentModification(new_val, it.value());

    value[it.value().get<RHash>()] = new_val;
  }
}

struct MemberJsonDecoderVisitor
{
  MemberJsonDecoderVisitor(Json & value)
    : m_Value(value)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    DecodeDocumentModification(f.Get(), m_Value[f.Name()]);
  }

public:
  Json & m_Value;
};
