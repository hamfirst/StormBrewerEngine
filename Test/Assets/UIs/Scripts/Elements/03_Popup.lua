
Popup = Elem:construct()

function Popup:setup(o)
  Elem:setup(o)
  o:SetClip(false)
end

function Popup:Draw()
  ui:DrawFilledRectangle(0 - 10, 0 - 10, self.width, self.height, 0, 0, 0, 0.3)
  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, 1, 1, 1, 1)
  ui:DrawRectangle(0, 0, self.width, self.height, 0.8, 0.8, 0.8, 1)
  ui:FlushGeometry()
end
