#pragma once

#include "stdafx.h"

#include <type_traits>
#include <functional>
#include <algorithm>

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/stringize.hpp>


#define REM(...) __VA_ARGS__
#define EAT(...)

// Retrieve the type
#define TYPEOF(x) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE x,)
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#define DETAIL_TYPEOF_HEAD(x, ...) REM x
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),
// Strip off the type
#define STRIP(x) EAT x
// Show the type without parenthesis
#define PAIR(x) REM x

// A helper metafunction for adding const to a type
template<class M, class T>
struct make_const
{
  typedef T type;
};

template<class M, class T>
struct make_const<const M, T>
{
  typedef typename std::add_const<T>::type type;
};


#define REFLECTABLE(...) \
static const int fields_n = BOOST_PP_VARIADIC_SIZE(__VA_ARGS__); \
friend struct reflector; \
template<int N, class Self> \
struct field_data {}; \
BOOST_PP_SEQ_FOR_EACH_I(REFLECT_EACH, data, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define REFLECT_EACH(r, data, i, x) \
PAIR(x); \
template<class Self> \
struct field_data<i, Self> \
{ \
    Self & self; \
    field_data(Self & self) : self(self) {} \
    \
    typename make_const<Self, decltype(x)>::type & get() \
    { \
        return self.STRIP(x); \
    }\
    typename std::add_const<decltype(x)>::type & get() const \
    { \
        return self.STRIP(x); \
    }\
    const char * name() const \
    {\
        return BOOST_PP_STRINGIZE(STRIP(x)); \
    } \
}; \

template <class C, class Visitor, int I>
struct field_iterator
{
  void operator()(C& c, Visitor v)
  {
    auto f = C::field_data<I - 1, C>(c);
    v(f);
    field_iterator < C, Visitor, I - 1 >() (c, v);
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
