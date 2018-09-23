
#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "Runtime/ServerObject/ServerObjectSerialize.h"

#include "Game/BehaviorTree/BehaviorTree.h"
#include "Game/BehaviorTree/BehaviorTreeTypeDatabase.h"

template <typename NetBitWriter>
struct NetSerializer<BotBehaviorTree, NetBitWriter>
{
  void operator()(const BotBehaviorTree & val, NetBitWriter & writer)
  {
    writer.WriteBits(val.GetCurrentNode(), GetRequiredBits(val.GetNodeCount()));
    writer.WriteBits(val.WantsAutoAdvance(), 1);

    auto visitor = [&](StormBehaviorTreeElementType type, std::size_t type_hash, void * mem, bool active) {
      g_BehaviorTreeTypeDatabase.SerializeType(mem, type_hash, active, writer);
    };
  }
};

template <typename NetBitReader>
struct NetDeserializer<BotBehaviorTree, NetBitReader>
{
  void operator()(BotBehaviorTree & val, NetBitReader & reader)
  {
    auto current_node = reader.ReadUBits(GetRequiredBits(val.GetNodeCount()));
    auto wants_to_advance = reader.ReadUBits(1);

    val.SetCurrentNode(static_cast<int>(current_node), wants_to_advance != 0);

    auto visitor = [&](StormBehaviorTreeElementType type, std::size_t type_hash, void * mem, bool active) {
      g_BehaviorTreeTypeDatabase.DeserializeType(mem, type_hash, active, reader);
    };
  }
};





