#pragma once

#include "Foundation/Common.h"
#include "Foundation/Bitset/Bitset.h"
#include "Foundation/Math/Util.h"

#include <queue>
#include <bitset>

template <typename Graph>
class Pathfinding
{
public:

  using NodeId = typename Graph::NodeId;
  static const NodeId kInvalidNodeId = Graph::kInvalidNodeId;

  struct NodeInfo
  {
    NodeId m_NodeId;
    float m_Cost;

    bool operator < (const NodeInfo & rhs) const { return m_Cost < rhs.m_Cost; }
  };

  static std::vector<NodeId> FindPath(NodeId start, NodeId end, Graph & graph)
  {
    std::priority_queue<NodeInfo> q;
    Bitset open_list(graph.GetNumNodes());
    Bitset closed_list(graph.GetNumNodes());

    graph.LinkNode(end, kInvalidNodeId, 0.0f);
    q.emplace(NodeInfo{ end, 0 });
    open_list.Set(end);

    auto visitor = [&](NodeId dst_node_id, NodeId src_node_id, float cost)
    {
      if (closed_list.Get(dst_node_id))
      {
        return;
      }

      auto guess = graph.EvalHeuristic(dst_node_id, start);

      if (open_list.Get(dst_node_id))
      {
        if (graph.LinkNodeCheck(dst_node_id, src_node_id, cost))
        {
          q.emplace(NodeInfo{ dst_node_id, cost + guess });
        }
      }
      else
      {
        graph.LinkNode(dst_node_id, src_node_id, cost);
        open_list.Set(dst_node_id);

        q.emplace(NodeInfo{ dst_node_id, cost + guess });
      }
    };

    while (q.size() > 0)
    {
      auto best = q.top();

      if (best.m_NodeId == start)
      {
        std::vector<NodeId> nodes;
        auto node = start;

        nodes.push_back(start);

        while (node != kInvalidNodeId)
        {
          node = graph.GetLinkedNode(node);
          nodes.push_back(node);
        }

        return nodes;
      }

      q.pop();
      open_list.Unset(best.m_NodeId);
      closed_list.Set(best.m_NodeId);

      graph.VisitNeighbors(best.m_NodeId, best.m_Cost, visitor);
    }

    return{};
  }
};
