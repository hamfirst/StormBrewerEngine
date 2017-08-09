
#include "Engine/EngineCommon.h"

#include "Foundation/SkipField/SkipField.h"

#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Entity/EntityDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Event/EventSystem.h"

#include "Server/ServerObject/ServerObject.h"
#include "Server/ServerObject/ServerObjectHandle.h"

#include "Engine/EngineState.h"
#include "Engine/Entity/Entity.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/DrawList/DrawList.h"


SkipField<Entity> s_EntityAllocator;

EntitySystem::EntitySystem(NotNullPtr<EngineState> engine_state, NotNullPtr<GameContainer> game) :
  m_EngineState(engine_state),
  m_GameContainer(game),
  m_EventSystem(std::make_unique<EntityEventSystem>())
{
  m_EntityAllocator = new SkipField<Entity>();
}

EntitySystem::~EntitySystem()
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  delete allocator;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), ServerObjectHandle{}, m_GameContainer);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(NotNullPtr<EntityDef> entity_def, bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), ServerObjectHandle{}, m_GameContainer);

  if (entity_def->m_Sprite.length() > 0)
  {
    ptr->m_Sprite = SpriteResource::Load(entity_def->m_Sprite.data());
    ptr->SetDefaultFrame();
  }

  AddComponentsToEntity(entity_def, ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

NotNullPtr<Entity> EntitySystem::CreateEntity(NotNullPtr<EntityResource> entity_resource, NullOptPtr<ServerObject> server_object, bool activate)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  auto ptr = allocator->Allocate(m_EngineState, m_EventSystem.get(), server_object->GetObjectHandle(), m_GameContainer);

  ptr->m_Sprite = entity_resource->m_Sprite;
  ptr->m_AssetHash = entity_resource->m_FileNameHash;
  ptr->SetDefaultFrame();

  AddComponentsToEntity(entity_resource->GetData(), ptr);

  if (activate)
  {
    ptr->Activate();
  }

  return ptr;
}

void EntitySystem::AddComponentsToEntity(NotNullPtr<EntityDef> entity_def, NotNullPtr<Entity> entity)
{
  for (auto elem : entity_def->m_Components)
  {
    auto & init_data = elem.second;
    if (init_data.GetValue() == nullptr)
    {
      continue;
    }

    auto comp = m_EngineState->m_ComponentSystem->CreateComponentFromTypeNameHash(init_data.GetTypeNameHash(), init_data.GetValue());
    if (comp == nullptr)
    {
      continue;
    }

    entity->AddComponentInternal(comp);
  }
}

void EntitySystem::DestroyEntity(NotNullPtr<Entity> entity)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->Release(entity);
}

NullOptPtr<Entity> EntitySystem::ResolveHandle(const EntityHandle & handle)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  return allocator->ResolveHandle(handle);
}

void EntitySystem::FindAllEntitiesWithName(czstr name, std::vector<NotNullPtr<Entity>> & outp_entities)
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->VisitAll([&](Entity & entity) {
    if (entity.GetName() == name)
    {
      outp_entities.push_back(&entity);
    }
  });
}

void EntitySystem::DestroyAllEntities()
{
  auto allocator = static_cast<SkipField<Entity> *>(m_EntityAllocator);
  allocator->VisitAll([](Entity & entity) {
    entity.Destroy();
  });
}


void EntitySystem::FinalizeEvents()
{
  m_EventSystem->FinalizeEvents();
}

void EntitySystem::DrawAllEntities(const Box & viewport_bounds, DrawList & draw_list)
{
  auto entity_alloc = static_cast<SkipField<Entity> *>(m_EntityAllocator);

  entity_alloc->VisitAll([&](Entity & entity)
  {
    auto & pos = entity.GetPosition();
    auto & render_state = entity.GetRenderState();
    if (render_state.m_Draw == false || entity.m_Activated == false)
    {
      return;
    }

    if (pos.x + render_state.m_FrameWidth / 2 < viewport_bounds.m_Start.x ||
      pos.y + render_state.m_FrameHeight / 2 < viewport_bounds.m_Start.y ||
      pos.x - render_state.m_FrameWidth / 2 > viewport_bounds.m_End.x ||
      pos.y - render_state.m_FrameHeight / 2 > viewport_bounds.m_End.y)
    {
      return;
    }

#ifdef USE_Z_ORDERING
    int draw_order = pos.y - render_state.m_FrameHeight / 2 + render_state.m_LowerEdge;
#else
    int draw_order = 0;
#endif

    draw_list.PushDraw(entity.GetLayer(), draw_order, [this, e = &entity](GameContainer & game_container, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
    {
      DrawEntity(e, viewport_bounds, screen_center, render_state, render_util);
    });
  });
}

void EntitySystem::DrawEntity(NullOptPtr<Entity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center, RenderState & render_state, RenderUtil & render_util)
{
  if (entity->m_CustomDraw)
  {
    entity->m_CustomDraw(viewport_bounds, screen_center, render_state, render_util);
  }
  else
  {
    DefaultDrawEntity(entity, viewport_bounds, screen_center);
  }
}

void EntitySystem::DefaultDrawEntity(NullOptPtr<Entity> entity, const Box & viewport_bounds, const RenderVec2 & screen_center)
{
  auto & sprite = entity->GetSprite();
  auto & render_state = entity->GetRenderState();

  SpriteEngineData::RenderSprite(sprite, render_state.m_AnimIndex, render_state.m_AnimFrame,
    RenderVec2{ entity->GetPosition() } - screen_center, render_state.m_Matrix, render_state.m_Color);
}
