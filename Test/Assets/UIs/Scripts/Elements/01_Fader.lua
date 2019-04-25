
Fader = Elem:construct()
Fader.alpha = 1.0
Fader.target_alpha = 1.0
Fader.r = default_fade_r
Fader.g = default_fade_g
Fader.b = default_fade_b
Fader.x = screen_start_x
Fader.y = screen_start_y
Fader.fade_speed = 0.3
Fader.width = screen_width
Fader.height = screen_height

function Fader:Draw()

  if self.alpha == 0 then
    return
  end

  ui:DrawFilledRectangle(0, 0, self.width, self.height, self.r, self.g, self.b, self.alpha)
  ui:FlushGeometry()
end

function Fader:Update()
  self:SetEnabled(self.alpha ~= 0)
end

function Fader:FadeToSolid()
  AddLerp(self, "alpha", self.target_alpha, self.fade_speed)
end

function Fader:FadeToSolidThen(func)
  AddLerp(self, "alpha", self.target_alpha, self.fade_speed, func)
end

function Fader:FadeToClear()
  AddLerp(self, "alpha", 0, self.fade_speed)
end

function Fader:SetAlpha(alpha)
  ClearLerp(self, "alpha")
  self.alpha = alpha
end

function FadeFromButtonPress(fader, button, func)
  button.Pressed = function()
    fader:FadeToSolidThen(func)
  end
end

function FadeFromInputEnterPress(fader, input, func)
  input.EnterPressed = function()
    fader:FadeToSolidThen(func)
  end
end
