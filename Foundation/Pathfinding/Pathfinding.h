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
  using NodeInfo = typename Graph::NodeInfo;
  using CostVar = typename Graph::CostType;
  using ScratchData = typename Graph::ScratchData;
  static const NodeId kInvalidNodeId = Graph::kInvalidNodeId;

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

  static std::vector<NodeId> FindPath(NodeId start, NodeId end, const Graph & graph, ScratchData & scratch_data)
  {
    while (scratch_data.m_Queue.empty() == false)
    {
      scratch_data.m_Queue.pop();
    }

    scratch_data.m_OpenList.Clear();
    scratch_data.m_ClosedList.Clear();

    graph.LinkNode(end, kInvalidNodeId, CostVar(0), scratch_data);
    scratch_data.m_Queue.emplace(NodeInfo{ start, CostVar(0) });
    scratch_data.m_OpenList.Set(start);

    CostVar cur_cost = CostVar(0);

    auto visitor = [&](NodeId dst_node_id, NodeId src_node_id, CostVar cost)
    {
      if (scratch_data.m_ClosedList.Get(dst_node_id))
      {
        return;
      }

      cost += cur_cost;
      auto guess = graph.EvalHeuristic(dst_node_id, end);

      if (scratch_data.m_OpenList.Get(dst_node_id))
      {
        if (graph.LinkNodeCheck(dst_node_id, src_node_id, cost, scratch_data))
        {
          scratch_data.m_Queue.emplace(NodeInfo{ dst_node_id, cost + guess });
        }
      }
      else
      {
        graph.LinkNode(dst_node_id, src_node_id, cost, scratch_data);
        scratch_data.m_OpenList.Set(dst_node_id);

        scratch_data.m_Queue.emplace(NodeInfo{ dst_node_id, cost + guess });
      }
    };

    while (scratch_data.m_Queue.size() > 0)
    {
      auto best = scratch_data.m_Queue.top();

      if (best.m_NodeId == end)
      {
        std::vector<NodeId> nodes;
        auto node = end;

        while (node != kInvalidNodeId)
        {
          nodes.push_back(node);
          node = graph.GetLinkedNode(node, scratch_data);
        }

        std::reverse(nodes.begin(), nodes.end());
        return nodes;
      }

      scratch_data.m_Queue.pop();
      scratch_data.m_OpenList.Unset(best.m_NodeId);
      scratch_data.m_ClosedList.Set(best.m_NodeId);

      cur_cost = best.m_Cost;
      graph.VisitNeighbors(best.m_NodeId, visitor);
    }

    return{};
  }

  
};
