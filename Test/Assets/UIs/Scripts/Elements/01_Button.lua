

hover_audio = loader:LoadAudio("./Sounds/ButtonHover.wav")
click_audio = loader:LoadAudio("./Sounds/ButtonClick.wav")

Button = Elem:construct()
Button.text = ""
Button.alpha = 1.0
Button.scale = 1.0

function Button:Render()

  local r, g, b = 0, 0, 0
  local cur_state = self:GetState()

  if cur_state == kHover or cur_state == kPressed then
      r = 0.3
      g = 0.4
      b = 1.0
  end

  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 1, 1, 1, self.alpha)
  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, r, g, b, self.alpha)
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
  ui:PlayAudio(click_audio)

  AddLerp(self, "x", self.x - 10, 0.3)
  AddLerp(self, "y", self.y - 10, 0.3)
  AddLerp(self, "width", self.width + 20, 0.3)
  AddLerp(self, "height", self.height + 20, 0.3)
  AddLerp(self, "alpha", 0, 0.3)
  AddLerp(self, "scale", 1.3, 0.3)

  self.Pressed()
end

function Button:Pressed()

end
