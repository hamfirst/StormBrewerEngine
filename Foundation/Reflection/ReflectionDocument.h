#pragma once

#include "Foundation\Common.h"

#include "Foundation\Document\Document.h"
#include "Foundation\Document\DocumentModification.h"
#include "Foundation\Reflection\ReflectionJson.h"

template <typename NumericType>
void DecodeDocumentModification(RNumber<NumericType> & value, const DocumentModification & mod, int path_index)
{
  if (path_index != mod.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  if (mod.m_Type != DocumentModificationType::kSet)
  {
    throw std::exception("invalid doc path");
  }

  value = ParseNumber<NumericType>(mod.m_Data);
}

static void DecodeDocumentModification(RBool & value, const DocumentModification & mod, int path_index)
{
  if (path_index != mod.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  if (mod.m_Type != DocumentModificationType::kSet)
  {
    throw std::exception("invalid doc path");
  }

  value = ParseBool(mod.m_Data);
}

static void DecodeDocumentModification(RString & value, const DocumentModification & mod, int path_index)
{
  if (path_index != mod.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  if (mod.m_Type != DocumentModificationType::kSet)
  {
    throw std::exception("invalid doc path");
  }

  value = Json::parse(mod.m_Data).get<std::string>();
}

template <typename EnumType>
void DecodeDocumentModification(REnum<EnumType> & value, const DocumentModification & mod, int path_index)
{
  if (path_index != mod.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  if (mod.m_Type != DocumentModificationType::kSet)
  {
    throw std::exception("invalid doc path");
  }

  value = EnumType::_from_string(Json::parse(mod.m_Data).get<std::string>());
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = nullptr>
void DecodeDocumentModification(T & value, const DocumentModification & mod, int path_index)
{
  if (path_index == mod.m_Path.GetSize() - 1)
  {
    throw std::exception("invalid doc path");
  }

  if (mod.m_Path[path_index].m_Type != DocumentPathElement::kStringIndex)
  {
    throw std::exception("invalid doc path");
  }

  MemberDocumentDecoderVisitor decoder(mod, path_index);
  VisitField(value, decoder, crc32(mod.m_Path[path_index].m_StringIndex));
}


template <class T>
void DecodeDocumentModification(RArrayList<T> & value, const DocumentModification & mod, int path_index)
{
  if (path_index == mod.m_Path.GetSize() - 1)
  {
    switch (mod.m_Type)
    {
    case kSet:
    case kCompress:
    case kClearObject:
    case kInsertObject:
    case kRemoveObject:
      throw std::exception("invalid doc modification");
    case kClearArray:
      {
        value.Clear();
      }
      break;
    case kAppendArray:
      {
        Json json_val = Json::parse(mod.m_Data);
        T t;
        DecodeJson(t, json_val);

        value.PushBack(t);
      }
      break;
    case kInsertArray:
      {
        Json json_val = Json::parse(mod.m_Data);
        T t;
        DecodeJson(t, json_val);

        value.InsertAt(t, mod.m_Index);
      }
      break;
    case kRemoveArray:
      {
        value.RemoveAt(mod.m_Index);
      }
      break;
    }
  }
  else
  {
    if (mod.m_Path[path_index].m_Type != DocumentPathElement::kIntIndex)
    {
      throw std::exception("invalid doc path");
    }

    DecodeDocumentModification(value[mod.m_Path[path_index].m_IntIndex], mod, path_index + 1);
  }
}

template <class T>
void DecodeDocumentModification(RSparseList<T> & value, const DocumentModification & mod, int path_index)
{

}

template <class T>
void DecodeDocumentModification(RMergeList<T> & value, const DocumentModification & mod, int path_index)
{

}

template <class T>
void DecodeDocumentModification(RHashMapy<T> & value, const DocumentModification & mod, int path_index)
{

}

struct MemberDocumentDecoderVisitor
{
  MemberDocumentDecoderVisitor(const DocumentModification & value, int path_index)
    : m_Value(value),
      m_PathIndex(path_index)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    DecodeDocumentModification(f.Get(), m_Value, m_PathIndex + 1);
  }

public:
  const DocumentModification & m_Value;
  int m_PathIndex;
};
