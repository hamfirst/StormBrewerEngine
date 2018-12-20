
logo = loader:LoadTexture("./Images/stormbrewers_logo.png")

function InitMenu()
  print("Testing menu ")

  texture = Texture:new()
  texture:SetTexture(logo)

  button = Button:new()
  button.x = 0
  button.y = 0
  button.width = 100
  button.height = 15
  button.text = "Test"

  button2 = Button:new()
  button2.x = 0
  button2.y = 20
  button2.width = 100
  button2.height = 15
  button2.text = "Test2"

  input = TextInput:new()
  input.x = 0
  input.y = -40
  input.width = 100
  input.height = 15
  input.prompt = "Input"
  
  fader = Fader:new()
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
end

