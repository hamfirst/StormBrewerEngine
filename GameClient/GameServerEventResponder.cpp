#include "GameClient/GameClientCommon.h"
#include "GameClient/GameServerEventResponder.h"
#include "GameClient/GameClientInstanceContainer.h"


GameServerEventResponder::GameServerEventResponder(bool authority, NullOptPtr<GameClientInstanceContainer> instance_container,
                                                   NullOptPtr<GameClientController> client_controller,
                                                   NullOptPtr<GameEventReconciler> reconciler, NullOptPtr<int> reconcile_frame) :
  m_Authority(authority),
  m_InstanceContainer(instance_container),
  m_ClientController(client_controller),
  m_Reconciler(reconciler),
  m_ReconcileFrame(reconcile_frame)
{

}

void GameServerEventResponder::SendGlobalEvent(std::size_t class_id, const void * event_ptr)
{
  if (m_ClientController)
  {
    m_ClientController->HandleGlobalEvent(class_id, event_ptr);
  }
}

void GameServerEventResponder::SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id)
{
  if (m_ClientController)
  {
    m_ClientController->HandleGlobalEvent(class_id, event_ptr);
  }
}

void GameServerEventResponder::SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle)
{

}

void GameServerEventResponder::SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle)
{

}

void GameServerEventResponder::SendAuthEvent(std::size_t class_id, const void * event_ptr)
{
  m_InstanceContainer->HandleLocalServerAuthorityEvent(class_id, event_ptr);
}

bool GameServerEventResponder::ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos)
{
  if (m_Reconciler)
  {
    return m_Reconciler->PushEvent(event_type_name_hash, event_id, pos, *m_ReconcileFrame);
  }

  return true;
}

