
#include <iostream>
#include <vector>
#include <functional>

#include "Foundation\Common.h"
#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\ReflectionJson.h"

#include "Foundation\Document\DocumentPath.h"

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
    (name, std::unordered_map<r_hash, int>),
    (age, r_int<0, 10>),
    (inv, Inventory),
    (e, TestEnum)
  )

    std::unordered_map<r_hash, int> member;
};

template <class T>
void TEST(T & t, bool expect_exception = false)
{
  try
  {
    bool val = t();
    if (expect_exception)
    {
      assert(false);
    }

    assert(val);
  }
  catch (std::exception & ex)
  {
    assert(false);
  }
}

int main()
{
  auto a = []() { DocumentPath p("a.a"); return p.GetSize() == 2 && p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName; };

  TEST(a);

  //Person p("Tom", 82);
  //p.e = TestEnum::kC;

  //nlohmann::json json_value = encode_json(p);
  //std::cout << json_value.dump(2);

  //Person copy("", 0);
  //decode_json(copy, json_value);

  return 0;
}
