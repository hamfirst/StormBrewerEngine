#pragma once

#include "Foundation/Update/UpdateRegistrationTemplates.h"

#include "Engine/Component/ComponentUpdateBucketList.h"

template <typename T>
static void ComponentRegisterUpdate(T & t, ComponentUpdateBucketList & bucket_list)
{
  RegisterUpdate(t, bucket_list, t.GetBucket());
}
