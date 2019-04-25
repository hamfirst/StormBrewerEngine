
title_image_texture = loader:LoadTexture("./Images/GameTitle.png")

cancel_connect = false

function FinalizeConnect()
  if cancel_connect then
    game:Back()
  else
    game:ConnectComplete()
  end
end

function InitConnectingMenu()

  cancel_connect = false
  local time_delayed = 0

  local label = PushMenuElement(Label:new())
  label.x = -50
  label.y = 10
  label.width = 200
  label.height = 50
  label.font = large_header_font
  label.alpha = 0
  label.text = "Connecting"
  label.centered = false

  local cancel = PushMenuElement(Button:new())
  cancel.x = screen_end_x -130
  cancel.y = screen_start_y + 30
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Back"
  cancel.back = true
  cancel.pressable = false

  cancel.Pressed = function()
    fader:FadeToSolidThen(FinalizeConnect)
    cancel_connect = true
  end

  function label:Update(dt)
    time_delayed = time_delayed + dt

    if time_delayed < 2 then
      label.alpha = 0
    elseif time_delayed < 4 then
      label.alpha = (time_delayed - 2) / 2
    else
      label.alpha = 1
    end

    if time_delayed < 1 then
      cancel.alpha = 0
    elseif time_delayed < 2 then
      cancel.alpha = time_delayed - 1
    else
      cancel.alpha = 1
    end

    cancel.pressable = cancel.pressable or cancel.alpha > 0.5

    local periods = math.fmod(time_delayed * 5, 3)

    label.text = "Connecting"
    for i=1,periods + 1 do
      label.text = label.text .. "."
    end
  end

  CreateDefualtControls()

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()
end

function ConnectComplete()
  fader:FadeToSolidThen(FinalizeConnect)
end
