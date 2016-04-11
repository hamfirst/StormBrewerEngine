
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
    items.PushBack(20);
  }

public:
  REFL_MEMBERS
  (
    (items, RList<int>)
  )
};

struct Person
{
  Person()
  {
    age = 82;
  }

  Person(const char *name, int age)
    :
    age(age),
    e(TestEnum::kA)
  {
  }
public:
  REFL_MEMBERS
  (
    (name, RDictionary<RString>),
    (age, int),
    (inv, Inventory),
    (e, TestEnum)
  )
};

template <class T>
void TEST(T t, bool expect_exception = false)
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
  catch (...)
  {
    if (expect_exception == false)
    {
      assert(false);
    }
  }
}

int main()
{

  RSparseList<int> asdf;
  asdf.PushBack(1);
  asdf.PushBack(2);
  asdf.PushBack(30);
  asdf.RemoveAt(1);
  asdf.PushBack(90);

  RHashMap<int> map;
  map.Set(0, 2);
  map.Get(0);
  map.Remove(0);

  Json j = EncodeJson(asdf);
  std::string test = j.dump(2);
  std::cout << test << std::endl;

  RSparseList<int> asdf2;
  DecodeJson(asdf2, j);

  Person p;
  p.age = 90;
  SetValueDefault(p, COMPILE_TIME_CRC32_STR("age"));
  p.e = TestEnum::kC;

  auto json_value = EncodeJson(p);
  std::cout << json_value.dump(2);

  //Person copy("", 0);
  //DecodeJson(copy, json_value);

  return 0;
}

