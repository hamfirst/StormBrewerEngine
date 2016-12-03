#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "TestTypes.refl.h"


template <>
struct StormReflTypeInfo<SubType>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SubType"; }
  static constexpr auto GetNameHash() { return 0x3AE4B300; }
  static SubType & GetDefault() { static SubType def; return def; }
};

template <>
struct StormReflTypeInfo<SubType>::field_data_static<0>
{
  using member_type = RSparseList<RInt>; // RSparseList<RNumber<int> >
  static constexpr auto GetName() { return "m_List"; }
  static constexpr auto GetType() { return "RSparseList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A556D07; }
  static constexpr unsigned GetTypeNameHash() { return 0xDF8E4478; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SubType::m_List; }
};

template <typename Self>
struct StormReflTypeInfo<SubType>::field_data<0, Self> : public StormReflTypeInfo<SubType>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<RInt>> & Get() { return self.m_List; }
  std::add_const_t<std::remove_reference_t<RSparseList<RInt>>> & Get() const { return self.m_List; }
  void SetDefault() { self.m_List = StormReflTypeInfo<SubType>::GetDefault().m_List; }
};

template <>
struct StormReflTypeInfo<TestType>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "TestType"; }
  static constexpr auto GetNameHash() { return 0xE18C5F7C; }
  static TestType & GetDefault() { static TestType def; return def; }
};

template <>
struct StormReflTypeInfo<TestType>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Int"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7B31E56; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &TestType::m_Int; }
};

template <typename Self>
struct StormReflTypeInfo<TestType>::field_data<0, Self> : public StormReflTypeInfo<TestType>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Int; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Int; }
  void SetDefault() { self.m_Int = StormReflTypeInfo<TestType>::GetDefault().m_Int; }
};

template <>
struct StormReflTypeInfo<TestType>::field_data_static<1>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_Float"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4493CEF5; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &TestType::m_Float; }
};

template <typename Self>
struct StormReflTypeInfo<TestType>::field_data<1, Self> : public StormReflTypeInfo<TestType>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_Float; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_Float; }
  void SetDefault() { self.m_Float = StormReflTypeInfo<TestType>::GetDefault().m_Float; }
};

template <>
struct StormReflTypeInfo<TestType>::field_data_static<2>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_List"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7A556D07; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &TestType::m_List; }
};

template <typename Self>
struct StormReflTypeInfo<TestType>::field_data<2, Self> : public StormReflTypeInfo<TestType>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_List; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_List; }
  void SetDefault() { self.m_List = StormReflTypeInfo<TestType>::GetDefault().m_List; }
};

template <>
struct StormReflTypeInfo<TestType>::field_data_static<3>
{
  using member_type = SubType; // SubType
  static constexpr auto GetName() { return "m_Sub"; }
  static constexpr auto GetType() { return "SubType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xABE0463B; }
  static constexpr unsigned GetTypeNameHash() { return 0x3AE4B300; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &TestType::m_Sub; }
};

template <typename Self>
struct StormReflTypeInfo<TestType>::field_data<3, Self> : public StormReflTypeInfo<TestType>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, SubType> & Get() { return self.m_Sub; }
  std::add_const_t<std::remove_reference_t<SubType>> & Get() const { return self.m_Sub; }
  void SetDefault() { self.m_Sub = StormReflTypeInfo<TestType>::GetDefault().m_Sub; }
};

namespace StormReflFileInfo
{
  struct TestTypes
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct TestTypes::type_info<0>
  {
    using type = ::SubType;
  };

  template <>
  struct TestTypes::type_info<1>
  {
    using type = ::TestType;
  };

}

