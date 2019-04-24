
function InitMapSettingsMenu()

  local mapsettings = PushMenuElement(MapSettings:new())
  mapsettings.x = -250
  mapsettings.width = 500
  mapsettings.y = -175
  mapsettings.height = 359

  local submit = PushMenuElement(Button:new())
  submit.x = 60
  submit.y = screen_start_y + 30
  submit.width = 70
  submit.height = 20
  submit.text = "Submit"

  local cancel = PushMenuElement(Button:new())
  cancel.x = -130
  cancel.y = screen_start_y + 30
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Cancel"
  cancel.back = true

  CreateDefualtControls();

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  FadeFromButtonPress(fader, submit, function() game:Submit() end)
  FadeFromButtonPress(fader, cancel, function() game:Back() end)

end


