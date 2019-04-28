
Button = Elem:construct()
Button.text = ""
Button.font = font
Button.text_offset_y = 0
Button.alpha = 1.0
Button.parent_alpha = 1.0
Button.scale = 1.0
Button.pressable = true
Button.toggleable = false
Button.toggled = false
Button.back = false
Button.fade = true
Button.border_r = default_border_r
Button.border_g = default_border_g
Button.border_b = default_border_b
Button.border_hover_r = default_widget_border_highlighted_r
Button.border_hover_g = default_widget_border_highlighted_g
Button.border_hover_b = default_widget_border_highlighted_b
Button.border_toggled_r = default_widget_border_selected_r
Button.border_toggled_g = default_widget_border_selected_g
Button.border_toggled_b = default_widget_border_selected_b
Button.bkg_r = default_widget_bkg_r
Button.bkg_g = default_widget_bkg_g
Button.bkg_b = default_widget_bkg_b
Button.bkg_hover_r = default_widget_bkg_highlighted_r
Button.bkg_hover_g = default_widget_bkg_highlighted_g
Button.bkg_hover_b = default_widget_bkg_highlighted_b
Button.bkg_toggled_r = default_widget_bkg_selected_r
Button.bkg_toggled_g = default_widget_bkg_selected_g
Button.bkg_toggled_b = default_widget_bkg_selected_b
Button.bkg_toggled_hover_r = default_widget_bkg_selected_highlighted_r
Button.bkg_toggled_hover_g = default_widget_bkg_selected_highlighted_g
Button.bkg_toggled_hover_b = default_widget_bkg_selected_highlighted_b
Button.text_r = default_text_r
Button.text_g = default_text_g
Button.text_b = default_text_b
Button.text_hover_r = default_text_highlighted_r
Button.text_hover_g = default_text_highlighted_g
Button.text_hover_b = default_text_highlighted_b
Button.text_toggled_r = default_text_selected_r
Button.text_toggled_g = default_text_selected_g
Button.text_toggled_b = default_text_selected_g
Button.image_r = 1
Button.image_g = 1
Button.image_b = 1
Button.image_a = 1
Button.image_scale_x = 1
Button.image_scale_y = 1

function Button:Draw()

  local cur_state = self:GetState()

  if self.pressable == false then
    cur_state = kActive
  end

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

  ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, bkg_r, bkg_g, bkg_b, alpha)
  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, border_r, border_g, border_b, alpha)

  ui:FlushGeometry()

  local width, height = ui:MeasureTextScaled(self.font, self.text, self.scale)
  local text_y = self.height / 2 + 1 - height / 2

  if self.image ~= nil then

    local width, height = ui:GetTextureSize(self.image)  
    width = width * self.image_scale_x
    height = height * self.image_scale_y

    ui:DrawTextureScaleTint(self.image, self.width / 2 - width / 2, self.height / 2 - height / 2 + 5 + self.text_offset_y,
      self.image_scale_x, self.image_scale_y, self.image_r, self.image_g, self.image_b, self.image_a * alpha)

      text_y = text_y - height / 2 - 5
  end

  ui:DrawTextScaled(self.font, self.text, self.width / 2 - width / 2, text_y + self.text_offset_y + 1,
                            r, g, b, alpha, kNormal, self.scale)

end

function Button:StateChanged(prev_state, new_state)
  if self.pressable == false then
    return
  end

  if prev_state == kActive and new_state == kHover then
      ui:PlayAudio(hover_audio)
      self:Hovered()
  end

  if prev_state == kHover and new_state == kActive then
    self:Unhovered()
  end
end

function Button:Clicked()
  if self.pressable == false then
    return
  end

  if self.back then
    ui:PlayAudio(back_audio)
  else
    ui:PlayAudio(click_audio)
  end

  if self.toggleable == false then
    if self.fade then

      self:SetClip(false)

      AddLerp(self, "x", self.x - 10, 0.3)
      AddLerp(self, "y", self.y - 10, 0.3)
      AddLerp(self, "width", self.width + 20, 0.3)
      AddLerp(self, "height", self.height + 20, 0.3)
      AddLerp(self, "alpha", 0, 0.3)
      AddLerp(self, "scale", 1.3, 0.3)
      AddLerp(self, "image_scale_x", self.image_scale_x * 1.3, 0.3)
      AddLerp(self, "image_scale_y", self.image_scale_y * 1.3, 0.3)
    end
  else
    self.toggled = not self.toggled
  end

  self:Pressed()
end

function Button:Hovered()

end

function Button:Unhovered()

end

function Button:Pressed()
  if self.toggleable then
    if self.toggled then
      self.ToggleOn()
    else
      self.ToggleOff()
    end
  end
end

function Button:ToggleOn()

end

function Button:ToggleOff()

end

function Button:SetToggled(toggled)
  if self.toggleable == false then
    return
  end

  if self.toggled ~= toggled then
    self.toggled = toggled
    self:Pressed()
  end
end
