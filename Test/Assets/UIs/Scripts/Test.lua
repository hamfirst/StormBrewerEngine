
function InitMenu()
  print("Testing menu ")

  local button = PushMenuElement(Button:new())
  button.x = 0
  button.y = 0
  button.width = 100
  button.height = 15
  button.text = "Test"

  local button2 = PushMenuElement(Button:new())
  button2.x = 0
  button2.y = 20
  button2.width = 100
  button2.height = 15
  button2.text = "Test2"

  local input = PushMenuElement(TextInput:new())
  input.x = 0
  input.y = -40
  input.width = 100
  input.height = 15
  input.prompt = "Input"

  local default_controls = PushMenuElement(DefaultControls:new())
  default_controls.x = ScreenWidth / 2 - 120
  default_controls.y = ScreenHeight / 2 - 40

  local popup = PushMenuElement(ConfirmPopup:new())
  popup.x = -400
  popup.y = -100
  popup.width = 300
  popup.height = 150
  
  local fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  button.Pressed = function()
    fader:FadeToSolid()
  end

  button2.Pressed = function()
    fader:FadeToSolid()
  end
end

function CleanupMenu()
  print("Cleaning up menu")
  ClearMenuElements()
end

