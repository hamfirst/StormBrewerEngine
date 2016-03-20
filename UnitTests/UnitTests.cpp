// UnitTests.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

#include "Reflection\Reflection.h"

struct Inventory
{
public:
  REFLECTABLE(
    ((std::vector<int>), (items))
    )
};

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
      ((const char *), (name)),
      ((int), (age)),
      ((Inventory), (inv))
      )
};

struct member_printer
{
  template <class T, typename std::enable_if<std::is_class<T>::value>::type * = 0>
  void print(const char * name, const char * type, const T value)
  {
    std::cout << name << " " << type << std::endl;
    print_fields(value);
  }

  template <class T, typename std::enable_if<std::is_arithmetic<T>::value>::type * = 0>
  void print(const char * name, const char * type, const T value)
  {
    std::cout << name << " " << type << " = " << value << std::endl;
  }

  template <class Enable = void>
  void print(const char * name, const char * type, const char * value)
  {
    std::cout << name << " " << type << " = " << value << std::endl;
  }

  template <class T, class Enable = void>
};

struct print_visitor
{
  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    member_printer printer;
    printer.print(f.name(), f.type(), f.get());
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


