
title_image_texture = loader:LoadTexture("./Images/GameTitle.png")

function InitMainMenu()

  local title_image = PushMenuElement(Texture:new())
  title_image:SetTexture(title_image_texture)
  title_image.x = screen_start_x
  title_image.y = screen_end_y - title_image.height

  local online_menu = PushMenuElement(QuickMenu:new())
  online_menu:PushMenuAction("Play Ranked", function() game:Quit() end)
  online_menu:PushMenuAction("Play Casual", function() game:Quit() end)
  online_menu:PushMenuAction("Private Game", function() game:Quit() end)

  local play_menu = PushMenuElement(QuickMenu:new())
  play_menu:PushSubMenu("Play Online", online_menu)
  play_menu:PushMenuAction("Play Local", function() end)
  
  local start_menu = PushMenuElement(QuickMenu:new())
  start_menu:PushSubMenu("Play", play_menu)
  start_menu:PushMenuAction("Tutorial", function()  end)

  if game:CanQuit() then
    start_menu:SetBottomButton("Quit", function () game:Quit() end)
  end

  start_menu:Show()
  
  CreateDefualtControls();

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

end


