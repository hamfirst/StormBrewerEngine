
time_to_wait = "test"

function InitFindingMatchMenu()

  local time_delayed = 0

  local label = PushMenuElement(Label:new())
  label.x = -100
  label.y = 10
  label.width = 250
  label.height = 50
  label.font = large_header_font
  label.alpha = 1
  label.text = "Searching For Match"
  label.centered = false

  local timer = PushMenuElement(Label:new())
  timer.x = -100
  timer.y = -10
  timer.width = 200
  timer.height = 50
  timer.font = font
  timer.alpha = 1
  timer.centered = true

  function timer:Update()
    timer.text = time_to_wait
  end

  local cancel = PushMenuElement(Button:new())
  cancel.x = screen_end_x -130
  cancel.y = screen_start_y + 30
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Back"
  cancel.back = true

  cancel.Pressed = function()
    game:Back()
  end

  function label:Update(dt)
    time_delayed = time_delayed + dt
    local periods = math.fmod(time_delayed * 5, 3)

    label.text = "Searching For Match"
    for i=0, periods + 1 do
      label.text = label.text .. "."
    end
  end

  CreateDefualtControls()

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()
end

