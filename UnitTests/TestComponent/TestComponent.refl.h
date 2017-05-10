
#pragma once

#include "Foundation/Common.h"
#include "Runtime/Component/Component.h"
#include "Runtime/Component/ComponentInitData.refl.h"

struct TestEvent
{
  static uint32_t TypeNameHash;
};

struct TestComponentInitData : public ComponentInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(TestComponentInitData);
};

class TestComponent : public Component
{
public:
  DECLARE_COMPONENT;

  TestComponent(TestComponentInitData & init_data);
  virtual ~TestComponent();

  virtual void OnActivate() override;
  void UpdateFirst();

  void HandleEvent(TestEvent * ev);
};
