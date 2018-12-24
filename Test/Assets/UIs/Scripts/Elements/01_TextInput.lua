
TextInput = Elem:construct()
TextInput.prompt = ""
TextInput.border_r = 0.4
TextInput.border_g = 0.4
TextInput.border_b = 0.4
TextInput.border_hover_r = 0.1
TextInput.border_hover_g = 0.1
TextInput.border_hover_b = 0.7
TextInput.bkg_r = 0.96
TextInput.bkg_g = 0.96
TextInput.bkg_b = 1
TextInput.bkg_hover_r = 1
TextInput.bkg_hover_g = 1
TextInput.bkg_hover_b = 1
TextInput.text_r = 0
TextInput.text_g = 0
TextInput.text_b = 0
TextInput.prompt_r = 0.71
TextInput.prompt_g = 0.70
TextInput.prompt_b = 0.72
TextInput.alpha = 1.0

function TextInput:setup(o)
  Elem:setup(o)

  o.context = TextInputContext:new()
  o.context.OnEnter = function ()
    o.EnterPressed()
  end

end

function TextInput:Draw()

  local r, g, b = 0, 0, 0
  local cur_state = self:GetState()

  local text = self:GetText()

  if cur_state == kHover or cur_state == kPressed or self:IsCurrent() then

    ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, 
            self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 2, self.height - 2, 
            self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha)

    r, g, b = self.text_hover_r, self.text_hover_g, self.text_hover_b

  else

    ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, 
            self.bkg_r, self.bkg_g, self.bkg_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 2, self.height - 2, 
            self.border_r, self.border_g, self.border_b, self.alpha)

    r, g, b = self.text_r, self.text_g, self.text_b
  end

  ui:FlushGeometry()

  if text == "" and self.prompt ~= "" then

    r = 0.71
    g = 0.70
    b = 0.72

    local text_width, text_height = ui:MeasureText(font, self.prompt)
    ui:DrawText(font, self.prompt, 10, self.height / 2 - text_height / 2 + 1, self.prompt_r, self.prompt_g, self.prompt_b, 1, kNormal)
  end

  if self:IsCurrent() then
    local text_width, text_height = ui:MeasureTextInput(font, self.context)
    ui:DrawTextInput(font, self.context, 5, self.height / 2 - text_height / 2 + 1, 0, 0, 0, 1, kNormal)
  end
end

function TextInput:GetText()
  return self.context:GetText()
end

function TextInput:MakeCurrent()
  self.context:MakeCurrent(self.clickable)
end

function TextInput:IsCurrent()
  return self.context:IsCurrent()
end

function TextInput:Clicked()
  self:MakeCurrent()
end

function TextInput:Destroyed()
  if self.IsCurrent() then
    ui:ClearCurrentTextInput()
  end
end

function TextInput:SetInputValidator(func)
  self.context.IsInvalidInput = function (text) return not func(text) end
end

function TextInput:EnterPressed()

end

function BindInputEnterToButton(input, button)
  input.EnterPressed = function()
    button:Clicked()
  end
end
