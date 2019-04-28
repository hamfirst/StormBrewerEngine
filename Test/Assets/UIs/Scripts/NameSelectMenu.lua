
name_repick = true

function InitNameSelectMenu()

  local instructions = PushMenuElement(Label:new())
  instructions.x = -130
  instructions.y = 20
  instructions.height = 70
  instructions.width = 260
  instructions.text = "Must be 3-16 characters\nOnly letters and numbers allowed"
  instructions.centered = true

  local error = PushMenuElement(Label:new())
  error.x = -130
  error.y = -100
  error.height = 70
  error.width = 260
  error.text = "Invalid User Name"
  error.centered = true
  error.r = 1
  error.g = 0.2
  error.b = 0.2
  error.alpha = 0

  if name_repick then
    print("repick ")
    local repick = PushMenuElement(Label:new())
    repick.x = -130
    repick.y = -70
    repick.height = 70
    repick.width = 260
    repick.text = "That user name is already taken"
    repick.centered = true
    repick.r = 1
    repick.g = 0.2
    repick.b = 0.2
    repick.alpha = 4
    AddLerp(repick, "alpha", 0, 8)
  end

  local input = PushMenuElement(TextInput:new())
  input.x = -130
  input.y = 5
  input.width = 260
  input.height = 20
  input.prompt = "Enter your name"
  input:SetInputValidator(function (text) return game:CheckValidUserName(text) end)

  local submit = PushMenuElement(Button:new())
  submit.x = 60
  submit.y = -20
  submit.width = 70
  submit.height = 20
  submit.text = "Submit"

  function submit:Clicked()
    if game:CheckSubmitValidUserName(input:GetText()) then
      Button.Clicked(self)
    else
      ui:PlayAudio(error_audio)

      error.alpha = 0
      error.y = -70

      AddLerp(error, "alpha", 1, 0.1)
      AddLerp(error, "y", -100, 0.3, nil, EaseOutBounce)
    end
  end

  local cancel = PushMenuElement(Button:new())
  cancel.x = -130
  cancel.y = -20
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Cancel"
  cancel.back = true

  CreateDefualtControls();

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  FadeFromButtonPress(fader, submit, function() game:Submit(input:GetText()) end)
  FadeFromButtonPress(fader, cancel, function() game:Back() end)
  BindInputEnterToButton(input, submit)

end


