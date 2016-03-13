// UnitTests.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "Reflection\Reflection.h"

struct Person
{
  Person(const char *name, int age)
    :
    name(name),
    age(age)
  {
  }
public:
  REFLECTABLE
    (
      (const char *)name,
      (int)age
      )
};

struct print_visitor
{
  template<class FieldData>
  void operator()(FieldData f)
  {
    std::cout << f.name() << "=" << f.get() << std::endl;
  }
};

template<class T>
void print_fields(T & x)
{
  visit_each(x, print_visitor());
}

int main()
{
  Person p("Tom", 82);
  print_fields(p);
  return 0;
}


