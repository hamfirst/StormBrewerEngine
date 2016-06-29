
#include <iostream>
#include <vector>
#include <functional>

#include "Foundation\Common.h"
#include "Foundation\Reflection\TypeDatabaseRegister.h"
#include "Foundation\Reflection\ReflectionParent.h"
#include "Foundation\Document\DocumentModification.h"
#include "Foundation\CallList\CallList.h"

#include "Foundation\Document\Document.h"

REFL_ENUM(TestEnum, int, kA, kB, kC);

struct Inventory
{
  Inventory()
  {
    //items.PushBack(20);
  }

public:
  REFL_MEMBERS
  (
    (items, RList<RInt>)
  )
};

struct Person
{
  Person()
    : 
    age(20)
  {
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
    (name, RString),
    (age, RInt),
    (inv, Inventory),
    (e, REnum<TestEnum>)
  )
};

struct PersonDerived : public Person
{
public:

  REFL_MEMBERS_DERIVED(Person,
    (crap, RInt)
    )

};

REGISTER_TYPE(Person);
REGISTER_TYPE(PersonDerived);

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


Document * doc;
std::vector<DocumentModification> reverse_list;

void ChangeNotifier(const DocumentModification & mod)
{
  doc->ApplyDocumentModification(mod, reverse_list);
}

int main()
{
  g_SingletonInitCallList.CallAll();

  PersonDerived person;
  InitializeParentInfo(person);

  Json person_json = EncodeJson(person);
  Document person_doc = person_json.dump();

  doc = &person_doc;

  EnableChangeNotification();
  person.name = "Duder";
  DisableChangeNotification();

  PersonDerived copy;
  //DecodeJson(copy, doc->GetJsonData());

  bool same = copy == person;

  return 0;
}

