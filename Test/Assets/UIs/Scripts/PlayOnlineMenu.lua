
title_image_texture = loader:LoadTexture("./Images/GameTitle.png")

function InitPlayOnlineMenu()

  local play_menu = PushMenuElement(QuickMenu:new())
  play_menu:PushMenuAction("Host", function() game:CreatePrivate() end)
  play_menu:PushMenuAction("Join", function() game:JoinPrivate() end)
  
  local start_menu = PushMenuElement(QuickMenu:new())
  start_menu:PushMenuAction("Ranked", function() game:SearchCompetitive() end)
  start_menu:PushMenuAction("Casual", function() game:SearchCasual() end)
  start_menu:PushSubMenu("Private", play_menu)

  start_menu:SetBottomButton("Back", function () fader:FadeToSolidThen(function() game:Back() end) end)

  start_menu:Show()
  
  CreateDefualtControls()
  CreatePopupFader()

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()
end
