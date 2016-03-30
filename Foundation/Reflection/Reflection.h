#pragma once

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>


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

#define MEMBER_DECL_EXCTRACT(X, ...) __VA_ARGS__ X
#define MEMBER_TYPE_EXCTRACT(X, ...) __VA_ARGS__
#define MEMBER_NAME_EXCTRACT(X, ...) X
#define MEMBER_TYPE_EXCTRACT_STR(X, ...) #__VA_ARGS__
#define MEMBER_NAME_EXCTRACT_STR(X, ...) BOOST_PP_STRINGIZE MEMBER_OP X MEMBER_CP

template<class M, class T>
struct make_const<const M, T>
{
  typedef typename std::add_const<T>::type type;
};


#define REFL_MEMBERS(...) \
static const int fields_n = BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
static const bool is_reflectable = true; \
friend struct reflector; \
template<int N, class Self> \
struct field_data {}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define REFLECT_EACH(r, data, i, x) \
MEMBER_DECL(x); \
template<class Self> \
struct field_data<i, Self> \
{ \
    Self & self; \
    typedef MEMBER_TYPE(x) member_type; \
    field_data(Self & self) : self(self) {} \
    \
    typename make_const<Self, MEMBER_TYPE(x)>::type & get() \
    { \
        return self.MEMBER_NAME(x); \
    }\
    typename std::add_const<MEMBER_TYPE(x)>::type & get() const \
    { \
        return self.MEMBER_NAME(x); \
    }\
    const char * name() const \
    {\
        return MEMBER_NAME_STR(x); \
    }\
    const char * type() const \
    {\
        return MEMBER_TYPE_STR(x); \
    }\
}; \

template <class C, class Visitor, int I>
struct field_iterator
{
  void operator()(C& c, Visitor v)
  {
    auto f = C::field_data<I - 1, C>(c);
    v.operator()<C::field_data<I - 1, C>, C::field_data<I - 1, C>::member_type>(f);
    field_iterator <C, Visitor, I - 1>() (c, v);
  }
};

template <class C, class Visitor>
struct field_iterator<C, Visitor, 0>
{
  void operator()(C& c, Visitor v)
  {

  }
};

template<class C, class Visitor>
void visit_each(C & c, Visitor v)
{
  field_iterator<C, Visitor, C::fields_n> itr;
  itr.operator()(c, v);
}
