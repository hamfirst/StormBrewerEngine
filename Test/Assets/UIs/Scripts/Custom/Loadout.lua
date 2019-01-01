
Loadout = Elem:construct()

function Loadout:Draw()
  local r, g, b, a = 0, 0, 0, 1

  local large_header_height = ui:GetLineHeight(large_header_font)

  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, r, g, b, a)
  ui:DrawFilledRectangle(0, self.height - 35, self.width - 1, 35, r, g, b, a)
  ui:FlushGeometry()

  ui:DrawText(large_header_font, "Loadout", 10, self.height - 35 / 2 - large_header_height / 2, 1, 1, 1, 1, kNormal)

end
