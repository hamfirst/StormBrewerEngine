// UnitTests.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <functional>

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionJson.h"

REFL_ENUM(TestEnum, int, kA, kB, kC);

struct Inventory
{
  Inventory()
  {
    items.push_back(20);
  }

public:
  REFL_MEMBERS
  (
    (items, r_list<int>)
  )
};

struct Person
{
  Person(const char *name, int age)
    :
    age(age),
    e(TestEnum::kA)
  {
  }
public:
  REFL_MEMBERS
  (
    (name, r_dictionary<r_string>),
    (age, r_int<0, 10>),
    (inv, Inventory),
    (e, TestEnum)
  )
};

int main()
{
  Person p("Tom", 82);
  p.e = TestEnum::kC;

  nlohmann::json json_value = encode_json(p);
  std::cout << json_value.dump(2);

  Person copy("", 0);
  decode_json(copy, json_value);

  return 0;
}


