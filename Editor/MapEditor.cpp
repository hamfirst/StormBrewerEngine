
#include "StormData/StormDataParent.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapCollision.h"
#include "Runtime/Collision/CollisionDatabase.h"

#include "EditorContainer.h"
#include "DocumentEditor.h"
#include "MapEditor.h"

#include "MapEditorToolManualTileLayerDraw.h"
#include "MapEditorToolManualTileLayerSelect.h"
#include "MapEditorToolEntityLayerDraw.h"
#include "MapEditorToolEntityLayerSelect.h"
#include "MapEditorToolServerObjectLayerDraw.h"
#include "MapEditorToolServerObjectLayerSelect.h"
#include "MapEditorToolParalaxObjectLayerDraw.h"
#include "MapEditorToolParalaxObjectLayerSelect.h"
#include "MapEditorToolVolumeCreate.h"
#include "MapEditorToolVolumeEditor.h"
#include "MapEditorToolVolumeMultiEditor.h"
#include "MapEditorToolPathCreate.h"
#include "MapEditorToolPathEditor.h"
#include "MapEditorToolPathMultiEditor.h"
#include "MapEditorToolAnchorCreate.h"
#include "MapEditorToolAnchorEditor.h"
#include "MapEditorToolAnchorMultiEditor.h"

#include <unordered_set>



MapEditor::MapEditor(PropertyFieldDatabase & property_db, const std::string & root_path, MapDef & map, DocumentChangeLinkDelegate && change_link_callback,
  DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_Map(map),
  m_ManualTileLayers(".m_ManualTileLayers", this, m_Map, m_Map.m_ManualTileLayers),
  m_EntityLayers(".m_EntityLayers", this, m_Map, m_Map.m_EntityLayers),
  m_ServerObjectLayers(".m_ServerObjectLayers", this, m_Map, m_Map.m_ServerObjectLayers),
  m_ParalaxLayers(".m_ParalaxLayers", this, m_Map, m_Map.m_ParalaxLayers),
  m_EffectLayers(".m_EffectLayers", this, m_Map, m_Map.m_EffectLayers),
  m_Volumes(".m_Volumes", this, m_Map, m_Map.m_Volumes),
  m_Paths(".m_Paths", this, m_Map, m_Map.m_Paths),
  m_Anchors(".m_Anchors", this, m_Map, m_Map.m_Anchors),
  m_Layout(std::make_unique<QGridLayout>()),
  m_Properties(std::make_unique<GenericFrame>("Properties", this)),
  m_Selector(std::make_unique<MapEditorSelector>(this, m_Map)),
  m_LayerList(std::make_unique<MapEditorLayerList>(this, m_Map)),
  m_Viewer(std::make_unique<MapEditorViewer>(this, m_Map)),
  m_IgnoreSelectionChanges(false)
{
  m_Properties->setMinimumWidth(230);

  m_Layout->setColumnStretch(0, 1);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(1, 4);
  m_Layout->setColumnMinimumWidth(0, 100);

  m_Layout->setColumnStretch(2, 1);
  m_Layout->setColumnMinimumWidth(1, 300);

  m_Layout->setRowStretch(0, 4);

  m_Layout->setRowStretch(1, 1);
  m_Layout->setRowMinimumHeight(1, 100);

  m_Layout->addWidget(m_LayerList.get(), 0, 0, 2, 1);
  m_Layout->addWidget(m_Viewer.get(), 0, 1);
  m_Layout->addWidget(m_Properties.get(), 0, 2);
  m_Layout->addWidget(m_Selector.get(), 1, 1, 1, 2);

  SetNotifyCallback(m_ParalaxInitData, [](void * this_ptr, const ReflectionChangeNotification & change)
  {
    MapEditor * editor = static_cast<MapEditor *>(this_ptr);
    editor->m_ParalaxInitObject = MapEditorParalaxLayer::CreateObjectFromPath(editor->m_ParalaxInitData.m_File.data(), [] {});
  }, this);

  m_PropertyEditor = m_Properties->CreateWidget<PropertyEditor>();
  setLayout(m_Layout.get());
}

void MapEditor::ChangeLayerSelection(const MapEditorLayerSelection & layer, bool change_viewer_position)
{
  if (m_IgnoreSelectionChanges)
  {
    return;
  }

  m_Selector->GetTileSelector()->SetLayer(-1);
  m_Selector->GetEntitySelector()->SetLayer(-1);
  m_Selector->GetServerObjectSelector()->SetLayer(-1);

  switch (layer.m_Type)
  {
  case MapEditorLayerItemType::kMapProperties:
    ClearLayerSelection();
    m_PropertyEditor->LoadStruct(this, m_Map.m_PropertiesInfo,
      [this, index = layer.m_Index]() -> void * { return &m_Map.m_PropertiesInfo; }, true);
    break;
  case MapEditorLayerItemType::kPathfinding:
    ClearLayerSelection();
    m_PropertyEditor->LoadStruct(this, m_Map.m_PathfingindInfo,
      [this, index = layer.m_Index]() -> void * { return &m_Map.m_PathfingindInfo; }, true);
    break;
  case MapEditorLayerItemType::kManualTileLayerParent:
  case MapEditorLayerItemType::kEntityLayerParent:
  case MapEditorLayerItemType::kServerObjectLayerParent:
  case MapEditorLayerItemType::kVolumeParent:
  case MapEditorLayerItemType::kPathParent:
  case MapEditorLayerItemType::kAnchorParent:
    ClearLayerSelection();
    break;
  case MapEditorLayerItemType::kManualTileLayer:
    m_PropertyEditor->LoadStruct(this, m_Map.m_ManualTileLayers[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ManualTileLayers.TryGet(index); }, true);

    m_Selector->GetTileSelector()->show();
    m_Selector->GetTileSelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParalaxObjectSelector()->Clear();
    m_Selector->GetParalaxObjectSelector()->hide();

    m_Selector->GetTileSelector()->LoadManualTileLayer(layer.m_Index);
    break;
  case MapEditorLayerItemType::kEntityLayer:

    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->show();
    m_Selector->GetEntitySelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParalaxObjectSelector()->Clear();
    m_Selector->GetParalaxObjectSelector()->hide();
    m_PropertyEditor->LoadStruct(this, m_Map.m_EntityLayers[layer.m_Index], 
      [this, index = layer.m_Index]() -> void * { return m_Map.m_EntityLayers.TryGet(index); }, true);
    break;
  case MapEditorLayerItemType::kServerObjectLayer:

    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->show();
    m_Selector->GetServerObjectSelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetParalaxObjectSelector()->Clear();
    m_Selector->GetParalaxObjectSelector()->hide();
    m_PropertyEditor->LoadStruct(this, m_Map.m_ServerObjectLayers[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ServerObjectLayers.TryGet(index); }, true);
    break;
  case MapEditorLayerItemType::kEntity:

    ClearSelectors();
    
    m_PropertyEditor->LoadStruct(this, m_Map.m_EntityLayers[layer.m_Index].m_Entities[layer.m_SubIndex], 
      [this, index = layer.m_Index, subindex = layer.m_SubIndex]() -> void * 
      { 
        auto layer = m_Map.m_EntityLayers.TryGet(index); 
        auto entity = layer ? layer->m_Entities.TryGet(subindex) : nullptr; 
        return entity;
      }, true
    );

    if (change_viewer_position)
    {
      m_Viewer->ZoomToEntity(layer.m_Index, layer.m_SubIndex);
    }
    break;
  case MapEditorLayerItemType::kServerObject:

    ClearSelectors();
    
    m_PropertyEditor->LoadStruct(this, m_Map.m_ServerObjectLayers[layer.m_Index].m_Objects[layer.m_SubIndex], 
      [this, index = layer.m_Index, subindex = layer.m_SubIndex]() -> void * 
      { 
        auto layer = m_Map.m_ServerObjectLayers.TryGet(index); 
        auto server_object = layer ? layer->m_Objects.TryGet(subindex) : nullptr; 
        return server_object;
      }, true
    );

    if (change_viewer_position)
    {
      m_Viewer->ZoomToServerObject(layer.m_Index, layer.m_SubIndex);
    }
    break;

  case MapEditorLayerItemType::kParalaxLayer:

    ClearSelectors();
    m_PropertyEditor->LoadStruct(this, m_Map.m_ParalaxLayers[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ParalaxLayers.TryGet(index); }, true);
    break;

  case MapEditorLayerItemType::kCreateParalaxObject:
    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParalaxObjectSelector()->show();
    m_Selector->GetParalaxObjectSelector()->SetLayer((int)layer.m_Index);

    {
      auto property_data = GetProperyMetaData<MapParalaxLayerObject>(GetPropertyFieldDatabase());
      m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_ParalaxInitData; }, "");
    }

    break;

  case MapEditorLayerItemType::kParalaxObject:

    ClearSelectors();
    
    m_PropertyEditor->LoadStruct(this, m_Map.m_ParalaxLayers[layer.m_Index].m_Objects[layer.m_SubIndex], 
      [this, index = layer.m_Index, subindex = layer.m_SubIndex]() -> void * 
      { 
        auto layer = m_Map.m_ParalaxLayers.TryGet(index); 
        auto paralax_object = layer ? layer->m_Objects.TryGet(subindex) : nullptr; 
        return paralax_object;
      }, true
    );

    if (change_viewer_position)
    {
      m_Viewer->ZoomToParalaxObject(layer.m_Index, layer.m_SubIndex);
    }
    break;

  case MapEditorLayerItemType::kEffectLayer:

    ClearSelectors();
    m_PropertyEditor->LoadStruct(this, m_Map.m_EffectLayers[layer.m_Index], 
      [this, index = layer.m_Index]() -> void * { return m_Map.m_EffectLayers.TryGet(index); }, true);
    break;

  case MapEditorLayerItemType::kCreateVolume:
    ClearSelectors();

    {
      auto property_data = GetProperyMetaData<RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo>>(GetPropertyFieldDatabase());
      m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_VolumeInitData; }, "");
    }

    break;

  case MapEditorLayerItemType::kAllVolumes:

    ClearSelectors();
    m_PropertyEditor->Unload();
    break;

  case MapEditorLayerItemType::kVolume:

    ClearSelectors();

    m_PropertyEditor->LoadStruct(this, m_Map.m_Volumes[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Volumes.TryGet(index); }, true);

    if (change_viewer_position)
    {
      m_Viewer->ZoomToVolume(layer.m_Index);
    }
    break;

  case MapEditorLayerItemType::kCreatePath:

    ClearSelectors();

    {
      auto property_data = GetProperyMetaData<RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo>>(GetPropertyFieldDatabase());
      m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_PathInitData; }, "");
    }

    break;

  case MapEditorLayerItemType::kAllPaths:

    ClearSelectors();
    m_PropertyEditor->Unload();
    break;

  case MapEditorLayerItemType::kPath:

    ClearSelectors();

    m_PropertyEditor->LoadStruct(this, m_Map.m_Paths[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Paths.TryGet(index); }, true);

    if (change_viewer_position)
    {
      m_Viewer->ZoomToPath(layer.m_Index);
    }
    break;

  case MapEditorLayerItemType::kCreateAnchor:

    ClearSelectors();

    {
      auto property_data = GetProperyMetaData<RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo>>(GetPropertyFieldDatabase());
      m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_AnchorInitData; }, "");
    }

    break;

  case MapEditorLayerItemType::kAllAnchors:

    ClearSelectors();
    m_PropertyEditor->Unload();
    break;

  case MapEditorLayerItemType::kAnchor:

    ClearSelectors();

    m_PropertyEditor->LoadStruct(this, m_Map.m_Anchors[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Anchors.TryGet(index); }, true);

    if (change_viewer_position)
    {
      m_Viewer->ZoomToAnchor(layer.m_Index);
    }
    break;
  }

  m_Viewer->ChangeLayerSelection(layer);
  m_LayerList->ChangeLayerSelection(layer);

  switch (layer.m_Type)
  {
  case MapEditorLayerItemType::kManualTileLayer:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolManualTileLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kEntity:
    m_EntityLayers.GetLayerManager(layer.m_Index)->SetSingleSelection(layer.m_SubIndex);
    m_Viewer->SetTool(MapEditorTool<MapEditorToolEntityLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kEntityLayer:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolEntityLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kServerObject:
    m_ServerObjectLayers.GetLayerManager(layer.m_Index)->SetSingleSelection(layer.m_SubIndex);
    m_Viewer->SetTool(MapEditorTool<MapEditorToolServerObjectLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kServerObjectLayer:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolServerObjectLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kParalaxLayer:
  case MapEditorLayerItemType::kCreateParalaxObject:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolParalaxObjectLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kParalaxObject:
    m_ParalaxLayers.GetLayerManager(layer.m_Index)->SetSingleSelection(layer.m_SubIndex);
    m_Viewer->SetTool(MapEditorTool<MapEditorToolParalaxObjectLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kCreateVolume:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolVolumeCreate>{});
    break;
  case MapEditorLayerItemType::kAllVolumes:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolVolumeMultiEditor>{});
    break;
  case MapEditorLayerItemType::kVolume:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolVolumeEditor>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kCreatePath:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolPathCreate>{});
    break;
  case MapEditorLayerItemType::kAllPaths:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolPathMultiEditor>{});
    break;
  case MapEditorLayerItemType::kPath:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolPathEditor>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kCreateAnchor:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolAnchorCreate>{});
    break;
  case MapEditorLayerItemType::kAllAnchors:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolAnchorMultiEditor>{});
    break;
  case MapEditorLayerItemType::kAnchor:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolAnchorEditor>{}, (int)layer.m_Index);
    break;
  }
}

void MapEditor::ClearLayerSelection()
{
  if (m_IgnoreSelectionChanges)
  {
    return;
  }

  m_PropertyEditor->Unload();
  m_Viewer->ClearLayerSelection();
  m_LayerList->ClearLayerSelection();

  m_Selector->GetTileSelector()->Clear();
  m_Selector->GetTileSelector()->hide();
  m_Selector->GetEntitySelector()->Clear();
  m_Selector->GetEntitySelector()->hide();
  m_Selector->GetServerObjectSelector()->Clear();
  m_Selector->GetServerObjectSelector()->hide();
}

void MapEditor::CalculatePathfindingInfo()
{
  std::vector<uint32_t> collision_hashes;
  for (auto elem : m_Map.m_PathfingindInfo.m_CollisionMask)
  {
    collision_hashes.push_back(crc32(elem.second.ToString()));
  }

  auto box_multi_list = ExtractMapCollision(m_Map, Vector2{}, collision_hashes);
  CollisionDatabase coll_database(box_multi_list.size());
  auto bounds = coll_database.PushMapCollision(0, std::move(box_multi_list));

  std::vector<Box> all_boxes_list;
  for (auto & list : box_multi_list)
  {
    all_boxes_list.insert(all_boxes_list.end(), list.begin(), list.end());
  }

  if (bounds.IsValid() == false)
  {
    ClearPathfindingInfo();
    return;
  }

  auto vector_hash = [](const Vector2 & v)
  {
    uint64_t val = (uint64_t)v.x;
    val <<= 32;
    val |= ((uint64_t)v.y) & 0xFFFFFFFF;
    return val;
  };

  auto hash_to_vector = [](const uint64_t & v)
  {
    int x = (int)(v >> 32);
    int y = (int)(v);
    return Vector2(x, y);
  };

  MapPathfindingCalculatedInfo info;
  info.m_Id = GetRandomNumber();

#ifndef MAP_PLATFORMER_PATHFINDING

  info.m_GridWidth = m_Map.m_PathfingindInfo.m_GridWidth;
  info.m_GridHeight = m_Map.m_PathfingindInfo.m_GridHeight;

  auto size = bounds.Value().Size();

  info.m_StartX = bounds->m_Start.x - info.m_GridWidth * 3;
  info.m_StartY = bounds->m_Start.y - info.m_GridHeight * 3;
  info.m_SizeX = (size.x + info.m_GridWidth * 6 + info.m_GridWidth - 1) / info.m_GridWidth;
  info.m_SizeY = (size.y + info.m_GridHeight * 6 + info.m_GridHeight - 1) / info.m_GridHeight;
  info.m_GridInfo.reserve(info.m_SizeX * info.m_SizeY);

  for (int y = 0; y < info.m_SizeY; ++y)
  {
    for (int x = 0; x < info.m_SizeX; ++x)
    {
      Box box;
      box.m_Start.x = info.m_StartX + x * info.m_GridWidth;
      box.m_Start.y = info.m_StartY + y * info.m_GridHeight;
      box.m_End.x = box.m_Start.x + info.m_GridWidth - 1;
      box.m_End.y = box.m_Start.y + info.m_GridHeight - 1;

      uint8_t grid_val = (uint8_t)(coll_database.CheckCollisionAny(box, 0xFFFFFFFF) != 0);
      info.m_GridInfo.push_back(grid_val);
    }
  }

#else

  std::unordered_set<uint64_t> positions;
  for (auto & b : all_boxes_list)
  {
    auto y = b.m_End.y + 1;
    auto start_x = b.m_Start.x;
    auto end_x = b.m_End.x;

    Optional<MapPathfindingSurface> surface;

    for (int x = start_x; x <= end_x; ++x)
    {
      auto pos = Vector2(x, y);
      auto hash = vector_hash(pos);

      auto result = positions.insert(hash);
      if (result.second == false)
      {
        break;
      }

      auto clearance = coll_database.CheckClearance(pos, m_Map.m_PathfingindInfo.m_MaximumClearance, 0xFFFFFFFF);
      if (clearance < m_Map.m_PathfingindInfo.m_MinimumClearance)
      {
        break;
      }
      else
      {
        if (surface)
        {
          if (surface->m_Clearance != clearance)
          {
            info.m_Surfaces.push_back(surface.Value());

            surface.Emplace();
            surface->m_P1 = Vector2(x, y);
            surface->m_P2 = Vector2(x, y);
            surface->m_Clearance = (int)clearance;
          }
          else
          {
            surface->m_P2 = Vector2(x, y);
          }
        }
        else
        {
          surface.Emplace();
          surface->m_P1 = Vector2(x, y);
          surface->m_P2 = Vector2(x, y);
          surface->m_Clearance = (int)clearance;
        }
      }
    }

    if (surface)
    {
      info.m_Surfaces.push_back(surface.Value());
    }
  }

  std::unordered_map<uint64_t, std::vector<std::pair<std::size_t, bool>>> endpoints;
  for (std::size_t index = 0, end = info.m_Surfaces.size(); index < end; ++index)
  {
    auto & surface = info.m_Surfaces[index];
    
    auto p1_hash = vector_hash(surface.m_P1);
    auto p2_hash = vector_hash(surface.m_P2);

    auto p1_itr = endpoints.emplace(std::make_pair(p1_hash, std::vector<std::pair<std::size_t, bool>>()));
    p1_itr.first->second.emplace_back(std::make_pair(index, true));

    auto p2_itr = endpoints.emplace(std::make_pair(p2_hash, std::vector<std::pair<std::size_t, bool>>()));
    p2_itr.first->second.emplace_back(std::make_pair(index, false));
  }

  for (std::size_t index = 0, end = info.m_Surfaces.size(); index < end; ++index)
  {
    auto & surface = info.m_Surfaces[index];

    surface.m_StartConnections1 = info.m_Connections.size();

    auto p1_connection = surface.m_P1;
    p1_connection.x--;

    auto p1_hash = vector_hash(p1_connection);
    auto p1_itr = endpoints.find(p1_hash);

    if (p1_itr != endpoints.end())
    {
      for (auto & elem : p1_itr->second)
      {
        MapPathfindingSurfaceConnection connection;
        connection.m_SurfaceIndex = elem.first;
        connection.m_P1 = elem.second;
        info.m_Connections.emplace_back(connection);
      }
    }

    surface.m_EndConnections1 = info.m_Connections.size();

    surface.m_StartConnections2 = info.m_Connections.size();

    auto p2_connection = surface.m_P2;
    p2_connection.x++;

    auto p2_hash = vector_hash(p2_connection);
    auto p2_itr = endpoints.find(p2_hash);

    if (p2_itr != endpoints.end())
    {
      for (auto & elem : p2_itr->second)
      {
        MapPathfindingSurfaceConnection connection;
        connection.m_SurfaceIndex = elem.first;
        connection.m_P1 = elem.second;
        info.m_Connections.emplace_back(connection);
      }
    }

    surface.m_EndConnections2 = info.m_Connections.size();
  }
#endif

  m_Map.m_PathfingindInfo.m_CalculatedInfo = info;
}

void MapEditor::ClearPathfindingInfo()
{
  MapPathfindingCalculatedInfo info = {};
  m_Map.m_PathfingindInfo.m_CalculatedInfo = info;
}

MapEditorLayerManager<MapManualTileLayer, MapEditorTileManager> & MapEditor::GetManualTileManager()
{
  return m_ManualTileLayers;
}

MapEditorLayerManager<MapEntityLayer, MapEditorEntityManager> & MapEditor::GetEntityManager()
{
  return m_EntityLayers;
}

MapEditorLayerManager<MapServerObjectLayer, MapEditorServerObjectManager> & MapEditor::GetServerObjectManager()
{
  return m_ServerObjectLayers;
}

MapEditorLayerManager<MapParalaxLayer, MapEditorParalaxLayer> & MapEditor::GetParalaxManager()
{
  return m_ParalaxLayers;
}

MapEditorLayerManager<MapEffectLayer, MapEditorEffectLayer> & MapEditor::GetEffectManager()
{
  return m_EffectLayers;
}

MapEditorLayerManager<MapVolume, MapEditorVolume> & MapEditor::GetVolumeManager()
{
  return m_Volumes;
}

MapEditorLayerManager<MapPath, MapEditorPath> & MapEditor::GetPathManager()
{
  return m_Paths;
}

MapEditorLayerManager<MapAnchor, MapEditorAnchor> & MapEditor::GetAnchorManager()
{
  return m_Anchors;
}

MapEditorSelector & MapEditor::GetSelector()
{
  return *m_Selector.get();
}

MapEditorLayerList & MapEditor::GetLayerList()
{
  return *m_LayerList.get();
}

MapEditorViewer & MapEditor::GetViewer()
{
  return *m_Viewer.get();
}

void MapEditor::SelectManualTile(int layer_index, uint64_t frame_id)
{
  m_Viewer->SetTool(MapEditorTool<MapEditorToolManualTileLayerDraw>{}, layer_index, false, frame_id);
  m_Selector->GetTileSelector()->SetSelectedTile(frame_id);
}

void MapEditor::SelectManualAnimation(int layer_index, uint64_t frame_id)
{
  m_Viewer->SetTool(MapEditorTool<MapEditorToolManualTileLayerDraw>{}, layer_index, true, frame_id);
  m_Selector->GetTileSelector()->SetSelectedAnimation(frame_id);
}

void MapEditor::SetSelectedEntity(int layer_index, czstr entity_file)
{
  m_Viewer->SetTool(MapEditorTool<MapEditorToolEntityLayerDraw>{}, layer_index, entity_file);
  m_Selector->GetEntitySelector()->SetSelectedEntity(entity_file);
}

void MapEditor::SetSelectedServerObject(int layer_index, czstr server_object_file)
{
  m_Viewer->SetTool(MapEditorTool<MapEditorToolServerObjectLayerDraw>{}, layer_index, server_object_file);
  m_Selector->GetServerObjectSelector()->SetSelectedServerObject(server_object_file);
}

void MapEditor::SetSelectedParalaxObject(int layer_index, const MapParalaxLayerObject & paralax_object_data)
{
  m_ParalaxInitData = paralax_object_data;

  auto property_data = GetProperyMetaData<MapParalaxLayerObject>(GetPropertyFieldDatabase());
  m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_ParalaxInitData; }, "");

  m_Viewer->SetTool(MapEditorTool<MapEditorToolParalaxObjectLayerDraw>{}, layer_index);
  m_Selector->GetParalaxObjectSelector()->SetSelectedParalaxObject(paralax_object_data.m_File.data());
}

void MapEditor::ClearPropertyPanel()
{
  m_PropertyEditor->Unload();
}

void MapEditor::ClearSelectors()
{
  m_Selector->GetTileSelector()->hide();
  m_Selector->GetTileSelector()->Clear();
  m_Selector->GetEntitySelector()->hide();
  m_Selector->GetEntitySelector()->Clear();
  m_Selector->GetServerObjectSelector()->hide();
  m_Selector->GetServerObjectSelector()->Clear();
}

const RPolymorphic<VolumeDataBase, VolumeTypeDatabase, VolumeDataTypeInfo> & MapEditor::GetVolumeInitData() const
{
  return m_VolumeInitData;
}

void MapEditor::CreateNewVolume(const Box & box)
{
  MapVolume vol;
  vol.m_XStart = box.m_Start.x;
  vol.m_YStart = box.m_Start.y;
  vol.m_XEnd = box.m_End.x;
  vol.m_YEnd = box.m_End.y;
  vol.m_VolumeData = m_VolumeInitData;
  
  auto type_info = m_VolumeInitData.GetTypeInfo();
  if (type_info)
  {
    vol.m_Name = type_info->m_Name;
  }
  else
  {
    vol.m_Name = "Volume";
  }

  m_Map.m_Volumes.EmplaceBack(vol);
}

const RPolymorphic<PathDataBase, PathTypeDatabase, PathDataTypeInfo> & MapEditor::GetPathInitData() const
{
  return m_PathInitData;
}

void MapEditor::CreateNewPath(const Line & line)
{
  MapPath path;
  path.m_PathData = m_PathInitData;
 
  MapPathPoint start;
  start.m_X = line.m_Start.x;
  start.m_Y = line.m_Start.y;

  MapPathPoint end;
  end.m_X = line.m_End.x;
  end.m_Y = line.m_End.y;

  path.m_Points.EmplaceBack(start);
  path.m_Points.EmplaceBack(end);

  auto type_info = m_PathInitData.GetTypeInfo();
  if (type_info)
  {
    path.m_Name = type_info->m_Name;
  }
  else
  {
    path.m_Name = "Path";
  }

  m_Map.m_Paths.EmplaceBack(path);
}

const RPolymorphic<AnchorDataBase, AnchorTypeDatabase, AnchorDataTypeInfo> & MapEditor::GetAnchorInitData() const
{
  return m_AnchorInitData;
}

void MapEditor::CreateNewAnchor(const Vector2 & point)
{
  MapAnchor anchor;
  anchor.m_AnchorData = m_AnchorInitData;
  anchor.m_X = point.x;
  anchor.m_Y = point.y;

  auto type_info = m_AnchorInitData.GetTypeInfo();
  if (type_info)
  {
    anchor.m_Name = type_info->m_Name;
  }
  else
  {
    anchor.m_Name = "Anchor";
  }

  m_Map.m_Anchors.EmplaceBack(anchor);
}

MapParalaxLayerObject & MapEditor::GetParalaxObjectInitData() 
{
  return m_ParalaxInitData;
}

MapEditorParalaxObjectType & MapEditor::GetParalaxObject()
{
  return m_ParalaxInitObject;
}

void MapEditor::CreateNewParalaxObject(int layer_index, const Vector2 & point)
{
  m_ParalaxInitData.m_XPosition = point.x;
  m_ParalaxInitData.m_YPosition = point.y;
  m_ParalaxLayers.GetLayerManager(layer_index)->AddParalaxObject(m_ParalaxInitData);
}

void MapEditor::AboutToClose()
{
  m_IgnoreSelectionChanges = true;
}

REGISTER_EDITOR("Map", MapEditor, MapDef, ".map", "Maps");
