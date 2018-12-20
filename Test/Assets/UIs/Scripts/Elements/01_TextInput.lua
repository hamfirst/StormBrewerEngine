
TextInput = Elem:construct()
TextInput.prompt = ""

function TextInput:setup(o)
  Elem:setup(o)

  o.context = TextInputContext:new()
end

function TextInput:Render()

  local r, g, b = 0, 0, 0
  local cur_state = self:GetState()

  local text = self:GetText()

  if cur_state == kHover or cur_state == kPressed then
      r = 0.3
      g = 0.4
      b = 1.0
  end

  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 1, 1, 1, 1)
  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, r, g, b, 1)
  ui:FlushGeometry()

  if text == "" then
    if self.prompt ~= "" then

      r = 0.51
      g = 0.50
      b = 0.52

      local text_width, text_height = ui:MeasureText(font, self.prompt)
      ui:DrawText(font, self.prompt, 5, self.height / 2 - text_height / 2 + 1, r, g, b, 1, kNormal)
    end
  else
    local text_width, text_height = ui:MeasureTextInput(font, self.context)
    ui:DrawTextInput(font, self.context, 5, self.height / 2 - text_height / 2 + 1, r, g, b, 1, kNormal)
  end
end

function TextInput:GetText()
  return self.context:GetText()
end

function TextInput:MakeCurrent()
  self.context:MakeCurrent(self.clickable)
end

function TextInput:Clicked()
  self:MakeCurrent()
end
