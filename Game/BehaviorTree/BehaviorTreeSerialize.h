
#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "Runtime/ServerObject/ServerObjectSerialize.h"

#include "Game/BehaviorTree/BehaviorTree.h"
#include "Game/BehaviorTree/BehaviorTreeTypeDatabase.h"

template <>
struct NetSerializer<BotBehaviorTree, ServerObjectNetBitWriter>
{
  void operator()(const BotBehaviorTree & val, ServerObjectNetBitWriter & writer)
  {
    writer.WriteBits(val.GetCurrentNode(), GetRequiredBits(val.GetNodeCount()));
    writer.WriteBits(val.WantsAutoAdvance(), 1);

    auto visitor = [&](StormBehaviorTreeElementType type, std::size_t type_hash, void * mem, bool active) {
      g_BehaviorTreeTypeDatabase.SerializeType(mem, type_hash, active, writer);
    };
  }
};

template<>
struct NetDeserializer<BotBehaviorTree, ServerObjectNetBitReader>
{
  void operator()(BotBehaviorTree & val, ServerObjectNetBitReader & reader)
  {
    auto current_node = reader.ReadUBits(GetRequiredBits(val.GetNodeCount()));
    auto wants_to_advance = reader.ReadUBits(1);

    val.SetCurrentNode(static_cast<int>(current_node), wants_to_advance != 0);

    auto visitor = [&](StormBehaviorTreeElementType type, std::size_t type_hash, void * mem, bool active) {
      g_BehaviorTreeTypeDatabase.DeserializeType(mem, type_hash, active, reader);
    };
  }
};





