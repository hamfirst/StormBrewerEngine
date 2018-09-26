
#include "Foundation/Common.h"
#include "Foundation/PropertyMeta/PropertyFieldDatabase.h"

PropertyFieldDatabase::PropertyFieldDatabase()
{
  m_Unknown.m_Type = PropertyFieldType::kUnknown;
  m_BasicBool.m_Type = PropertyFieldType::kBool;

  m_BasicInt8.m_Type = PropertyFieldType::kSignedNumber;
  m_BasicInt8.m_SignedNumber.Get = [](void * obj) -> int64_t { auto var = static_cast<RNumber<int8_t> *>(obj); return (int8_t)(*var); };
  m_BasicInt8.m_SignedNumber.Set = [](void * obj, int64_t val) { auto var = static_cast<RNumber<int8_t> *>(obj); (*var) = (int8_t)val; };
  m_BasicInt8.m_SignedNumber.m_Min = INT8_MIN;
  m_BasicInt8.m_SignedNumber.m_Max = INT8_MAX;

  m_BasicInt16.m_Type = PropertyFieldType::kSignedNumber;
  m_BasicInt16.m_SignedNumber.Get = [](void * obj) -> int64_t { auto var = static_cast<RNumber<int16_t> *>(obj); return (int16_t)(*var); };
  m_BasicInt16.m_SignedNumber.Set = [](void * obj, int64_t val) { auto var = static_cast<RNumber<int16_t> *>(obj); (*var) = (int16_t)val; };
  m_BasicInt16.m_SignedNumber.m_Min = INT16_MIN;
  m_BasicInt16.m_SignedNumber.m_Max = INT16_MAX;

  m_BasicInt32.m_Type = PropertyFieldType::kSignedNumber;
  m_BasicInt32.m_SignedNumber.Get = [](void * obj) -> int64_t { auto var = static_cast<RNumber<int32_t> *>(obj); return (int32_t)(*var); };
  m_BasicInt32.m_SignedNumber.Set = [](void * obj, int64_t val) { auto var = static_cast<RNumber<int32_t> *>(obj); (*var) = (int32_t)val; };
  m_BasicInt32.m_SignedNumber.m_Min = INT32_MIN;
  m_BasicInt32.m_SignedNumber.m_Max = INT32_MAX;

  m_BasicInt64.m_Type = PropertyFieldType::kSignedNumber;
  m_BasicInt64.m_SignedNumber.Get = [](void * obj) -> int64_t { auto var = static_cast<RNumber<int64_t> *>(obj); return (int64_t)(*var); };
  m_BasicInt64.m_SignedNumber.Set = [](void * obj, int64_t val) { auto var = static_cast<RNumber<int64_t> *>(obj); (*var) = (int64_t)val; };
  m_BasicInt64.m_SignedNumber.m_Min = INT64_MIN;
  m_BasicInt64.m_SignedNumber.m_Max = INT64_MAX;

  m_BasicUInt8.m_Type = PropertyFieldType::kUnsignedNumber;
  m_BasicUInt8.m_UnsignedNumber.Get = [](void * obj) -> uint64_t { auto var = static_cast<RNumber<uint8_t> *>(obj); return (uint8_t)(*var); };
  m_BasicUInt8.m_UnsignedNumber.Set = [](void * obj, uint64_t val) { auto var = static_cast<RNumber<uint8_t> *>(obj); (*var) = (uint8_t)val; };
  m_BasicUInt8.m_UnsignedNumber.m_Min = 0;
  m_BasicUInt8.m_UnsignedNumber.m_Max = UINT8_MAX;

  m_BasicUInt16.m_Type = PropertyFieldType::kUnsignedNumber;
  m_BasicUInt16.m_UnsignedNumber.Get = [](void * obj) -> uint64_t { auto var = static_cast<RNumber<uint16_t> *>(obj); return (uint16_t)(*var); };
  m_BasicUInt16.m_UnsignedNumber.Set = [](void * obj, uint64_t val) { auto var = static_cast<RNumber<uint16_t> *>(obj); (*var) = (uint16_t)val; };
  m_BasicUInt16.m_UnsignedNumber.m_Min = 0;
  m_BasicUInt16.m_UnsignedNumber.m_Max = UINT16_MAX;

  m_BasicUInt32.m_Type = PropertyFieldType::kUnsignedNumber;
  m_BasicUInt32.m_UnsignedNumber.Get = [](void * obj) -> uint64_t { auto var = static_cast<RNumber<uint32_t> *>(obj); return (uint32_t)(*var); };
  m_BasicUInt32.m_UnsignedNumber.Set = [](void * obj, uint64_t val) { auto var = static_cast<RNumber<uint32_t> *>(obj); (*var) = (uint32_t)val; };
  m_BasicUInt32.m_UnsignedNumber.m_Min = 0;
  m_BasicUInt32.m_UnsignedNumber.m_Max = UINT32_MAX;

  m_BasicUInt64.m_Type = PropertyFieldType::kUnsignedNumber;
  m_BasicUInt64.m_UnsignedNumber.Get = [](void * obj) -> uint64_t { auto var = static_cast<RNumber<uint64_t> *>(obj); return (uint64_t)(*var); };
  m_BasicUInt64.m_UnsignedNumber.Set = [](void * obj, uint64_t val) { auto var = static_cast<RNumber<uint64_t> *>(obj); (*var) = (uint64_t)val; };
  m_BasicUInt64.m_UnsignedNumber.m_Min = 0;
  m_BasicUInt64.m_UnsignedNumber.m_Max = UINT64_MAX;

  m_BasicFloat.m_Type = PropertyFieldType::kFloatNumber;
  m_BasicFloat.m_FloatNumber.Get = [](void * obj) -> float { auto var = static_cast<RNumber<float> *>(obj); return (float)(*var); };
  m_BasicFloat.m_FloatNumber.Set = [](void * obj, float val) { auto var = static_cast<RNumber<float> *>(obj); (*var) = (float)val; };
  m_BasicFloat.m_FloatNumber.m_Min = -FLT_MAX;
  m_BasicFloat.m_FloatNumber.m_Max = FLT_MAX;

  m_BasicDouble.m_Type = PropertyFieldType::kFloatNumber;
  m_BasicDouble.m_FloatNumber.Get = [](void * obj) -> float { auto var = static_cast<RNumber<double> *>(obj); return (float)(*var); };
  m_BasicDouble.m_FloatNumber.Set = [](void * obj, float val) { auto var = static_cast<RNumber<double> *>(obj); (*var) = (double)val; };
  m_BasicDouble.m_FloatNumber.m_Min = (float)-DBL_MAX;
  m_BasicDouble.m_FloatNumber.m_Max = (float)DBL_MAX;

  m_BasicFloatDeterministic.m_Type = PropertyFieldType::kFloatNumberDeterministic;
  m_BasicFloatDeterministic.m_FloatNumberDeterministic.Get = [](void * obj) -> czstr { auto var = static_cast<RDeterministicFloatBase *>(obj); return var->GetStr(); };
  m_BasicFloatDeterministic.m_FloatNumberDeterministic.Set = [](void * obj, czstr val) { auto var = static_cast<RDeterministicFloatBase *>(obj); (*var) = val; };
  m_BasicFloatDeterministic.m_FloatNumberDeterministic.m_Min = -FLT_MAX;
  m_BasicFloatDeterministic.m_FloatNumberDeterministic.m_Max = FLT_MAX;

  m_BasicString.m_Type = PropertyFieldType::kString;
  m_BasicString.m_String.m_MaxLength = 0;
}

PropertyField * PropertyFieldDatabase::GetUnknownField()
{
  return &m_Unknown;
}

PropertyField * PropertyFieldDatabase::GetBasicField(PropertyFieldType type)
{
  switch (type)
  {
  case PropertyFieldType::kBool:
    return &m_BasicBool;
  case PropertyFieldType::kString:
    return &m_BasicString;
  case PropertyFieldType::kFloatNumberDeterministic:
    return &m_BasicFloatDeterministic;
  default:
    return nullptr;
  }
}

PropertyField * PropertyFieldDatabase::GetBasicSignedField(int size)
{
  switch (size)
  {
  case 1:
    return &m_BasicInt8;
  case 2:
    return &m_BasicInt16;
  case 4:
    return &m_BasicInt32;
  case 8:
    return &m_BasicInt64;
  default:
    return nullptr;
  }
}

PropertyField * PropertyFieldDatabase::GetBasicUnsignedField(int size)
{
  switch (size)
  {
  case 1:
    return &m_BasicUInt8;
  case 2:
    return &m_BasicUInt16;
  case 4:
    return &m_BasicUInt32;
  case 8:
    return &m_BasicUInt64;
  default:
    return nullptr;
  }
}

PropertyField * PropertyFieldDatabase::GetBasicFloatField(int size)
{
  switch (size)
  {
  case 4:
    return &m_BasicFloat;
  case 8:
    return &m_BasicDouble;
  default:
    return nullptr;
  }
}

PropertyField * PropertyFieldDatabase::AllocateField()
{
  m_PropertyAlloc.emplace_back(std::make_unique<PropertyField>());
  return m_PropertyAlloc.back().get();
}

std::pair<bool, PropertyField *> PropertyFieldDatabase::GetEnumData(uint32_t enum_hash)
{
  auto itr = m_EnumField.find(enum_hash);
  if (itr == m_EnumField.end())
  {
    m_EnumData.emplace_back(std::make_unique<PropertyFieldEnumData>());
    auto enum_data = m_EnumData.back().get();

    auto field = AllocateField();
    field->m_Type = PropertyFieldType::kEnum;
    field->m_Enum.m_EnumData = enum_data;

    auto result = m_EnumField.emplace(std::make_pair(enum_hash, field));
    return std::make_pair(true, field);
  }

  return std::make_pair(false, itr->second);
}

std::pair<bool, PropertyField *> PropertyFieldDatabase::GetPolyData(uint32_t base_type_hash)
{
  auto itr = m_PolyField.find(base_type_hash);
  if (itr == m_PolyField.end())
  {
    m_PolyData.emplace_back(std::make_unique<PropertyFieldPolymorphicData>());
    auto poly_data = m_PolyData.back().get();

    auto field = AllocateField();
    field->m_Type = PropertyFieldType::kPolymorphic;
    field->m_Poly.m_PolyData = poly_data;

    auto result = m_PolyField.emplace(std::make_pair(base_type_hash, field));
    return std::make_pair(true, field);
  }

  return std::make_pair(false, itr->second);
}

std::pair<bool, PropertyField *> PropertyFieldDatabase::GetStructData(uint32_t type_name_hash)
{
  auto itr = m_StructField.find(type_name_hash);
  if (itr == m_StructField.end())
  {
    m_StructData.emplace_back(std::make_unique<PropertyFieldStructData>());
    auto struct_data = m_StructData.back().get();
    struct_data->m_TypeNameHash = type_name_hash;

    auto field = AllocateField();
    field->m_Type = PropertyFieldType::kStruct;
    field->m_Struct.m_StructData = struct_data;

    auto result = m_StructField.emplace(std::make_pair(type_name_hash, field));
    return std::make_pair(true, field);
  }

  return std::make_pair(false, itr->second);
}

PropertyField * PropertyFieldDatabase::FindStructData(uint32_t type_name_hash) const
{
  auto itr = m_StructField.find(type_name_hash);
  if (itr == m_StructField.end())
  {
    return nullptr;
  }

  return itr->second;
}

void PropertyFieldDatabase::RegisterStructWithAlternateName(uint32_t type_name_hash, PropertyField * prop)
{
  auto itr = m_StructField.find(type_name_hash);
  if (itr == m_StructField.end())
  {
    m_StructField.emplace(std::make_pair(type_name_hash, prop));
  }
}
