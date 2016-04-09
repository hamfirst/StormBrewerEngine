
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



void TestDocumentPath()
{
  TEST([]()
  {
    DocumentPath p("a.a");
    return p.GetSize() == 2 &&
      p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName &&
      p[1].m_Data == "a" && p[1].m_Type == DocumentPath::kFieldName;
  });

  TEST([]()
  {
    DocumentPath p("a.a[1]");
    return p.GetSize() == 3 &&
      p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName &&
      p[1].m_Data == "a" && p[1].m_Type == DocumentPath::kFieldName &&
      p[2].m_Data == "1" && p[2].m_Type == DocumentPath::kIntIndex;
  });

  TEST([]()
  {
    DocumentPath p("a.a[1].a");
    return p.GetSize() == 4 &&
      p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName &&
      p[1].m_Data == "a" && p[1].m_Type == DocumentPath::kFieldName &&
      p[2].m_Data == "1" && p[2].m_Type == DocumentPath::kIntIndex &&
      p[3].m_Data == "a" && p[3].m_Type == DocumentPath::kFieldName;
  });

  TEST([]()
  {
    DocumentPath p("a.a[1].a[asdf]");
    return p.GetSize() == 5 &&
      p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName &&
      p[1].m_Data == "a" && p[1].m_Type == DocumentPath::kFieldName &&
      p[2].m_Data == "1" && p[2].m_Type == DocumentPath::kIntIndex &&
      p[3].m_Data == "a" && p[3].m_Type == DocumentPath::kFieldName &&
      p[4].m_Data == "asdf" && p[4].m_Type == DocumentPath::kStringIndex;
  });

  TEST([]()
  {
    DocumentPath p("a.a[-1].a[asdf]");
    return p.GetSize() == 5 &&
      p[0].m_Data == "a" && p[0].m_Type == DocumentPath::kFieldName &&
      p[1].m_Data == "a" && p[1].m_Type == DocumentPath::kFieldName &&
      p[2].m_Data == "-1" && p[2].m_Type == DocumentPath::kIntIndex &&
      p[3].m_Data == "a" && p[3].m_Type == DocumentPath::kFieldName &&
      p[4].m_Data == "asdf" && p[4].m_Type == DocumentPath::kStringIndex;
  });

  TEST([]() { DocumentPath p("a.."); return true; }, true);
  TEST([]() { DocumentPath p("a."); return true; }, true);
  TEST([]() { DocumentPath p("a[]"); return true; }, true);
  TEST([]() { DocumentPath p("a[a].a["); return true; }, true);
  TEST([]() { DocumentPath p("a[[1]"); return true; }, true);
  TEST([]() { DocumentPath p("a[a.a]"); return true; }, true);
  TEST([]() { DocumentPath p("a]"); return true; }, true);
  TEST([]() { DocumentPath p("."); return true; }, true);
  TEST([]() { DocumentPath p(""); return true; }, true);
  TEST([]() { DocumentPath p("a.[asdf]"); return true; }, true);
  TEST([]() { DocumentPath p("a.a[asdf.]"); return true; }, true);
  TEST([]() { DocumentPath p("a.a[a]."); return true; }, true);
  TEST([]() { DocumentPath p("a.a[--1]"); return true; }, true);
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

  TestDocumentPath();

  RSparseList<int> asdf2;
  DecodeJson(asdf2, j);

  //Person p("Tom", 82);
  //p.e = TestEnum::kC;

  //nlohmann::json json_value = EncodeJson(p);
  //std::cout << json_value.dump(2);

  //Person copy("", 0);
  //DecodeJson(copy, json_value);

  return 0;
}

