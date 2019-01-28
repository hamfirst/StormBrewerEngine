
ScrollButton = Button:construct()
ScrollButton.options = {}
ScrollButton.num_options = 0
ScrollButton.option_lerp = 0
ScrollButton.option_index = 0
ScrollButton.direction = 0

function ScrollButton:Draw()

  local cur_state = self:GetState()

  local r, g, b = 0, 0, 0
  local bkg_r, bkg_g, bkg_b = 0, 0, 0
  local border_r, border_g, border_b = 0, 0, 0
  local alpha = self.alpha * self.parent_alpha

  if cur_state == kHover or cur_state == kPressed then
    
    if self.toggleable and self.toggled then
      bkg_r, bkg_g, bkg_b = self.bkg_toggled_hover_r, self.bkg_toggled_hover_g, self.bkg_toggled_hover_b
    else
      bkg_r, bkg_g, bkg_b = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b
    end

    border_r, border_g, border_b = self.border_hover_r, self.border_hover_g, self.border_hover_b
    r, g, b = self.text_hover_r, self.text_hover_g, self.text_hover_b

  elseif self.toggleable and self.toggled then

    bkg_r, bkg_g, bkg_b = self.bkg_toggled_r, self.bkg_toggled_g, self.bkg_toggled_b
    border_r, border_g, border_b = self.border_toggled_r, self.border_toggled_g, self.border_toggled_b

    r, g, b = self.text_toggled_r, self.text_toggled_g, self.text_toggled_b
  else

    bkg_r, bkg_g, bkg_b = self.bkg_r, self.bkg_g, self.bkg_b
    border_r, border_g, border_b = self.border_r, self.border_g, self.border_b

    r, g, b = self.text_r, self.text_g, self.text_b
  end

  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, bkg_r, bkg_g, bkg_b, alpha)
  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, border_r, border_g, border_b, alpha)

  local arrow_r, arrow_g, arrow_b = 0, 0, 0
  if self.direction == -1 then
    arrow_r, arrow_g, arrow_b = self.border_hover_r, self.border_hover_g, self.border_hover_b
  else
    arrow_r, arrow_g, arrow_b = self.border_r, self.border_g, self.border_b
  end

  ui:DrawLine(2, self.height / 2, 6, self.height / 2 + 4, arrow_r, arrow_g, arrow_b, alpha)
  ui:DrawLine(2, self.height / 2, 6, self.height / 2 - 4, arrow_r, arrow_g, arrow_b, alpha)

  if self.direction == 1 then
    arrow_r, arrow_g, arrow_b = self.border_hover_r, self.border_hover_g, self.border_hover_b
  else
    arrow_r, arrow_g, arrow_b = self.border_r, self.border_g, self.border_b
  end

  ui:DrawLine(self.width - 4, self.height / 2, self.width - 8, self.height / 2 + 4, arrow_r, arrow_g, arrow_b, alpha)
  ui:DrawLine(self.width - 4, self.height / 2, self.width - 8, self.height / 2 - 4, arrow_r, arrow_g, arrow_b, alpha)

  ui:FlushGeometry()

  if self.num_options >= 1 then

    local frac = self.option_lerp - math.floor(self.option_lerp)
    local baseline = math.floor(self.option_lerp / self.num_options) * self.num_options
    local index = self.option_lerp - baseline - frac

    local next_index = index + 1
    if next_index >= self.num_options then
      next_index = 0
    end

    local t1_alpha = 1 - frac
    local t2_alpha = frac

    local t1_pos = self.width / 2 - frac * self.width
    local t2_pos = self.width / 2 + (1 - frac) * self.width

    local t1 = self.options[index]
    local t2 = self.options[next_index]

    local t1_width, t1_height = ui:MeasureTextScaled(font, t1, self.scale)
    local t2_width, t2_height = ui:MeasureTextScaled(font, t2, self.scale)

    ui:DrawTextScaled(font, t1, t1_pos - t1_width / 2, self.height / 2 + 1 - t1_height / 2, r, g, b, alpha * t1_alpha, kNormal, self.scale)
    ui:DrawTextScaled(font, t2, t2_pos - t2_width / 2, self.height / 2 + 1 - t2_height / 2, r, g, b, alpha * t2_alpha, kNormal, self.scale)

  end

end

function ScrollButton:StateChanged(prev_state, new_state)
  if self.pressable == false then
    return
  end

  if prev_state == kActive and new_state == kHover then
      ui:PlayAudio(hover_audio)
  end
end

function ScrollButton:Clicked()
  if self.pressable == false then
    return
  end

  ui:PlayAudio(click_audio)

  if self.num_options >= 1 and self.direction ~= 0 then

    self.option_index = self.option_index + self.direction
    if self.option_index >= self.num_options then
      self.option_index = 0
    end

    if self.option_index < 0 then
      self.option_index = self.num_options - 1
    end

    self:SelectedOptionChanged(self.option_index)

    AddLerp(self, "option_lerp", self.option_lerp + self.direction, 0.15, nil, EaseInOutCubic)
  end

  self:Pressed()
end

function ScrollButton:Pressed()

end

function ScrollButton:SetToggled(toggled)

end

function ScrollButton:MouseEntered(x, y)

end

function ScrollButton:MouseMoved(x, y)
  if x >= self.width / 2 then
    self.direction = 1
  else
    self.direction = -1
  end
end

function ScrollButton:MouseLeft()
  self.direction = 0
end

function ScrollButton:SelectedOptionChanged(option_index)

end

function ScrollButton:SetSelectedOption(option_index)
  if option_index ~= self.option_index then
    self.option_index = option_index
    self.option_lerp = option_index
    self:SelectedOptionChanged(self.option_index)
  end
end

function ScrollButton:PushOption(option)
  self.options[self.num_options] = option
  self.num_options = self.num_options + 1
end

function ScrollButton:ClearOptions()
  self.options = {}
  self.num_options = 0
end

function ScrollButton:GetSelectedOption()
  return self.options[self.option_index]
end
