
HeaderContainer = Elem:construct()
HeaderContainer.text = "Header"
HeaderContainer.font = large_header_font
HeaderContainer.header_padding = 16
HeaderContainer.r = default_frame_r
HeaderContainer.g = default_frame_g
HeaderContainer.b = default_frame_b
HeaderContainer.alpha = 1
HeaderContainer.parent_alpha = 1

function HeaderContainer:Draw()
  local r, g, b, a = self.r, self.g, self.b, self.parent_alpha * self.alpha

  local header_height = ui:GetLineHeight(self.font)
  local header_bkg_height = header_height + self.header_padding

  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, r, g, b, a)
  ui:DrawFilledRectangle(0, self.height - header_bkg_height, self.width - 1, header_bkg_height, r, g, b, a)
  ui:FlushGeometry()

  ui:DrawText(self.font, self.text, 11, self.height - header_bkg_height / 2 - header_height / 2 + 2, 1, 1, 1, a, kNormal)

end
