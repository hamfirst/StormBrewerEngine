
ConfirmPopup = Popup:construct()
ConfirmPopup.text = "Confirm?"

function ConfirmPopup:setup(o)
  Popup:setup(o)

  o.okay = Button:new()
  o.okay:SetParent(o)
  o.okay.text = "Okay"
  o.cancel = Button:new()
  o.cancel:SetParent(o)
  o.cancel.text = "Cancel"
end

function ConfirmPopup:Update()
  local half_width = self.width / 2

  self.okay.x = half_width * 0.2
  self.okay.y = 20
  self.okay.width = half_width * 0.6
  self.okay.height = 20

  self.cancel.x = half_width * 1.2
  self.cancel.y = 20
  self.cancel.width = half_width * 0.6
  self.cancel.height = 20
end

function ConfirmPopup:Draw()
  Popup.Draw(self)

  ui:DrawCenteredText(font, self.text, self.width / 2, self.height - 50, 0, 0, 0, 1, kNormal)
end
