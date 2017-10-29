#pragma once

#include "PropertyFieldMetaData.h"
#include "PropertyFieldDatabase.h"

#include <StormRefl/StormReflMetaEnum.h>

template <typename T>
PropertyField * GetProperyMetaData(PropertyFieldDatabase & property_db);

template <typename T, typename SurroundingType, typename FieldData>
PropertyField * GetProperyMetaData(PropertyFieldDatabase & property_db, FieldData field_data);

template <typename T, bool>
struct PropertyMetaDataStruct
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetUnknownField();
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <typename T>
struct PropertyMetaDataStruct<T, true>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    auto struct_data = property_db.GetStructData(StormReflTypeInfo<T>::GetNameHash());
    if (struct_data.first)
    {
      auto & list = struct_data.second->m_Struct.m_StructData->m_Members;
      auto visitor = [&](auto f)
      {
        using FieldDataType = typename std::decay_t<decltype(f)>;

        if (StormReflHasAnnotation<T, FieldDataType::GetFieldIndex()>("noui"))
        {
          return;
        }

        PropertyFieldStructMemberData member_data;
        member_data.m_Name = FieldDataType::GetName();
        member_data.m_FieldData = GetProperyMetaData<typename FieldDataType::member_type, T, FieldDataType>(property_db, f);
        member_data.GetMember = [](void * obj) -> void * { T * t = static_cast<T *>(obj); auto ptr = FieldDataType::GetMemberPtr(); auto & val = t->*ptr; return &val;  };

        list.emplace_back(std::move(member_data));
      };

      T crap;
      StormReflVisitEach(crap, visitor);
    }

    return struct_data.second;
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};


template <typename T>
struct PropertyMetaData : PropertyMetaDataStruct<T, StormDataCheckReflectable<T>::value>
{

};

template <>
struct PropertyMetaData<RBool>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicField(PropertyFieldType::kBool);
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <typename T>
struct PropertyMetaDataSigned
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicSignedField(sizeof(T));
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    auto min = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("min");
    auto max = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("max");

    auto basic = &property_db.GetBasicSignedField(sizeof(T))->m_SignedNumber;

    if (min || max)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kSignedNumber;
      field->m_SignedNumber.Get = basic->Get;
      field->m_SignedNumber.Set = basic->Set;
      field->m_SignedNumber.m_Min = min ? std::max((int64_t)atol(min), basic->m_Min) : basic->m_Min;
      field->m_SignedNumber.m_Max = max ? std::min((int64_t)atol(max), basic->m_Max) : basic->m_Max;
      return field;
    }

    return GetMetaData(property_db);
  }
};

template <>
struct PropertyMetaData<RNumber<int8_t>> : PropertyMetaDataSigned<int8_t>
{

};

template <>
struct PropertyMetaData<RNumber<int16_t>> : PropertyMetaDataSigned<int16_t>
{

};

template <>
struct PropertyMetaData<RNumber<int32_t>> : PropertyMetaDataSigned<int32_t>
{

};

template <>
struct PropertyMetaData<RNumber<int64_t>> : PropertyMetaDataSigned<int64_t>
{

};

template <typename T>
struct PropertyMetaDataUnsigned
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicUnsignedField(sizeof(T));
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    auto min = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("min");
    auto max = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("max");

    auto basic = &property_db.GetBasicUnsignedField(sizeof(T))->m_UnsignedNumber;

    if (min || max)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kUnsignedNumber;
      field->m_UnsignedNumber.Get = basic->Get;
      field->m_UnsignedNumber.Set = basic->Set;
      field->m_UnsignedNumber.m_Min = min ? std::max((uint64_t)atol(min), basic->m_Min) : basic->m_Min;
      field->m_UnsignedNumber.m_Max = max ? std::min((uint64_t)atoi(max), basic->m_Max) : basic->m_Max;
      return field;
    }

    return GetMetaData(property_db);
  }
};

template <>
struct PropertyMetaData<RNumber<uint8_t>> : PropertyMetaDataUnsigned<uint8_t>
{

};

template <>
struct PropertyMetaData<RNumber<uint16_t>> : PropertyMetaDataUnsigned<uint16_t>
{

};

template <>
struct PropertyMetaData<RNumber<uint32_t>> : PropertyMetaDataUnsigned<uint32_t>
{

};

template <>
struct PropertyMetaData<RNumber<uint64_t>> : PropertyMetaDataUnsigned<uint64_t>
{

};

template <typename T>
struct PropertyMetaDataFloat
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicFloatField(sizeof(T));
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    auto min = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("min");
    auto max = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("max");

    auto basic = &property_db.GetBasicFloatField(sizeof(T))->m_FloatNumber;

    if (min || max)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kFloatNumber;
      field->m_FloatNumber.Get = basic->Get;
      field->m_FloatNumber.Set = basic->Set;
      field->m_FloatNumber.m_Min = min ? std::max((float)atof(min), basic->m_Min) : basic->m_Min;
      field->m_FloatNumber.m_Max = max ? std::min((float)atof(max), basic->m_Max) : basic->m_Max;
      return field;
    }

    return GetMetaData(property_db);
  }
};


template <>
struct PropertyMetaData<RNumber<float>> : PropertyMetaDataFloat<float>
{

};

template <>
struct PropertyMetaData<RNumber<double>> : PropertyMetaDataFloat<double>
{

};

template <>
struct PropertyMetaData<RDeterministicFloat>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicField(PropertyFieldType::kFloatNumberDeterministic);
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    auto min = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("min");
    auto max = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("max");

    auto basic = &property_db.GetBasicField(PropertyFieldType::kFloatNumberDeterministic)->m_FloatNumberDeterministic;

    if (min || max)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kFloatNumberDeterministic;
      field->m_FloatNumberDeterministic.Get = basic->Get;
      field->m_FloatNumberDeterministic.Set = basic->Set;
      field->m_FloatNumberDeterministic.m_Min = min ? std::max((float)atof(min), basic->m_Min) : basic->m_Min;
      field->m_FloatNumberDeterministic.m_Max = max ? std::min((float)atof(max), basic->m_Max) : basic->m_Max;
      return field;
    }

    return GetMetaData(property_db);
  }
};

template <>
struct PropertyMetaData<RString>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetBasicField(PropertyFieldType::kString);
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    auto file = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("file");
    if (file)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kFile;
      field->m_File.m_Extension = file;
      return field;
    }

    auto max = StormReflGetAnnotationValue<SurroundingType, FieldData::GetFieldIndex()>("max");

    if (max)
    {
      auto field = property_db.AllocateField();
      field->m_Type = PropertyFieldType::kString;
      field->m_String.m_MaxLength = atoi(max);
      return field;
    }

    return GetMetaData(property_db);
  }
};

template <typename T>
struct PropertyMetaData<REnum<T>>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    auto enum_data = property_db.GetEnumData(StormReflEnumInfo<T>::GetNameHash());
    if (enum_data.first)
    {
      auto & values = enum_data.second->m_Enum.m_EnumData->m_PossibleValues;

      auto visitor = [&](auto f)
      {
        values.emplace_back(std::make_pair((uint64_t)f.GetValue(), f.GetName()));
      };

      StormReflVisitEnumValues<T>::VisitEach(visitor);

      enum_data.second->m_Enum.Get = [](void * en) -> czstr { REnum<T> * elem = static_cast<REnum<T> *>(en); return StormReflGetEnumAsString(*(T *)(en)); };
      enum_data.second->m_Enum.Set = [](void * en, czstr val) { REnum<T> * elem = static_cast<REnum<T> *>(en); T t; if (StormReflGetEnumFromHash(t, crc32(val))) { *elem = t; }};
    }

    return enum_data.second;
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <typename T>
struct PropertyMetaData<ROpaque<T>>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetUnknownField();
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <typename ListType, typename T>
struct PropertyMetaDataList
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    auto field = property_db.AllocateField();
    field->m_Type = PropertyFieldType::kList;

    field->m_List.m_ListData = GetProperyMetaData<T>(property_db);
    field->m_List.GetElement = [](void * obj, std::size_t index) -> void * { auto l = static_cast<ListType *>(obj); return &(*l)[(int)index]; };
    field->m_List.Insert = [](void * obj, std::size_t index) { auto l = static_cast<ListType *>(obj); l->EmplaceAt(index); };
    field->m_List.Remove = [](void * obj, std::size_t index) { auto l = static_cast<ListType *>(obj); l->RemoveAt(index); };
    field->m_List.Append = [](void * obj) { auto l = static_cast<ListType *>(obj); l->EmplaceBack(); return (std::size_t)l->HighestIndex(); };

    field->m_List.GetElementIndices = [](void * obj)
    {
      std::vector<std::size_t> indices;

      auto l = static_cast<ListType *>(obj);
      for (auto elem : *l)
      {
        indices.push_back(elem.first);
      }

      return indices;
    };

    return field;
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};


template <typename T>
struct PropertyMetaData<RMergeList<T>> : PropertyMetaDataList<RMergeList<T>, T>
{

};

template <typename T>
struct PropertyMetaData<RSparseList<T>> : PropertyMetaDataList<RSparseList<T>, T>
{

};

template <typename K, typename T>
struct PropertyMetaData<RMap<K, T>>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    return property_db.GetUnknownField();
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <class Base, class TypeDatabase, class TypeInfo, bool DefaultFirstNonBase>
struct PropertyMetaData<RPolymorphic<Base, TypeDatabase, TypeInfo, DefaultFirstNonBase>>
{
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db)
  {
    auto poly_data = property_db.GetPolyData(crc32(StormReflTypeInfo<Base>::GetName()));

    if (poly_data.first)
    {
      auto & list = poly_data.second->m_Poly.m_PolyData;
      auto visitor = [&](uint32_t type_name_hash, const TypeInfo & type_info)
      {
        PropertyFieldPolymorphicOptionData option;
        option.m_Name = type_info.m_Name;
        option.m_NameHash = type_name_hash;
        option.m_FieldData = type_info.RegisterPropertyFields(property_db);
        list->m_PossibleValues.emplace_back(std::move(option));
      };

      StormDataTypeDatabaseVisitTypes(typename TypeDatabase::VisitorInfo{}, visitor);

      poly_data.second->m_Poly.GetType = 
        [](void * obj) { auto * p = static_cast<RPolymorphic<Base, TypeDatabase, TypeInfo, DefaultFirstNonBase> *>(obj); return p->GetTypeNameHash(); };
      poly_data.second->m_Poly.SetType = 
        [](void * obj, uint32_t type) { auto * p = static_cast<RPolymorphic<Base, TypeDatabase, TypeInfo, DefaultFirstNonBase> *>(obj); p->SetTypeFromNameHash(type); };
      poly_data.second->m_Poly.GetValue = 
        [](void * obj) -> void * { auto * p = static_cast<RPolymorphic<Base, TypeDatabase, TypeInfo, DefaultFirstNonBase> *>(obj); return p->GetValue(); };

    };

    return poly_data.second;
  }

  template <typename SurroundingType, typename FieldData>
  static PropertyField * GetMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
  {
    return GetMetaData(property_db);
  }
};

template <typename T>
PropertyField * GetProperyMetaData(PropertyFieldDatabase & property_db)
{
  return PropertyMetaData<T>::GetMetaData(property_db);
}

template <typename T, typename SurroundingType, typename FieldData>
PropertyField * GetProperyMetaData(PropertyFieldDatabase & property_db, FieldData field_data)
{
  return PropertyMetaData<T>::template GetMetaData<SurroundingType, FieldData>(property_db, field_data);
}
