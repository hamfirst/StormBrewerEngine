

Checkbox = Elem:construct()
Checkbox.box_size = 16
Checkbox.text = ""
Checkbox.alpha = 1.0
Checkbox.parent_alpha = 1.0
Checkbox.scale = 1.0
Checkbox.pressable = true
Checkbox.toggled = false
Checkbox.back = false
Checkbox.fade = true
Checkbox.check_alpha = 0
Checkbox.border_r = default_border_r
Checkbox.border_g = default_border_g
Checkbox.border_b = default_border_b
Checkbox.border_hover_r = default_widget_border_highlighted_r
Checkbox.border_hover_g = default_widget_border_highlighted_g
Checkbox.border_hover_b = default_widget_border_highlighted_b
Checkbox.border_toggled_r = default_widget_border_selected_r
Checkbox.border_toggled_g = default_widget_border_selected_g
Checkbox.border_toggled_b = default_widget_border_selected_b
Checkbox.bkg_r = default_widget_bkg_r
Checkbox.bkg_g = default_widget_bkg_g
Checkbox.bkg_b = default_widget_bkg_b
Checkbox.bkg_hover_r = default_widget_bkg_highlighted_r
Checkbox.bkg_hover_g = default_widget_bkg_highlighted_g
Checkbox.bkg_hover_b = default_widget_bkg_highlighted_b
Checkbox.bkg_toggled_r = default_widget_bkg_selected_r
Checkbox.bkg_toggled_g = default_widget_bkg_selected_g
Checkbox.bkg_toggled_b = default_widget_bkg_selected_b
Checkbox.bkg_toggled_hover_r = default_widget_bkg_selected_highlighted_r
Checkbox.bkg_toggled_hover_g = default_widget_bkg_selected_highlighted_g
Checkbox.bkg_toggled_hover_b = default_widget_bkg_selected_highlighted_b
Checkbox.text_r = default_text_r
Checkbox.text_g = default_text_g
Checkbox.text_b = default_text_b
Checkbox.text_hover_r = default_text_highlighted_r
Checkbox.text_hover_g = default_text_highlighted_g
Checkbox.text_hover_b = default_text_highlighted_b
Checkbox.text_toggled_r = default_text_selected_r
Checkbox.text_toggled_g = default_text_selected_g
Checkbox.text_toggled_b = default_text_selected_g

function Checkbox:Draw()

  local cur_state = self:GetState()

  local r, g, b = 0, 0, 0
  local bkg_r, bkg_g, bkg_b = 0, 0, 0
  local border_r, border_g, border_b = 0, 0, 0

  local alpha = self.alpha * self.parent_alpha

  local box_size = self.box_size
  box_size = math.min(box_size, self.width - 1)
  box_size = math.min(box_size, self.height - 1)

  if cur_state == kHover or cur_state == kPressed then
    
    if self.toggled then
      bkg_r, bkg_g, bkg_b = self.bkg_toggled_hover_r, self.bkg_toggled_hover_g, self.bkg_toggled_hover_b
    else
      bkg_r, bkg_g, bkg_b = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b
    end

    border_r, border_g, border_b = self.border_hover_r, self.border_hover_g, self.border_hover_b
    r, g, b = self.text_hover_r, self.text_hover_g, self.text_hover_b

  elseif self.toggled then

    bkg_r, bkg_g, bkg_b = self.bkg_toggled_r, self.bkg_toggled_g, self.bkg_toggled_b
    border_r, border_g, border_b = self.border_toggled_r, self.border_toggled_g, self.border_toggled_b

    r, g, b = self.text_toggled_r, self.text_toggled_g, self.text_toggled_b
  else

    bkg_r, bkg_g, bkg_b = self.bkg_r, self.bkg_g, self.bkg_b
    border_r, border_g, border_b = self.border_r, self.border_g, self.border_b

    r, g, b = self.text_r, self.text_g, self.text_b
  end

  ui:DrawFilledRectangle(0, 0, box_size, box_size, bkg_r, bkg_g, bkg_b, alpha)
  ui:DrawRectangle(0, 0, box_size, box_size, border_r, border_g, border_b, alpha)

  ui:DrawLine(2, 6, 6, 2, border_r, border_g, border_b, self.check_alpha)
  ui:DrawLine(6, 2, box_size - 2, box_size - 2, border_r, border_g, border_b, self.check_alpha)

  ui:FlushGeometry()

  local width, height = ui:MeasureTextScaled(font, self.text, self.scale)

  ui:DrawTextScaled(font, self.text, box_size + 5, self.height / 2 + 1 - height / 2, 
                            r, g, b, alpha, kNormal, self.scale);

end

function Checkbox:StateChanged(prev_state, new_state)
  if self.pressable == false then
    return
  end

  if prev_state == kActive and new_state == kHover then
      ui:PlayAudio(hover_audio)
  end
end

function Checkbox:Clicked()
  if self.pressable == false then
    return
  end

  if self.back then
    ui:PlayAudio(back_audio)
  else
    ui:PlayAudio(click_audio)
  end

  self.toggled = not self.toggled
  self:Pressed()
end

function Checkbox:Pressed()
  if self.toggled then
    self.ToggleOn()

    AddLerp(self, "check_alpha", 1, 0.05)
  else
    self.ToggleOff()

    AddLerp(self, "check_alpha", 0, 0.2)
  end
end

function Checkbox:ToggleOn()

end

function Checkbox:ToggleOff()

end

function Checkbox:SetToggled(toggled)
  if self.toggled ~= toggled then
    self.toggled = toggled
    self:Pressed()
  end
end
