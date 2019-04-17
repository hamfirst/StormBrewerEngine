#pragma once

#include <vector>
#include <unordered_map>

#include "StormData/StormDataTypes.h"

struct PropertyField;

enum class PropertyFieldType
{
  kUnknown,
  kBool,
  kSignedNumber,
  kUnsignedNumber,
  kFloatNumber,
  kFloatNumberDeterministic,
  kString,
  kFile,
  kEnum,
  kList,
  kPolymorphic,
  kStruct,
};

struct PropertyFieldEnumData
{
  std::vector<std::pair<uint64_t, std::string>> m_PossibleValues;
};

struct PropertyFieldPolymorphicOptionData
{
  std::string m_Name;
  uint32_t m_NameHash;
  PropertyField * m_FieldData;
};

struct PropertyFieldPolymorphicData
{
  std::vector<PropertyFieldPolymorphicOptionData> m_PossibleValues;
};

struct PropertyFieldStructMemberData
{
  std::string m_Name;
  void *(*GetMember)(void * obj);
  PropertyField * m_FieldData;
};

struct PropertyFieldStructData
{
  uint32_t m_TypeNameHash;
  std::vector<PropertyFieldStructMemberData> m_Members;
};

struct PropertyField
{
  PropertyFieldType m_Type;

  union
  {
    struct
    {
      int64_t(*Get)(void *);
      void(*Set)(void *, int64_t);
      int64_t m_Min;
      int64_t m_Max;
    } m_SignedNumber;

    struct
    {
      uint64_t(*Get)(void *);
      void(*Set)(void *, uint64_t);
      uint64_t m_Min;
      uint64_t m_Max;
    } m_UnsignedNumber;

    struct
    {
      float(*Get)(void *);
      void(*Set)(void *, float);
      float m_Min;
      float m_Max;
    } m_FloatNumber;

    struct
    {
      czstr(*Get)(void *);
      void(*Set)(void *, czstr);
      float m_Min;
      float m_Max;
    } m_FloatNumberDeterministic;

    struct
    {
      int m_MaxLength;
    } m_String;

    struct
    {
      const char * m_Extension;
    } m_File;

    struct
    {
      czstr(*Get)(void * en);
      void(*Set)(void * en, czstr val);
      PropertyFieldEnumData * m_EnumData;
    } m_Enum;

    struct
    {
      void *(*GetElement)(void * obj, std::size_t index);
      void(*Insert)(void * obj, std::size_t index);
      void(*Remove)(void * obj, std::size_t index);
      std::size_t(*Append)(void * obj);
      std::vector<std::size_t>(*GetElementIndices)(void * obj);
      PropertyField * m_ListData;
    } m_List;

    struct
    {
      uint32_t(*GetType)(void * obj);
      void(*SetType)(void * obj, uint32_t);
      void *(*GetValue)(void * obj);
      PropertyFieldPolymorphicData * m_PolyData;
    } m_Poly;

    struct
    {
      PropertyFieldStructData * m_StructData;
    } m_Struct;
  };
};
