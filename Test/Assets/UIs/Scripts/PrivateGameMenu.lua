

host_private_img = loader:LoadTexture("./Images/UI/Host.png")
join_private_img = loader:LoadTexture("./Images/UI/Join.png")

function InitPrivateGameMenu()

  local instructions = PushMenuElement(Label:new())
  instructions.x = -130
  instructions.y = 0
  instructions.height = 350
  instructions.width = 260
  instructions.text = "Private Game"
  instructions.centered = true

  local host = PushMenuElement(Button:new())
  host.x = 20
  host.y = -120
  host.width = 300
  host.height = 230
  host.text = "Host New Game"
  host.image = host_private_img
  host.image_a = 0.4

  local join = PushMenuElement(Button:new())
  join.x = -320
  join.y = -120
  join.width = 300
  join.height = 230
  join.text = "Join Existing Game"
  join.image = join_private_img
  join.image_a = 0.4

  local cancel = PushMenuElement(Button:new())
  cancel.x = screen_end_x - 100
  cancel.y = screen_start_y + 30
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Cancel"
  cancel.back = true

  CreateDefualtControls();

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  FadeFromButtonPress(fader, host, function() game:CreatePrivateMatch() end)
  FadeFromButtonPress(fader, join, function() game:JoinPrivateMatch() end)
  FadeFromButtonPress(fader, cancel, function() CleanupMenu() InitMainMenu() end)
end


