#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"
#include "Engine/UI/UIElementExprTypes.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/UI/UIDef.refl.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

#include "StormExpr/StormExprDynamicBlock.h"
#include "StormExpr/StormExprReflBlock.h"
#include "StormExpr/StormExprBinding.h"
#include "StormExpr/StormExprEval.h"


class RenderState;
class RenderUtil;

enum class UIElementState
{
  kInactive,
  kActive,
  kHover,
  kPressed,
};

using UIOnClickHandler = Delegate<void, NotNullPtr<UIElement>>;
using UIOnStateChangeHandler = Delegate<void, UIElementState, UIElementState>;
using UIOnUpdateHandler = Delegate<void, NotNullPtr<UIElement>>;

class UIElement
{
public:

  UIElement();
  virtual ~UIElement();

  virtual void Update(float dt);
  virtual void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  virtual NotNullPtr<UIElementDataBase> GetBaseData() = 0;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() = 0;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() = 0;

  void SetActive(bool active = true);
  void SetInactive();

  void SetEnabled(bool enabled = true);
  void SetDisabled();

  void Destroy();

  UIElementHandle GetHandle();
  NotNullPtr<UIManager> GetManager();

  UIElementState GetState();
  Optional<Box> GetActiveArea();

  NullOptPtr<UIElement> GetChild(uint32_t child_name_hash);
  NullOptPtr<UIElement> GetParent();

  void SetOnUpdateHandler(UIOnUpdateHandler && handler);
  void SetOnClickHandler(UIOnClickHandler && handler);
  void SetOnStateChangeHandler(UIOnStateChangeHandler && handler);

  void SetInput(uint32_t variable_name, float val);
  void SetInput(uint32_t variable_name, const std::string & val);
  void SetInput(uint32_t variable_name, czstr val);

protected:

  std::vector<std::pair<std::string, StormExprDynamicBlockVariable>> InitializeExprBlock(const UIDef & def, 
    NullOptPtr<StormExprValueInitBlock> parent_init_block, void * parent_data,
    NullOptPtr<StormExprValueInitBlock> parent_auto_init_block, void * parent_auto_data,
    UIManager & manager, std::vector<std::string> & errors, bool use_default_inputs);

  const std::string & GetName() const;

  void SetActiveArea(const Box & box);
  void SetOffset(const Vector2 & offset);

  virtual StormExprValueInitBlock & GetLocalInitBlock() = 0;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() = 0;
  virtual StormExprBindingList & GetBindingList() = 0;

private:

  template <typename Type>
  friend class SkipField;

  friend class UIManager;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

private:
  struct BindingEvalInfo
  {
    StormExprBinding m_Binding;
    void * m_BasePtr;
    int m_FunctionIndex;
  };

  struct ChildBindingEvalInfo
  {
    StormExprBinding m_Binding;
    void * m_BasePtr;
    UIElementHandle m_Handle;
    int m_FunctionIndex;
  };

private:

  UIElementHandle m_Handle;
  SkipFieldIterator m_Iterator;

  std::string m_Name;
  uint32_t m_NameHash;
  NullOptPtr<UIElement> m_Parent;
  std::vector<NotNullPtr<UIElement>> m_Children;

  UIOnClickHandler m_OnClick;
  UIOnStateChangeHandler m_OnStateChange;
  UIOnUpdateHandler m_OnUpdate;

  Box m_ActiveArea;
  Vector2 m_Offset;
  UIElementState m_State = UIElementState::kInactive;
  float m_TimeCreated;

  UIAutoCalculatedBlock m_AutoBlock;
  StormExprDynamicBlock m_InputBlock;
  Optional<StormExprValueBlock> m_FloatInputValueBlock;
  Optional<StormExprValueBlock> m_StringInputValueBlock;
  std::vector<std::pair<uint32_t, StormExprDynamicBlockVariable>> m_InputLookup;
  std::vector<BindingEvalInfo> m_BindingList;
  std::vector<ChildBindingEvalInfo> m_ChildBindingList;

  Optional<StormExprEval> m_Eval;
};
