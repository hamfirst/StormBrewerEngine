

#include "Foundation/Common.h"
#include "Runtime/Entity/Entity.h"

#include "UnitTests/TestComponent/TestComponent.refl.h"
#include "UnitTests/TestComponent/TestComponent.refl.meta.h"

uint32_t TestEvent::TypeNameHash = COMPILE_TIME_CRC32_STR("TestEvent");

TestComponent::TestComponent(TestComponentInitData & init_data)
{
  
}

TestComponent::~TestComponent()
{
  
}

void TestComponent::UpdateFirst()
{

}

void TestComponent::OnActivate()
{
  AddEventHandler(&TestComponent::HandleEvent);
}

void TestComponent::HandleEvent(TestEvent * ev)
{

}
