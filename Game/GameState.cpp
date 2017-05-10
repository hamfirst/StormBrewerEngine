
#include "Foundation/Common.h"
#include "Game/GameState.h"

#include "Runtime/Component/ComponentUpdateBucketList.h"

GameState::GameState()
{

}

void GameState::Update()
{
  ComponentUpdateBucketList bucket_list;
  CreateUpdateList(bucket_list);

  int buckets = bucket_list.GetNumBuckets();
  for (int index = 0; index < buckets; ++index)
  {
    bucket_list.CallFirst(index);
    FinalizeEvents();
  }

  for (int index = 0; index < buckets; ++index)
  {
    bucket_list.CallMiddle(index);
    FinalizeEvents();
  }

  for (int index = 0; index < buckets; ++index)
  {
    bucket_list.CallLast(index);
    FinalizeEvents();
  }
}

