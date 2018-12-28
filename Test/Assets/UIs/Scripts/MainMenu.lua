
title_image_texture = loader:LoadTexture("./Images/GameTitle.png")

function InitMainMenu()

  local title_image = PushMenuElement(Texture:new())
  title_image:SetTexture(title_image_texture)
  title_image.x = screen_start_x
  title_image.y = screen_end_y - title_image.height

  local multiplayer = PushMenuElement(Button:new())
  multiplayer.toggleable = true
  multiplayer.x = screen_start_x + 30
  multiplayer.y = screen_start_y + 150
  multiplayer.width = 100
  multiplayer.height = 20
  multiplayer.text = "Multi-Player"

  local quickmatch = PushMenuElement(Button:new())
  quickmatch.x = screen_start_x + 150
  quickmatch.y = screen_start_y + 150
  quickmatch.width = 0
  quickmatch.height = 20
  quickmatch.text = "Quick Match"

  local createprivate = PushMenuElement(Button:new())
  createprivate.x = screen_start_x + 150
  createprivate.y = screen_start_y + 120
  createprivate.width = 0
  createprivate.height = 20
  createprivate.text = "Create Private Game"

  local joinprivate = PushMenuElement(Button:new())
  joinprivate.x = screen_start_x + 150
  joinprivate.y = screen_start_y + 90
  joinprivate.width = 0
  joinprivate.height = 20
  joinprivate.text = "Join Private Game"

  local localmulti = PushMenuElement(Button:new())
  localmulti.x = screen_start_x + 150
  localmulti.y = screen_start_y + 60
  localmulti.width = 0
  localmulti.height = 20
  localmulti.text = "Local Multi-Player"

  local singleplayer = PushMenuElement(Button:new())
  singleplayer.x = screen_start_x + 30
  singleplayer.y = screen_start_y + 120
  singleplayer.width = 100
  singleplayer.height = 20
  singleplayer.text = "Single-Player"

  local tutorial = PushMenuElement(Button:new())
  tutorial.x = screen_start_x + 30
  tutorial.y = screen_start_y + 90
  tutorial.width = 100
  tutorial.height = 20
  tutorial.text = "Tutorial"

  if game:CanQuit() then
    local quit = PushMenuElement(Button:new())
    quit.x = screen_start_x + 30
    quit.y = screen_start_y + 30
    quit.width = 100
    quit.height = 20
    quit.text = "Quit"

    quit.Pressed = function () game:Quit() end
  end

  CreateDefualtControls();

  local fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  multiplayer.ToggleOn = function()
    AddLerp(quickmatch, "width", 150, 0.1, nil, EaseInCubic)
    AddLerp(createprivate, "width", 150, 0.1, nil, EaseInCubic)
    AddLerp(joinprivate, "width", 150, 0.1, nil, EaseInCubic)
    AddLerp(localmulti, "width", 150, 0.1, nil, EaseInCubic)
  end

  multiplayer.ToggleOff = function()
    AddLerp(quickmatch, "width", 0, 0.1, nil, EaseInCubic)
    AddLerp(createprivate, "width", 0, 0.1, nil, EaseInCubic)
    AddLerp(joinprivate, "width", 0, 0.1, nil, EaseInCubic)
    AddLerp(localmulti, "width", 0, 0.1, nil, EaseInCubic)
  end

  FadeFromButtonPress(fader, quickmatch, function() game:PlayOnline() end)
  FadeFromButtonPress(fader, createprivate, function() game:CreatePrivateMatch() end)
  FadeFromButtonPress(fader, joinprivate, function() game:JoinPrivateMatch() end)
  FadeFromButtonPress(fader, localmulti, function() game:PlayOffline() end)
  FadeFromButtonPress(fader, singleplayer, function() game:PlaySingleplayer() end)
  FadeFromButtonPress(fader, tutorial, function() game:Tutorial() end)
end


