

function InitQuitMenu()

  CreatePopupFader()
  local default_controls = CreateDefualtControls()

  FadeInDefaultControls(default_controls)

  local quitpopup = PushMenuElement(ConfirmPopup:new())
  quitpopup.x = -150
  quitpopup.y = -75
  quitpopup.width = 300
  quitpopup.height = 150
  quitpopup.text = "Quit Out Of The Game?"
  quitpopup:FadeIn()
  
  fader = PushMenuElement(Fader:new())
  fader:SetAlpha(0)

  quitpopup.OkayPressed = function()
    fader:FadeToSolidThen(function() game:Quit() end)
  end

  quitpopup.CancelPressed = function()
    game:CancelPopup()
  end
end

