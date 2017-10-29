#pragma once

#include "Foundation/Pathfinding/Pathfinding.h"

template <typename GraphData, typename CostVar, typename Heuristic>
class PathfindingSymmetricGraph
{
public:
  using NodeId = int;
  using CostType = CostVar;
  static const NodeId kInvalidNodeId = -1;

  struct NodeInfo
  {
    NodeId m_NodeId;
    CostVar m_Cost;

    bool operator < (const NodeInfo & rhs) const { return m_Cost < rhs.m_Cost; }
    bool operator > (const NodeInfo & rhs) const { return m_Cost > rhs.m_Cost; }
  };

  struct PerNodeData
  {
    NodeId m_PrevNode;
    CostVar m_Cost;
  };

  struct ScratchData
  {
    ScratchData(std::size_t num_nodes) :
      m_NodeData(num_nodes),
      m_OpenList(num_nodes),
      m_ClosedList(num_nodes)
    {

    }

    std::priority_queue<NodeInfo, std::vector<NodeInfo>, std::greater<NodeInfo>> m_Queue;
    std::vector<PerNodeData> m_NodeData;
    Bitset m_OpenList;
    Bitset m_ClosedList;
  };

  PathfindingSymmetricGraph()
  {

  }

  PathfindingSymmetricGraph(const PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> & rhs) = delete;
  PathfindingSymmetricGraph(PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> && rhs) = delete;

  PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> & operator =(const PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> & rhs) = delete;
  PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> & operator =(PathfindingSymmetricGraph<GraphData, CostVar, Heuristic> && rhs) = delete;

  std::size_t GetNumNodes() const
  {
    return m_Graph.size();
  }

  NodeId CreateNode(const GraphData & data)
  {
    NodeId index = (NodeId)m_Graph.size();
    m_Graph.emplace_back(GraphContainerData{ data });
    return index;
  }

  void ConnectNodes(NodeId node_a, NodeId node_b, CostVar cost)
  {
    m_Graph[node_a].m_Connections.emplace_back(std::make_pair(node_b, cost));
    m_Graph[node_b].m_Connections.emplace_back(std::make_pair(node_a, cost));
  }

  void ConnectNodes(NodeId node_a, NodeId node_b)
  {
    ConnectNodes(node_a, node_b, EvalHeuristic(node_a, node_b));
  }

  const GraphData & GetGridData(NodeId node_id) const
  {
    return m_Graph[node_id].m_Data;
  }

  GraphData & GetGridData(NodeId node_id)
  {
    return m_Graph[node_id].m_Data;
  }

  void LinkNode(NodeId node_id, NodeId src_node, CostVar cost, ScratchData & scratch_data) const
  {
    auto & graph_data = scratch_data.m_NodeData[node_id];

    graph_data.m_PrevNode = src_node;
    graph_data.m_Cost = cost;
  }

  bool LinkNodeCheck(NodeId node_id, NodeId src_node, CostVar cost, ScratchData & scratch_data) const
  {
    auto & graph_data = scratch_data.m_NodeData[node_id];

    if (cost < graph_data.m_Cost)
    {
      graph_data.m_PrevNode = src_node;
      graph_data.m_Cost = cost;
      return true;
    }

    return false;
  }

  NodeId GetLinkedNode(NodeId node_id, ScratchData & scratch_data) const
  {
    auto & graph_data = scratch_data.m_NodeData[node_id];
    return graph_data.m_PrevNode;
  }

  CostVar EvalHeuristic(NodeId dest_node_id, NodeId src_node_id) const
  {
    return m_Heuristic(m_Graph[src_node_id].m_Data, m_Graph[dest_node_id].m_Data);
  }

  template <typename Visitor>
  void VisitNeighbors(NodeId node_id, Visitor && visitor)
  {
    auto & graph_data = m_Graph[node_id];
    for (auto & elem : graph_data.m_Connections)
    {
      visitor(elem.first, node_id, elem.second);
    }
  }

  template <typename Visitor>
  void VisitNeighbors(NodeId node_id, Visitor && visitor) const
  {
    auto & graph_data = m_Graph[node_id];
    for (auto & elem : graph_data.m_Connections)
    {
      visitor(elem.first, node_id, elem.second);
    }
  }

  template <typename Visitor>
  void VisitNodes(Visitor && visitor)
  {
    for (std::size_t index = 0, end = m_Graph.size(); index < end; ++index)
    {
      visitor((int)index, m_Graph[index].m_Data);
    }
  }

  template <typename Visitor>
  void VisitNodes(Visitor && visitor) const
  {
    for (std::size_t index = 0, end = m_Graph.size(); index < end; ++index)
    {
      visitor((int)index, m_Graph[index].m_Data);
    }
  }

  ScratchData CreateScratchData() const
  {
    return ScratchData(GetNumNodes());
  }

private:
  struct GraphContainerData
  {
    GraphData m_Data;
    std::vector<std::pair<NodeId, CostVar>> m_Connections;
  };

  std::vector<GraphContainerData> m_Graph;
  Heuristic m_Heuristic;
};



