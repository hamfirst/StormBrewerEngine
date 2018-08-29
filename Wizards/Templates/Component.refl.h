#pragma once

#include ""GameClient/GameClientCommon.h""
#include ""Runtime/Component/ComponentInitData.refl.h""
#include ""Engine/Component/Component.h""

struct {class_name}InitData : public ComponentInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({class_name}InitData);
}};

class {class_name} : public Component
{{
public:
  DECLARE_COMPONENT;

  {class_name}({class_name}InitData && init_data);
  virtual ~{class_name}();

  void UpdateFirst();
}};
