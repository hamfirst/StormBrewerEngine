
#include <QFile>

#include <unordered_set>

#include "StormData/StormDataParent.h"

#include "Foundation/Buffer/Buffer.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Runtime/Map/MapTileJson.h"
#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapCollision.h"
#include "Runtime/Collision/CollisionDatabase.h"

#include "EditorContainer.h"
#include "AssetEditors/DocumentEditor/DocumentEditor.h"
#include "AssetEditors/MapEditor/MapEditor.h"

#include "AssetEditors/MapEditor/MapEditorToolManualTileLayerDraw.h"
#include "AssetEditors/MapEditor/MapEditorToolManualTileLayerSelect.h"
#include "AssetEditors/MapEditor/MapEditorToolEntityLayerDraw.h"
#include "AssetEditors/MapEditor/MapEditorToolEntityLayerSelect.h"
#include "AssetEditors/MapEditor/MapEditorToolServerObjectLayerDraw.h"
#include "AssetEditors/MapEditor/MapEditorToolServerObjectLayerSelect.h"
#include "AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerDraw.h"
#include "AssetEditors/MapEditor/MapEditorToolParallaxObjectLayerSelect.h"
#include "AssetEditors/MapEditor/MapEditorToolVolumeCreate.h"
#include "AssetEditors/MapEditor/MapEditorToolVolumeEditor.h"
#include "AssetEditors/MapEditor/MapEditorToolVolumeMultiEditor.h"
#include "AssetEditors/MapEditor/MapEditorToolPathCreate.h"
#include "AssetEditors/MapEditor/MapEditorToolPathEditor.h"
#include "AssetEditors/MapEditor/MapEditorToolPathMultiEditor.h"
#include "AssetEditors/MapEditor/MapEditorToolAnchorCreate.h"
#include "AssetEditors/MapEditor/MapEditorToolAnchorEditor.h"
#include "AssetEditors/MapEditor/MapEditorToolAnchorMultiEditor.h"
#include "AssetEditors/MapEditor/MapEditorTypes.refl.meta.h"

MapEditor::MapEditor(EditorContainer & editor_container, PropertyFieldDatabase & property_db, const std::string & root_path, MapDef & map, 
  DocumentChangeLinkDelegate && change_link_callback, DocumentBeginTransactionDelegate && begin_transaction_callback, DocumentCommitChangesDelegate && commit_change_callback, QWidget *parent) :
  DocumentEditorWidgetBase(editor_container, property_db, root_path, std::move(change_link_callback), std::move(begin_transaction_callback), std::move(commit_change_callback), parent),
  m_Map(map),
  m_ManualTileLayers(".m_ManualTileLayers", this, m_Map, m_Map.m_ManualTileLayers),
  m_EntityLayers(".m_EntityLayers", this, m_Map, m_Map.m_EntityLayers),
  m_ServerObjectLayers(".m_ServerObjectLayers", this, m_Map, m_Map.m_ServerObjectLayers),
  m_ParallaxLayers(".m_ParallaxLayers", this, m_Map, m_Map.m_ParallaxLayers),
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

  SetNotifyCallback(m_ParallaxInitData, [](void * this_ptr, const ReflectionChangeNotification & change)
  {
    MapEditor * editor = static_cast<MapEditor *>(this_ptr);
    editor->m_ParallaxInitObject = MapEditorParallaxLayer::CreateObjectFromPath(editor->m_ParallaxInitData.m_File.data(), [] {});
  }, this);

  m_PropertyEditor = m_Properties->CreateWidget<PropertyEditor>();
  setLayout(m_Layout.get());

  m_Textures.Emplace();

  QFile vfx_file(":/EditorContainer/Resources/Vfx.png");
  if (vfx_file.open(QIODevice::ReadOnly))
  {
    auto vfx_file_data = vfx_file.readAll();
    m_Textures->m_VfxTexture = TextureAsset::SideLoad(":/EditorContainer/Resources/Vfx.png", vfx_file_data.data(), vfx_file_data.size());
  }
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
    m_PropertyEditor->LoadStruct(this, m_Map.m_PathfindingInfo,
      [this, index = layer.m_Index]() -> void * { return &m_Map.m_PathfindingInfo; }, true);
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
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ManualTileLayers.TryGet(static_cast<int>(index)); }, true);

    m_Selector->GetTileSelector()->show();
    m_Selector->GetTileSelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParallaxObjectSelector()->Clear();
    m_Selector->GetParallaxObjectSelector()->hide();

    m_Selector->GetTileSelector()->LoadManualTileLayer(layer.m_Index);
    break;
  case MapEditorLayerItemType::kEntityLayer:

    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->show();
    m_Selector->GetEntitySelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParallaxObjectSelector()->Clear();
    m_Selector->GetParallaxObjectSelector()->hide();
    m_PropertyEditor->LoadStruct(this, m_Map.m_EntityLayers[layer.m_Index], 
      [this, index = layer.m_Index]() -> void * { return m_Map.m_EntityLayers.TryGet(static_cast<int>(index)); }, true);
    break;
  case MapEditorLayerItemType::kServerObjectLayer:

    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->show();
    m_Selector->GetServerObjectSelector()->SetLayer((int)layer.m_Index);
    m_Selector->GetParallaxObjectSelector()->Clear();
    m_Selector->GetParallaxObjectSelector()->hide();
    m_PropertyEditor->LoadStruct(this, m_Map.m_ServerObjectLayers[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ServerObjectLayers.TryGet(static_cast<int>(index)); }, true);
    break;
  case MapEditorLayerItemType::kEntity:

    ClearSelectors();
    
    m_PropertyEditor->LoadStruct(this, m_Map.m_EntityLayers[layer.m_Index].m_Entities[layer.m_SubIndex], 
      [this, index = layer.m_Index, subindex = layer.m_SubIndex]() -> void * 
      { 
        auto layer = m_Map.m_EntityLayers.TryGet(static_cast<int>(index));
        auto entity = layer ? layer->m_Entities.TryGet(static_cast<int>(subindex)) : nullptr;
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
        auto layer = m_Map.m_ServerObjectLayers.TryGet(static_cast<int>(index));
        auto server_object = layer ? layer->m_Objects.TryGet(subindex) : nullptr; 
        return server_object;
      }, true
    );

    if (change_viewer_position)
    {
      m_Viewer->ZoomToServerObject(layer.m_Index, layer.m_SubIndex);
    }
    break;

  case MapEditorLayerItemType::kParallaxLayer:

    ClearSelectors();
    m_PropertyEditor->LoadStruct(this, m_Map.m_ParallaxLayers[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_ParallaxLayers.TryGet(static_cast<int>(index)); }, true);
    break;

  case MapEditorLayerItemType::kCreateParallaxObject:
    m_Selector->GetTileSelector()->hide();
    m_Selector->GetTileSelector()->Clear();
    m_Selector->GetEntitySelector()->Clear();
    m_Selector->GetEntitySelector()->hide();
    m_Selector->GetServerObjectSelector()->Clear();
    m_Selector->GetServerObjectSelector()->hide();
    m_Selector->GetParallaxObjectSelector()->show();
    m_Selector->GetParallaxObjectSelector()->SetLayer((int)layer.m_Index);

    {
      auto property_data = GetProperyMetaData<MapParallaxLayerObject>(GetPropertyFieldDatabase());
      m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_ParallaxInitData; }, "");
    }

    break;

  case MapEditorLayerItemType::kParallaxObject:

    ClearSelectors();
    
    m_PropertyEditor->LoadStruct(this, m_Map.m_ParallaxLayers[layer.m_Index].m_Objects[layer.m_SubIndex],
      [this, index = layer.m_Index, subindex = layer.m_SubIndex]() -> void * 
      { 
        auto layer = m_Map.m_ParallaxLayers.TryGet(static_cast<int>(index));
        auto parallax_object = layer ? layer->m_Objects.TryGet(subindex) : nullptr;
        return parallax_object;
      }, true
    );

    if (change_viewer_position)
    {
      m_Viewer->ZoomToParallaxObject(layer.m_Index, layer.m_SubIndex);
    }
    break;

  case MapEditorLayerItemType::kEffectLayer:

    ClearSelectors();
    m_PropertyEditor->LoadStruct(this, m_Map.m_EffectLayers[layer.m_Index], 
      [this, index = layer.m_Index]() -> void * { return m_Map.m_EffectLayers.TryGet(static_cast<int>(index)); }, true);
    break;

  case MapEditorLayerItemType::kCreateVolume:
    ClearSelectors();

    {
      auto property_data = GetProperyMetaData<RPolymorphic<VolumeDataBase>>(GetPropertyFieldDatabase());
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
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Volumes.TryGet(static_cast<int>(index)); }, true);

    if (change_viewer_position)
    {
      m_Viewer->ZoomToVolume(layer.m_Index);
    }
    break;

  case MapEditorLayerItemType::kCreatePath:

    ClearSelectors();

    {
      auto property_data = GetProperyMetaData<RPolymorphic<PathDataBase>>(GetPropertyFieldDatabase());
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
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Paths.TryGet(static_cast<int>(index)); }, true);

    if (change_viewer_position)
    {
      m_Viewer->ZoomToPath(layer.m_Index);
    }
    break;

  case MapEditorLayerItemType::kCreateAnchor:

    ClearSelectors();
    m_PropertyEditor->LoadStruct(this, m_AnchorInitData, true);

    break;

  case MapEditorLayerItemType::kAllAnchors:

    ClearSelectors();
    m_PropertyEditor->Unload();
    break;

  case MapEditorLayerItemType::kAnchor:

    ClearSelectors();

    m_PropertyEditor->LoadStruct(this, m_Map.m_Anchors[layer.m_Index],
      [this, index = layer.m_Index]() -> void * { return m_Map.m_Anchors.TryGet(static_cast<int>(index)); }, true);

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
  case MapEditorLayerItemType::kParallaxLayer:
  case MapEditorLayerItemType::kCreateParallaxObject:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolParallaxObjectLayerSelect>{}, (int)layer.m_Index);
    break;
  case MapEditorLayerItemType::kParallaxObject:
    m_ParallaxLayers.GetLayerManager(layer.m_Index)->SetSingleSelection(layer.m_SubIndex);
    m_Viewer->SetTool(MapEditorTool<MapEditorToolParallaxObjectLayerSelect>{}, (int)layer.m_Index);
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
    m_Viewer->SetTool(MapEditorTool<MapEditorToolAnchorMultiEditor>{}, -1);
    break;
  case MapEditorLayerItemType::kAnchor:
    m_Viewer->SetTool(MapEditorTool<MapEditorToolAnchorMultiEditor>{}, (int)layer.m_Index);
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
  for (auto elem : m_Map.m_PathfindingInfo.m_CollisionMask)
  {
    collision_hashes.push_back(crc32(elem.second.ToString()));
  }

  auto box_multi_list = ExtractMapCollision(m_Map, Vector2{}, collision_hashes);
  StaticCollisionDatabase coll_database(box_multi_list.size());
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

  info.m_GridWidth = m_Map.m_PathfindingInfo.m_GridWidth;
  info.m_GridHeight = m_Map.m_PathfindingInfo.m_GridHeight;

  auto size = bounds.Value().Size();

  info.m_StartX = bounds->m_Start.x - info.m_GridWidth * 3;
  info.m_StartY = bounds->m_Start.y - info.m_GridHeight * 3;
  info.m_SizeX = (size.x + info.m_GridWidth * 6 + info.m_GridWidth - 1) / info.m_GridWidth;
  info.m_SizeY = (size.y + info.m_GridHeight * 6 + info.m_GridHeight - 1) / info.m_GridHeight;
  info.m_GridInfo.reserve(info.m_SizeX * info.m_SizeY);

  info.m_StartX = RoundDownInt(info.m_StartX, info.m_GridWidth);
  info.m_StartY = RoundDownInt(info.m_StartY, info.m_GridHeight);
  info.m_SizeX = RoundUpInt(info.m_SizeX, info.m_GridWidth);
  info.m_SizeY = RoundUpInt(info.m_SizeY, info.m_GridHeight);

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
      info.m_GridInfo.push_back(std::make_tuple(grid_val, (uint8_t)0, (uint8_t)0));
    }
  }

  int clearance_x = m_Map.m_PathfindingInfo.m_MaximumClearanceX / m_Map.m_PathfindingInfo.m_GridWidth;
  int clearance_y = m_Map.m_PathfindingInfo.m_MaximumClearanceY / m_Map.m_PathfindingInfo.m_GridHeight;
  if (clearance_x != 0 && clearance_y != 0)
  {
    auto test_grid = [&](int x, int y)
    {
      if (x < 0 || x >= info.m_SizeX || y < 0 || y >= info.m_SizeY)
      {
        return false;
      }

      return std::get<0>(info.m_GridInfo[y * info.m_SizeX + x]) != 0;
    };

    auto sample_grid_box = [&](int x, int y, int w, int h)
    {
      for (int ty = 0; ty <= h; ty++)
      {
        for (int tx = 0; tx <= w; tx++)
        {
          if (test_grid(x - tx, y - ty) == true ||
            test_grid(x - tx, y + ty) == true ||
            test_grid(x + tx, y - ty) == true ||
            test_grid(x + tx, y + ty) == true)
          {
            return true;
          }
        }
      }

      return false;
    };

    auto test_clearance = [&](int x, int y)
    {
      int w = 0;
      int h = 0;

      bool expand_x = true;
      bool expand_y = true;

      while (expand_x || expand_y)
      {
        if (expand_x)
        {
          if (sample_grid_box(x, y, w + 1, h) == false)
          {
            expand_x = false;
          }
          else
          {
            w++;
            if (w >= clearance_x)
            {
              expand_x = false;
            }
          }
        }

        if (expand_y)
        {
          if (sample_grid_box(x, y, w, h + 1) == false)
          {
            expand_y = false;
          }
          else
          {
            h++;
            if (h >= clearance_y)
            {
              expand_y = false;
            }
          }
        }
      }

      return std::make_pair(w, h);
    };

    for (int y = 0; y < info.m_SizeY; ++y)
    {
      for (int x = 0; x < info.m_SizeX; ++x)
      {
        if (test_grid(x, y))
        {
          continue;
        }

        auto clearance = test_clearance(x, y);
        auto & elem = info.m_GridInfo[y * info.m_SizeX + x];

        elem = std::make_tuple((uint8_t)0, (uint8_t)clearance.first, (uint8_t)clearance.second);
      }
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

      auto clearance = coll_database.CheckClearance(pos, m_Map.m_PathfindingInfo.m_MaximumClearance, 0xFFFFFFFF);
      if (clearance < m_Map.m_PathfindingInfo.m_MinimumClearance)
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

  BeginTransaction();
  m_Map.m_PathfindingInfo.m_CalculatedInfo = info;
  m_Map.m_PathfindingInfo.m_Valid = true;
  CommitChanges();
}

void MapEditor::ClearPathfindingInfo()
{
  BeginTransaction();
  MapPathfindingCalculatedInfo info = {};
  m_Map.m_PathfindingInfo.m_CalculatedInfo = info;
  m_Map.m_PathfindingInfo.m_Valid = false;
  CommitChanges();
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

MapEditorLayerManager<MapParallaxLayer, MapEditorParallaxLayer> & MapEditor::GetParallaxManager()
{
  return m_ParallaxLayers;
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

MapDef & MapEditor::GetMapDef()
{
  return m_Map;
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

void MapEditor::SetSelectedParallaxObject(int layer_index, const MapParallaxLayerObject & parallax_object_data)
{
  m_ParallaxInitData = parallax_object_data;

  auto property_data = GetProperyMetaData<MapParallaxLayerObject>(GetPropertyFieldDatabase());
  m_PropertyEditor->LoadObject(this, property_data, false, [this]() -> void * { return &m_ParallaxInitData; }, "");

  m_Viewer->SetTool(MapEditorTool<MapEditorToolParallaxObjectLayerDraw>{}, layer_index);
  m_Selector->GetParallaxObjectSelector()->SetSelectedParallaxObject(parallax_object_data.m_File.data());
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

const RPolymorphic<VolumeDataBase> & MapEditor::GetVolumeInitData() const
{
  return m_VolumeInitData;
}

void MapEditor::CreateNewVolume(const Box & box)
{
  MapVolume vol;
  vol.m_GUID = GetRandomNumber();
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

const RPolymorphic<PathDataBase> & MapEditor::GetPathInitData() const
{
  return m_PathInitData;
}

void MapEditor::CreateNewPath(const Line & line)
{
  MapPath path;
  path.m_GUID = GetRandomNumber();
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

const MapEditorAnchorInitData & MapEditor::GetAnchorInitData() const
{
  return m_AnchorInitData;
}

void MapEditor::CreateNewAnchor(const Vector2 & point)
{
  MapAnchor anchor;
  anchor.m_GUID = GetRandomNumber();
  anchor.m_AnchorData = m_AnchorInitData.m_InitData;
  anchor.m_Sprite = m_AnchorInitData.m_Sprite;
  anchor.m_X = point.x;
  anchor.m_Y = point.y;

  auto type_info = m_AnchorInitData.m_InitData.GetTypeInfo();
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

void MapEditor::DuplicateAnchorData(int layer_index)
{
  auto & anchor = m_Map.m_Anchors[layer_index];

  m_AnchorInitData.m_InitData = anchor.m_AnchorData;
  m_AnchorInitData.m_Sprite = anchor.m_Sprite;

  MapEditorLayerSelection layer_selection = {};
  layer_selection.m_Type = MapEditorLayerItemType::kCreateAnchor;
  ChangeLayerSelection(layer_selection);
}

MapParallaxLayerObject & MapEditor::GetParallaxObjectInitData()
{
  return m_ParallaxInitData;
}

MapEditorParallaxObjectType & MapEditor::GetParallaxObject()
{
  return m_ParallaxInitObject;
}

void MapEditor::CreateNewParallaxObject(int layer_index, const Vector2 & point)
{
  m_ParallaxInitData.m_XPosition = point.x;
  m_ParallaxInitData.m_YPosition = point.y;
  m_ParallaxLayers.GetLayerManager(layer_index)->AddParallaxObject(m_ParallaxInitData);
}

void MapEditor::CreateNewParallaxObject(czstr file_name, int layer_index, const Vector2 & point)
{
  auto type = MapEditorParallaxLayer::GetParallaxTypeForPath(file_name);
  if (type.IsValid() == false)
  {
    return;
  }

  m_ParallaxInitData = {};
  m_ParallaxInitData.m_File = file_name;
  m_ParallaxInitData.m_Name = GetFileStemForCanonicalPath(file_name);
  m_ParallaxInitData.m_XPosition = point.x;
  m_ParallaxInitData.m_YPosition = point.y;
  m_ParallaxInitData.m_Type = type.Value();
  m_ParallaxLayers.GetLayerManager(layer_index)->AddParallaxObject(m_ParallaxInitData);
}

MapEditorTextures & MapEditor::GetTextures()
{
  return m_Textures.Value();
}

NullOptPtr<MapDef> MapEditor::GetMap()
{
  return &m_Map;
}

void MapEditor::AboutToClose()
{
  m_IgnoreSelectionChanges = true;
  m_Textures.Clear();
}

REGISTER_EDITOR("Map", MapEditor, MapDef, ".map", "Maps");
