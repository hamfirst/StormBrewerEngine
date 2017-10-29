#pragma once

#include "Foundation/Common.h"

template <typename Graph>
class PathfindingPathCache
{
public:
  using NodeId = typename Graph::NodeId;
  static const NodeId kInvalidNodeId = Graph::kInvalidNodeId;

  void CachePath(const std::vector<NodeId> & path)
  {
    if (path.size() < 2)
    {
      return;
    }

    auto src_node = &path.front();
    auto dst_node = &path.back();

    CachedPath cached_path;
    cached_path.m_Path = std::make_shared<std::vector<NodeId>>(path);

    int start_offset = 0;
    while (src_node != dst_node)
    {
      cached_path.m_SrcNode = src_node;
      cached_path.m_DstNode = dst_node;
      cached_path.m_StartOffset = start_offset;

      auto result = m_PathCache.emplace(std::make_pair(src_node, std::vector<CachedPath>{}));
      result.first.second.emplace_back(cached_path);

      src_node++;
      start_offset++;
    }
  }

  Optional<std::vector<NodeId>> GetPath(NodeId src_node, NodeId dst_node)
  {
    auto itr = m_PathCache.find(src_node);
    if (itr == m_PathCache.end())
    {
      return {};
    }

    for (auto & path : itr->second)
    {
      if (path.m_DstNode == dst_node)
      {
        std::vector<NodeId> return_path;
        for (auto node_itr = path.m_Path.begin() + itr->m_StartOffset, end = path.m_Path.end(), node_itr != end; ++node_itr)
        {
          return_path.push_back(*node_itr);
        }

        return return_path;
      }
    }

    return {};
  }

  void EvictAll()
  {
    m_PathCache.clear();
  }

private:

  struct CachedPath
  {
    NodeId m_SrcNode;
    NodeId m_DstNode;
    int m_StartOffset;
    std::shared_ptr<std::vector<NodeId>> m_Path;
  };

  std::unordered_map<NodeId, std::vector<CachedPath>> m_PathCache;

};
