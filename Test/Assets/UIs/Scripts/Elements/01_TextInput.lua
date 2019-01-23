
TextInput = Elem:construct()
TextInput.prompt = ""
TextInput.cursor_scroll = 5
TextInput.border_r = default_widget_border_r
TextInput.border_g = default_widget_border_g
TextInput.border_b = default_widget_border_b
TextInput.border_hover_r = default_widget_border_highlighted_r
TextInput.border_hover_g = default_widget_border_highlighted_g
TextInput.border_hover_b = default_widget_border_highlighted_b
TextInput.bkg_r = default_widget_bkg_r
TextInput.bkg_g = default_widget_bkg_g
TextInput.bkg_b = default_widget_bkg_b
TextInput.bkg_hover_r = default_widget_bkg_highlighted_r
TextInput.bkg_hover_g = default_widget_bkg_highlighted_b
TextInput.bkg_hover_b = default_widget_bkg_highlighted_g
TextInput.text_r = default_text_r
TextInput.text_g = default_text_g
TextInput.text_b = default_text_b
TextInput.prompt_r = default_text_selected_highlighted_r
TextInput.prompt_g = default_text_selected_highlighted_g
TextInput.prompt_b = default_text_selected_highlighted_b
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

    ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 
            self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, 
            self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha)

    r, g, b = self.text_hover_r, self.text_hover_g, self.text_hover_b

  else

    ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 
            self.bkg_r, self.bkg_g, self.bkg_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, 
            self.border_r, self.border_g, self.border_b, self.alpha)

    r, g, b = self.text_r, self.text_g, self.text_b
  end

  ui:FlushGeometry()

  if text == "" and self.prompt ~= "" then

    r = 0.71
    g = 0.70
    b = 0.72

    local text_width, text_height = ui:MeasureText(chat_font, self.prompt)
    ui:DrawText(chat_font, self.prompt, 10, self.height / 2 - text_height / 2 + 1, self.prompt_r, self.prompt_g, self.prompt_b, 1, kNormal)
  end

  local chat_font_height = ui:GetLineHeight(chat_font)
  if text ~= "" then

    local cursor_pos = self:GetCursorPos()
    local pre_cursor_width = 0
    
    if cursor_pos > 0 then
      pre_cursor_width = ui:MeasureText(chat_font, string.sub(text, 0, cursor_pos - 1))
    end

    if pre_cursor_width + self.cursor_scroll < 5 then
      self.cursor_scroll = 5 - pre_cursor_width
    end

    if pre_cursor_width + self.cursor_scroll > self.width - 20 then
      self.cursor_scroll = self.width - 20 - pre_cursor_width
    end

    ui:DrawTextInput(chat_font, self.context, self.cursor_scroll, self.height / 2 - chat_font_height / 2 + 3, self.text_r, self.text_g, self.text_b, 1, kNormal)
  else
    ui:DrawTextInput(chat_font, self.context, 5, self.height / 2 - chat_font_height / 2 + 3, self.text_r, self.text_g, self.text_b, 1, kNormal)
  end
end

function TextInput:GetText()
  return self.context:GetText()
end

function TextInput:Clear()
  self.context:Clear()
  self.cursor_scroll = 5
end

function TextInput:MakeCurrent()
  self.context:MakeCurrent(self.clickable)
end

function TextInput:IsCurrent()
  return self.context:IsCurrent()
end

function TextInput:GetCursorPos()
  return self.context:GetCursorPos()
end

function TextInput:StateChanged(old_state, new_state)
  if new_state == kPressed then
    self:MakeCurrent()
  end
end

function TextInput:Destroyed()
  if self:IsCurrent() then
    self.context:MakeNotCurrent()
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
