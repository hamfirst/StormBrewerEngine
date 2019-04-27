
title_image_texture = loader:LoadTexture("./Images/GameTitle.png")

function InitMainMenu()

  local title_image = PushMenuElement(Texture:new())
  title_image:SetTexture(title_image_texture)
  title_image.x = screen_start_x
  title_image.y = screen_end_y - title_image.height

  local play_menu = PushMenuElement(QuickMenu:new())
  local start_menu = PushMenuElement(QuickMenu:new())

  if game.allow_local then
    play_menu:PushMenuAction("Play Online", function() game:PlayOnline() end)
    play_menu:PushMenuAction("Play Local", function() game:PlayOffline() end)
    
    start_menu = PushMenuElement(QuickMenu:new())
    start_menu:PushSubMenu("Play", play_menu)
  else
    start_menu = PushMenuElement(QuickMenu:new())
    start_menu:PushMenuAction("Play Online", function() game:PlayOnline() end)
  end

  if game.allow_tutorial then
    start_menu:PushMenuAction("Tutorial", function() game:Tutorial() end)
  end

  if game.allow_quit then
    start_menu:SetBottomButton("Quit", function () fader:FadeToSolidThen(function() game:Quit() end) end)
  end

  start_menu:Show()
  
  CreateDefualtControls()
  CreatePopupFader()

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()
end