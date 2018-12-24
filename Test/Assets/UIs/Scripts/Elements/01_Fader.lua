
Fader = Elem:construct()
Fader.alpha = 1.0
Fader.x = screen_start_x
Fader.y = screen_start_y
Fader.width = screen_width
Fader.height = screen_height

function Fader:Draw()

  if self.alpha == 0 then
    return
  end

  local r, g, b = 1, 1, 1

  ui:DrawFilledRectangle(0, 0, self.width, self.height, r, g, b, self.alpha)
  ui:FlushGeometry()
end

function Fader:Update()
  self:SetEnabled(self.alpha ~= 0)
end

function Fader:FadeToSolid()
  AddLerp(self, "alpha", 1, 0.5)
end

function Fader:FadeToSolidThen(func)
  AddLerp(self, "alpha", 1, 0.5, func)
end

function Fader:FadeToClear()
  AddLerp(self, "alpha", 0, 0.5)
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
