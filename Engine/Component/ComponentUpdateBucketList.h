#pragma once

#include "Engine/Component/Component.h"
#include "Foundation/Update/UpdateBucketList.h"

using ComponentUpdateFunc = void (Component::*)();

extern template class UpdateList<Component, ComponentUpdateFunc>;
extern template class UpdateBucketList<Component, ComponentUpdateFunc>;

class ComponentUpdateList : public UpdateList<Component, ComponentUpdateFunc> {};
class ComponentUpdateBucketList : public UpdateBucketList<Component, ComponentUpdateFunc> {};

