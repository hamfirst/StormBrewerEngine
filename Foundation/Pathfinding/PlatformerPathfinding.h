#pragma once

#include "Foundation/Pathfinding/Pathfinding.h"

template <typename GridData, typename CostVar, typename MoveEvaluator>
class PathfindingPlatformerGrid2D
{
public:

  using NodeId = uint32_t;
  using CostType = CostVar;
  static const NodeId kInvalidNodeId = -1;

  enum AgentActionType
  {
    kNone,
    kMove,
    kJump,
    kFall,
  };

  struct AgentState
  {
    bool m_OnGround;
    CostVar m_VelocityY;
    Vector2 m_Position;
  };

  struct AgentAction
  {
    AgentActionType m_Type;
    AgentState m_State;
  };

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
    EvalResult m_Result;
  };

  struct EvalResult
  {
    CostVar m_Cost;
    AgentAction m_Action;
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

  PathfindingPlatformerGrid2D(const Vector2 & grid_start, const Vector2 & grid_element_size, const Vector2 & grid_size, const Vector2 & agent_size,
                              CostVar move_speed, CostVar jump_speed, CostVar gravity, CostVar extra_gravity) :
    m_GridStart(grid_start),
    m_GridElementSize(grid_element_size),
    m_GridSize(grid_size),
    m_AgentSize(agent_size),
    m_MoveSpeed(move_speed),
    m_JumpSpeed(jump_speed),
    m_Gravity(gravity),
    m_ExtraGravity(extra_gravity)
  {
    int frames_jumping = (int)(jump_speed / gravity);
    
    m_JumpHeight = 0;
    for (int index = 0; index < frames_jumping; ++index)
    {
      m_JumpHeight += jump_speed;
      jump_speed -= gravity;

      m_JumpFrames++;
    }

    m_JumpHorizontalPotential = (int)(move_speed * CostVar(m_JumpFrames));

    m_Grid = std::make_unique<GridData[]>(m_GridSize.x * m_GridSize.y);
  }

  PathfindingPlatformerGrid2D(const PathfindingPlatformerGrid2D & rhs) = delete;
  PathfindingPlatformerGrid2D(PathfindingPlatformerGrid2D && rhs) = delete;

  PathfindingPlatformerGrid2D & operator =(const PathfindingPlatformerGrid2D & rhs) = delete;
  PathfindingPlatformerGrid2D & operator =(PathfindingPlatformerGrid2D && rhs) = delete;

  Vector2 NodeIdToLocation(NodeId node_id) const
  {
    return Vector2{ (int)(node_id % m_Width), (int)(node_id / m_Width) };
  }

  NodeId LocationToNodeId(const Vector2 & pos) const
  {
    return (NodeId)(pos.y * m_Width + pos.x);
  }

  std::size_t GetNumNodes() const
  {
    return m_Width * m_Height;
  }

  void SetGridData(int x, int y, const GridData & data)
  {
    m_Grid[x + y * m_Width] = data;
  }

  const GridData & GetGridData(int x, int y) const
  {
    return m_Grid[x + y * m_Width];
  }

  void LinkNode(NodeId node_id, NodeId src_node, CostVar cost, ScratchData & scratch_data) const
  {
    auto & grid_data = scratch_data.m_NodeData[node_id];

    grid_data.m_PrevNode = src_node;
    grid_data.m_Cost = cost;
  }

  bool LinkNodeCheck(NodeId node_id, NodeId src_node, CostVar cost, ScratchData & scratch_data) const
  {
    auto & grid_data = scratch_data.m_NodeData[node_id];

    if (cost < grid_data.m_Cost)
    {
      grid_data.m_PrevNode = src_node;
      grid_data.m_Cost = cost;
      return true;
    }

    return false;
  }

  NodeId GetLinkedNode(NodeId node_id, ScratchData & scratch_data) const
  {
    auto & grid_data = scratch_data.m_NodeData[node_id];
    return grid_data.m_PrevNode;
  }

  CostVar EvalHeuristic(NodeId dest_node_id, NodeId src_node) const
  {
    auto src_location = NodeIdToLocation(src_node);
    auto dst_location = NodeIdToLocation(dest_node_id);

    return ManhattanDist(src_location, dst_location);
  }

  template <typename Visitor>
  void VisitNeighbors(NodeId node_id, Visitor && visitor) const
  {
    auto location = NodeIdToLocation(node_id);
    auto target_location = NodeIdToLocation(node_id);
    auto & src_grid = GetGridData(location.x, location.y);

    auto zero = CostVar(0);

    if (location.x > 0)
    {
      auto dest_node = LocationToNodeId(Vector2(location.x - 1, location.y));
      auto & dest_data = GetGridData(location.x - 1, location.y);
      auto cost = m_Eval(src_grid, dest_data);

      if (cost >= zero)
      {
        visitor(dest_node, node_id, cost);
      }
    }

    if (location.x < m_Width - 1)
    {
      auto dest_node = LocationToNodeId(Vector2(location.x + 1, location.y));
      auto & dest_data = GetGridData(location.x + 1, location.y);
      auto cost = m_Eval(src_grid, dest_data);

      if (cost >= zero)
      {
        visitor(dest_node, node_id, cost);
      }
    }

    if (location.y > 0)
    {
      auto dest_node = LocationToNodeId(Vector2(location.x, location.y - 1));
      auto & dest_data = GetGridData(location.x, location.y - 1);
      auto cost = m_Eval(src_grid, dest_data);

      if (cost >= zero)
      {
        visitor(dest_node, node_id, cost);
      }
    }

    if (location.y < m_Height - 1)
    {
      auto dest_node = LocationToNodeId(Vector2(location.x, location.y + 1));
      auto & dest_data = GetGridData(location.x, location.y + 1);
      auto cost = m_Eval(src_grid, dest_data);

      if (cost >= zero)
      {
        visitor(dest_node, node_id, cost);
      }
    }
  }

  AgentState GetDefaultState(const Vector2 & base_pos)
  {
    AgentState state;
    if (CheckGround(base_pos))
    {
      state.m_OnGround = true;
      state.m_JumpPotential = m_JumpHeight;
    }
    else
    {
      state.m_OnGround = false;
      state.m_JumpPotential = 0;
    }
    return state;
  }

  ScratchData CreateScratchData() const
  {
    return ScratchData(GetNumNodes());
  }

private:

  bool CheckPositionValid(const Vector2 & base_pos) const
  {
    Vector2 start_pos = base_pos - m_GridStart;
    Vector2 end_pos = start_pos + m_AgentSize;

    start_pos /= m_GridElementSize;
    end_pos /= m_GridElementSize;

    for (int y = start_pos.y; y <= end_pos.y; ++y)
    {
      if (y < 0)
      {
        continue;
      }

      if (y >= m_GridSize.y)
      {
        return true;
      }

      for (int x = start_pos.x; x <= end_pos.x; ++x)
      {
        if (x < 0)
        {
          continue;
        }

        if (x >= m_GridSize.x)
        {
          break;
        }

        if (m_Grid[y * m_GridSize.x + x])
        {
          return false;
        }
      }
    }

    return true;
  }

  bool CheckGround(const Vector2 & base_pos) const
  {
    Vector2 start_pos = base_pos - m_GridStart;
    Vector2 end_pos = start_pos + m_AgentSize;

    start_pos /= m_GridElementSize;
    end_pos /= m_GridElementSize;

    int y = start_pos.y - 1;

    for (int x = start_pos.x; x <= end_pos.x; x++)
    {
      if (x < 0)
      {
        continue;
      }

      if (x >= m_GridSize.x)
      {
        return false;
      }

      if (m_Grid[y * m_GridSize.x + x])
      {
        return true;
      }
    }

    return false;
  }

  bool CanJumpToLocation(NodeId dest_node_id, const Vector2 & base_pos)
  {
    auto dst_location = NodeIdToLocation(dest_node_id);

    int horizontal_dist = 0;
    if (dst_location.x < base_pos.x)
    {
      horizontal_dist = base_pos.x - dst_location.x;
    }
    else
    {
      horizontal_dist = dst_location.x - base_pos.x - m_AgentSize.x;
      if (horizontal_dist < 0)
      {
        horizontal_dist = 0;
      }
    }

    auto vertical_dist = dst_location.y - base_pos.y;
    if (vertical_dist > m_JumpHeight)
    {
      return false;
    }

    if (horizontal_dist < m_JumpHorizontalPotential)
    {
      return true;
    }

    horizontal_dist -= m_JumpHorizontalPotential;
    auto fall_frames = (int)(CostVar(horizontal_dist) / m_MoveSpeed);
    auto fall_dist = (CostVar(fall_frames * fall_frames) * m_Gravity) / 2;

    if (vertical_dist > (int)m_JumpHeight - fall_dist)
    {
      return false;
    }

    return true;
  }

  CostVar GetHorizontalTravelTime(const Vector2 & dst_location, const Vector2 & base_pos) const
  {
    CostVar time;

    if (dst_location.x < base_pos.x)
    {
      time = CostVar(base_pos.x - dst_location.x) / m_MoveSpeed;
    }
    else
    {
      auto dist = dst_location.x - base_pos.x - m_AgentSize.x;
      if (dist < 0)
      {
        time = 0;
      }
      else
      {
        time = CostVar(dist) / m_MoveSpeed;
      }
    }

    return time;
  }

  Optional<CostVar> GetVerticalTravelTime(const Vector2 & dst_location, const Vector2 & base_pos, Optional<CostVar> & vertical_speed) const
  {
    if (dst_location.y < base_pos.y)
    {
      // Attempting to fall
      int frames_falling = 0;
      CostVar y_pos = base_pos.y;
      CostVar dst = dst_location.y;

      CostVar fall_speed = 0;

      if (vertical_speed)
      {
        fall_speed = vertical_speed.Value();
        while (fall_speed > 0)
        {
          y_pos += fall_speed;
          fall_speed -= m_ExtraGravity;
          frames_falling++;
        }
      }

      while (y_pos > dst)
      {
        y_pos += fall_speed;
        fall_speed -= m_ExtraGravity;
        frames_falling++;
      }

      return CostVar(frames_falling);
    }
    else if (dst_location.y == base_pos.y)
    {
      return CostVar(0);
    }
    else
    {
      auto dist_to_jump = dst_location.y - base_pos.y;
      int frames_jumping = 0;
      if (dist_to_jump > m_JumpHeight)
      {
        return {};
      }

      CostVar upward_vel = m_JumpSpeed;

      if (vertical_speed)
      {
        if (vertical_speed.Value() <= 0)
        {
          return {};
        }

        upward_vel = vertical_speed.Value();
      }

      CostVar dst = dist_to_jump;
      while (dst > 0)
      {
        if (upward_vel <= 0)
        {
          return {};
        }

        dst -= upward_vel;
        upward_vel -= m_Gravity;
        frames_jumping++;
      }

      return CostVar(frames_jumping);
    }
  }

private:

  Vector2 m_GridStart;
  Vector2 m_GridElementSize;
  Vector2 m_GridSize;
  Vector2 m_AgentSize;

  CostVar m_MoveSpeed;
  CostVar m_JumpSpeed;
  CostVar m_Gravity;
  CostVar m_ExtraGravity;
  CostVar m_JumpHeight;
  int m_JumpFrames;
  int m_JumpHorizontalPotential;

  std::unique_ptr<GridData[]> m_Grid;
  std::size_t m_Width;
  std::size_t m_Height;

  MoveEvaluator m_Eval;
};