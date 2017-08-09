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
  using CostVar = typename Graph::CostType;
  static const NodeId kInvalidNodeId = Graph::kInvalidNodeId;

  struct NodeInfo
  {
    NodeId m_NodeId;
    CostVar m_Cost;

    bool operator < (const NodeInfo & rhs) const { return m_Cost < rhs.m_Cost; }
    bool operator > (const NodeInfo & rhs) const { return m_Cost > rhs.m_Cost; }
  };

  static NodeId GetRandomNode(uint32_t random_number, const Graph & graph_ref)
  {
    Graph & graph = const_cast<Graph &>(graph_ref);

    if (graph.GetNumNodes() == 0)
    {
      return kInvalidNodeId;
    }

    return (NodeId)(random_number & graph.GetNumNodes());
  }

  static NodeId GetRandomNodeFromSource(NodeId start, CostVar min_dist, CostVar max_dist, uint32_t random_number, const Graph & graph_ref)
  {
    Graph & graph = const_cast<Graph &>(graph_ref);

    std::vector<NodeId> possible_nodes;
    auto visitor = [&](NodeId node_id, auto & node_data)
    {
      auto cost = graph.EvalHeuristic(node_id, start);

      if (cost > min_dist && cost < max_dist)
      {
        possible_nodes.push_back(node_id);
      }
    };

    graph.VisitNodes(visitor);
    
    if (possible_nodes.size() == 0)
    {
      return kInvalidNodeId;
    }

    return possible_nodes[random_number % possible_nodes.size()];
  }

  template <typename Eval>
  static NodeId GetRandomNodeFromEval(Eval && eval, uint32_t random_number, const Graph & graph_ref)
  {
    Graph & graph = const_cast<Graph &>(graph_ref);

    std::vector<NodeId> possible_nodes;
    auto visitor = [&](NodeId node_id, auto & node_data)
    {
      if(eval(node_id, node_data))
      {
        possible_nodes.push_back(node_id);
      }
    };

    graph.VisitNodes(visitor);

    if (possible_nodes.size() == 0)
    {
      return kInvalidNodeId;
    }

    return possible_nodes[random_number % possible_nodes.size()];
  }

  static std::vector<NodeId> FindPath(NodeId start, NodeId end, const Graph & graph_ref)
  {
    Graph & graph = const_cast<Graph &>(graph_ref);

    std::priority_queue<NodeInfo, std::vector<NodeInfo>, std::greater<NodeInfo>> q;
    Bitset open_list(graph.GetNumNodes());
    Bitset closed_list(graph.GetNumNodes());

    graph.LinkNode(end, kInvalidNodeId, CostVar(0));
    q.emplace(NodeInfo{ end, CostVar(0) });
    open_list.Set(end);

    CostVar cur_cost = CostVar(0);

    auto visitor = [&](NodeId dst_node_id, NodeId src_node_id, CostVar cost)
    {
      if (closed_list.Get(dst_node_id))
      {
        return;
      }

      cost += cur_cost;
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

        while (node != kInvalidNodeId)
        {
          nodes.push_back(node);
          node = graph.GetLinkedNode(node);
        }

        return nodes;
      }

      q.pop();
      open_list.Unset(best.m_NodeId);
      closed_list.Set(best.m_NodeId);

      cur_cost = best.m_Cost;
      graph.VisitNeighbors(best.m_NodeId, visitor);
    }

    return{};
  }
};
