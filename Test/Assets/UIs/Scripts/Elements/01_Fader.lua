
Fader = Elem:construct()
Fader.alpha = 1.0
Fader.x = ScreenWidth / -2
Fader.y = ScreenHeight / -2
Fader.width = ScreenWidth
Fader.height = ScreenHeight

function Fader:Render()

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
  ClearLerp(self, "alpha")
  AddLerp(self, "alpha", 1, 0.5)
end

function Fader:FadeToClear()
  ClearLerp(self, "alpha")
  AddLerp(self, "alpha", 0, 0.5)
end
