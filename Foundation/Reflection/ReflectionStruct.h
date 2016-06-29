#pragma once

#include "Foundation\Reflection\Reflection.h"


// A helper metafunction for adding const to a type
template<class M, class T>
struct make_const
{
  typedef T type;
};

#define MEMBER_EAT(__VAR_ARGS__) __VAR_ARGS__

#define MEMBER_OP (
#define MEMBER_CP )
#define MEMBER_DECL(x) MEMBER_DECL_EXCTRACT x
#define MEMBER_TYPE(x) MEMBER_TYPE_EXCTRACT x 
#define MEMBER_NAME(x) MEMBER_NAME_EXCTRACT x 
#define MEMBER_TYPE_STR(x) MEMBER_TYPE_EXCTRACT_STR x
#define MEMBER_NAME_STR(x) MEMBER_NAME_EXCTRACT_STR x 

#define MEMBER_DECL_EXCTRACT(X, Y, ...) Y X
#define MEMBER_TYPE_EXCTRACT(X, Y, ...) Y
#define MEMBER_NAME_EXCTRACT(X, Y, ...) X
#define MEMBER_TYPE_EXCTRACT_STR(X, Y, ...) BOOST_PP_STRINGIZE(Y)
#define MEMBER_NAME_EXCTRACT_STR(X, Y, ...) BOOST_PP_STRINGIZE MEMBER_OP X MEMBER_CP

template <class M, class T>
struct match_ref
{
  typedef typename std::conditional_t<
    std::is_reference<M>::value,
    typename std::add_lvalue_reference_t<T>,
    typename std::remove_reference_t<T>
  > type;
};

template <class M, class T>
using match_ref_t = typename match_ref<M, T>::type;

template <class M, class T>
struct match_const
{
  typedef typename std::conditional_t<
    std::is_const<typename std::remove_reference_t<M>>::value,
    typename match_ref_t<T, typename std::add_const_t<typename std::remove_reference_t<T>>>,
    typename match_ref_t<T, typename std::remove_const_t<typename std::remove_reference_t<T>>>
  > type;
};

template <class M, class T>
using match_const_t = typename match_const<M, T>::type;

#define REFL_MEMBERS(...) \
static constexpr int fields_n = BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
static constexpr bool is_reflectable = true; \
const auto & GetDefault() const { static std::remove_reference<decltype(*this)>::type def; return def; } \
Hash GetTypeNameHash() const { return crc32(typeid(*this).name()); }\
template <class C> \
bool operator == (const C & c) const \
{\
  const C & me = *this;\
  return CompareFields(me, c);\
}\
friend struct reflector; \
REFLECTION_CHANGE_NOTIFIER_INFO \
template<int N>\
struct field_data_static {}; \
template<int N, class Self> \
struct field_data {}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


#define REFLECT_EACH(r, data, i, x) \
MEMBER_DECL(x) = {}; \
template<> \
struct field_data_static<i> \
{ \
  typedef MEMBER_TYPE(x) member_type; \
  czstr GetName() const \
  {\
    return MEMBER_NAME_STR(x); \
  }\
  constexpr Hash GetNameHash() const \
  {\
    return COMPILE_TIME_CRC32_STR(MEMBER_NAME_STR(x)); \
  }\
  czstr GetType() const \
  {\
    return MEMBER_TYPE_STR(x); \
  }\
  const int GetFieldIndex() const \
  {\
    return i;\
  }\
};\
template<class Self> \
struct field_data<i, Self> : field_data_static<i> \
{ \
  Self & self; \
  field_data(Self & self) : self(self) {} \
  \
  typename match_const_t<Self, MEMBER_TYPE(x)> & Get() \
  { \
    return self.MEMBER_NAME(x); \
  }\
  typename std::add_const_t<typename std::remove_reference_t<MEMBER_TYPE(x)>> & Get() const \
  { \
    return self.MEMBER_NAME(x); \
  }\
  void SetDefault() \
  {\
    self.MEMBER_NAME(x) = self.GetDefault().MEMBER_NAME(x); \
  }\
};\

#define REFL_MEMBERS_DERIVED(BaseClass, ...) \
using MyBase = BaseClass; \
static constexpr int fields_n = MyBase::fields_n + BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
const auto & GetDefault() const { static std::remove_reference<decltype(*this)>::type def; return def; } \
Hash GetTypeNameHash() const { return crc32(typeid(*this).name()); }\
template <class C> \
bool operator == (const C & c) const \
{\
  const C & me = *this;\
  return CompareFields(me, c);\
}\
friend struct reflector; \
template<int N> \
struct field_data_static \
{ \
  typedef MyBase::field_data_static<N> parent_type; \
  parent_type parent_val; \
  typedef typename MyBase::field_data_static<N>::member_type member_type; \
  czstr GetName() const { return parent_val.GetName(); } \
  constexpr Hash GetNameHash() const { return parent_val.GetNameHash(); } \
  czstr GetType() const { return parent_val.GetType(); } \
  int GetFieldIndex() const { return parent_val.GetFieldIndex(); } \
}; \
template<int N, class Self> \
struct field_data : public field_data_static<N> \
{ \
  typedef MyBase::field_data<N, typename match_const_t<Self, MyBase>> parent_type; \
  MyBase::field_data<N, typename match_const_t<Self, MyBase>> parent_val; \
  field_data(Self & self) : parent_val(self) {} \
  decltype(auto) Get() { return parent_val.Get(); } \
  decltype(auto) Get() const { return parent_val.Get(); } \
  void SetDefault() { parent_val.SetDefault(); } \
}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH_DERIVED, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


#define REFLECT_EACH_DERIVED(r, data, i, x) \
MEMBER_DECL(x) = {}; \
template<> \
struct field_data_static<MyBase::fields_n + i> \
{ \
  czstr GetName() const \
  {\
    return MEMBER_NAME_STR(x); \
  }\
  constexpr Hash GetNameHash() const \
  {\
    return COMPILE_TIME_CRC32_STR(MEMBER_NAME_STR(x)); \
  }\
  czstr GetType() const \
  {\
    return MEMBER_TYPE_STR(x); \
  }\
  const int GetFieldIndex() const \
  {\
    return MyBase::fields_n + i;\
  }\
};\
template<class Self> \
struct field_data<MyBase::fields_n + i, Self> : field_data_static<MyBase::fields_n + i> \
{ \
  Self & self; \
  typedef MEMBER_TYPE(x) member_type; \
  field_data(Self & self) : self(self) {} \
  \
  typename match_const_t<Self, MEMBER_TYPE(x)> & Get() \
  { \
    return self.MEMBER_NAME(x); \
  }\
  typename std::add_const_t<typename std::remove_reference_t<MEMBER_TYPE(x)>> & Get() const \
  { \
    return self.MEMBER_NAME(x); \
  }\
  void SetDefault() \
  {\
    self.MEMBER_NAME(x) = self.GetDefault().MEMBER_NAME(x); \
  }\
};\

template <class C, class Visitor, int I>
struct FieldIterator
{
  void operator()(C& c, Visitor & v)
  {
    auto f = C::field_data<C::fields_n - I, C>(c);
    v(f);
    FieldIterator <C, Visitor, I - 1>() (c, v);
  }
};

template <class C, class Visitor>
struct FieldIterator<C, Visitor, 0>
{
  void operator()(C& c, Visitor & v)
  {

  }
};

template <class C, class Visitor, int I>
struct FieldSelector
{
  void operator()(C& c, Visitor & v, Hash field_name_hash)
  {
    auto f = C::field_data<C::fields_n - I, C>(c);

    if (f.GetNameHash() == field_name_hash)
    {
      v(f);
      return;
    }

    FieldSelector <C, Visitor, I - 1>() (c, v, field_name_hash);
  }
};

template <class C, class Visitor>
struct FieldSelector<C, Visitor, 0>
{
  void operator()(C& c, Visitor & v, Hash field_name_hash)
  {

  }
};

template <class C, class Visitor, int I>
struct FieldExaminer
{
  void operator()(Visitor & v)
  {
    auto f = C::field_data_static<C::fields_n - I>();
    v(f);
    FieldExaminer <C, Visitor, I - 1>() (v);
  }
};

template <class C, class Visitor>
struct FieldExaminer<C, Visitor, 0>
{
  void operator()(Visitor & v)
  {

  }
};

template <class C, int I>
struct FieldComparer
{
  bool operator()(const C& c1, const C& c2)
  {
    auto f1 = C::field_data<C::fields_n - I, const C>(c1);
    auto f2 = C::field_data<C::fields_n - I, const C>(c2);
    if (f1.Get() == f2.Get())
    {
      return FieldComparer<C, I - 1>() (c1, c2);
    }

    return false;
  }
};

template <class C>
struct FieldComparer<C, 0>
{
  bool operator()(C& c1, C& c2)
  {
    return true;
  }
};

template<class C, class Visitor>
void VisitEach(C & c, Visitor & v)
{
  FieldIterator<C, Visitor, C::fields_n> itr;
  itr(c, v);
}

template<class C, class Visitor>
void VisitField(C & c, Visitor & v, Hash field_name_hash)
{
  FieldSelector<C, Visitor, C::fields_n> itr;
  itr(c, v, field_name_hash);
}

template<class C, class Visitor>
void ExamineFields(Visitor & v)
{
  FieldExaminer<C, Visitor, C::fields_n> itr;
  itr(v);
}

template<class C>
bool CompareFields(C & c1, C & c2)
{
  FieldComparer<C, C::fields_n> itr;
  return itr(c1, c2);
}

template <class C>
void SetValueDefault(C & c, Hash field_name_hash)
{
  VisitField(c, [](auto field_data) { field_data.SetDefault(); }, field_name_hash);
}

template <class C>
std::vector<std::string> GetFields()
{
  std::vector<std::string> fields;
  auto visitor = [&](auto field_data) { fields.push_back(field_data.GetName()); };

  ExamineFields<C, decltype(visitor)>(visitor);
  return fields;
}

template <class C>
czstr GetFieldName(int index)
{
  czstr name = nullptr;
  auto visitor = [&](auto field_data) { if (field_data.GetFieldIndex() == index) name = field_data.GetName(); };

  ExamineFields<C, decltype(visitor)>(visitor);
  return name;
}
