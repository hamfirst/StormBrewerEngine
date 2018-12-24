

hover_audio = loader:LoadAudio("./Sounds/ButtonHover.wav")
click_audio = loader:LoadAudio("./Sounds/ButtonClick.wav")
back_audio = loader:LoadAudio("./Sounds/MenuBack.wav")
error_audio = loader:LoadAudio("./Sounds/Error.wav")

Button = Elem:construct()
Button.text = ""
Button.alpha = 1.0
Button.scale = 1.0
Button.toggleable = false
Button.toggled = false
Button.back = false
Button.border_r = 0.4
Button.border_g = 0.4
Button.border_b = 0.4
Button.border_hover_r = 0.1
Button.border_hover_g = 0.1
Button.border_hover_b = 0.7
Button.border_toggled_r = 0.1
Button.border_toggled_g = 0.1
Button.border_toggled_b = 0.7
Button.bkg_r = 0.96
Button.bkg_g = 0.96
Button.bkg_b = 1
Button.bkg_hover_r = 1
Button.bkg_hover_g = 1
Button.bkg_hover_b = 1
Button.bkg_toggled_r = 1
Button.bkg_toggled_g = 1
Button.bkg_toggled_b = 1
Button.text_r = 0
Button.text_g = 0
Button.text_b = 0
Button.text_hover_r = 0.2
Button.text_hover_g = 0.2
Button.text_hover_b = 0.4
Button.text_toggled_r = 0.4
Button.text_toggled_g = 0.4
Button.text_toggled_b = 0.4

function Button:Draw()

  local cur_state = self:GetState()

  local r, g, b = 0, 0, 0

  if cur_state == kHover or cur_state == kPressed then

    ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, 
            self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 2, self.height - 2, 
            self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha)

    r, g, b = self.text_hover_r, self.text_hover_g, self.text_hover_b

  elseif self.toggleable and self.toggled then

    ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, 
            self.bkg_toggled_r, self.bkg_toggled_g, self.bkg_toggled_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 2, self.height - 2, 
            self.border_toggled_r, self.border_toggled_g, self.border_toggled_b, self.alpha)

    r, g, b = self.text_toggled_r, self.text_toggled_g, self.text_toggled_b
  else

    ui:DrawFilledRectangle(0, 0, self.width - 2, self.height - 2, 
            self.bkg_r, self.bkg_g, self.bkg_b, self.alpha)

    ui:DrawRectangle(0, 0, self.width - 2, self.height - 2, 
            self.border_r, self.border_g, self.border_b, self.alpha)

    r, g, b = self.text_r, self.text_g, self.text_b
  end


  ui:FlushGeometry()

  ui:DrawCenteredTextScaled(font, self.text, self.width / 2, self.height / 2 + 1, 
                            r, g, b, self.alpha, kNormal, self.scale);

end

function Button:StateChanged(prev_state, new_state)
  if prev_state == kActive and new_state == kHover then
      ui:PlayAudio(hover_audio)
  end
end

function Button:Clicked()
  if self.back then
    ui:PlayAudio(back_audio)
  else
    ui:PlayAudio(click_audio)
  end

  if self.toggleable == false then
    AddLerp(self, "x", self.x - 10, 0.3)
    AddLerp(self, "y", self.y - 10, 0.3)
    AddLerp(self, "width", self.width + 20, 0.3)
    AddLerp(self, "height", self.height + 20, 0.3)
    AddLerp(self, "alpha", 0, 0.3)
    AddLerp(self, "scale", 1.3, 0.3)
  else
    self.toggled = not self.toggled
  end

  self:Pressed()
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
