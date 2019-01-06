

ListBox = Elem:construct()
ListBox.alpha = 1.0
ListBox.parent_alpha = 1.0
ListBox.options = {}
ListBox.num_options = 0
ListBox.selected_index = 0
ListBox.hover_index = -1
ListBox.scroll_offset = 0
ListBox.content_height = 0
ListBox.scale = 1.0
ListBox.pressable = true
ListBox.mouse_y = 0
ListBox.mouse_in = false
ListBox.border_r = 0.4
ListBox.border_g = 0.4
ListBox.border_b = 0.4
ListBox.border_hover_r = 0.1
ListBox.border_hover_g = 0.1
ListBox.border_hover_b = 0.7
ListBox.border_selected_r = 0.1
ListBox.border_selected_g = 0.1
ListBox.border_selected_b = 0.7
ListBox.bkg_r = 0.96
ListBox.bkg_g = 0.96
ListBox.bkg_b = 1
ListBox.bkg_hover_r = 1
ListBox.bkg_hover_g = 1
ListBox.bkg_hover_b = 1
ListBox.bkg_selected_r = 0.9
ListBox.bkg_selected_g = 0.9
ListBox.bkg_selected_b = 0.91
ListBox.bkg_selected_hover_r = 0.7
ListBox.bkg_selected_hover_g = 0.7
ListBox.bkg_selected_hover_b = 0.71
ListBox.text_r = 0
ListBox.text_g = 0
ListBox.text_b = 0
ListBox.text_hover_r = 0.2
ListBox.text_hover_g = 0.2
ListBox.text_hover_b = 0.4
ListBox.text_selected_r = 0.4
ListBox.text_selected_g = 0.4
ListBox.text_selected_b = 0.4

function ListBox:setup(o)
  Elem:setup(o)
  o.scrollbar = PushMenuElement(ScrollBar:new())
  o.scrollbar.ValueChanged = function()
    o.scroll_offset = o.scrollbar.value
  end

  o.scroll_proxy = o.scrollbar
end

function ListBox:Draw()

  local cur_state = self:GetState()

  local r, g, b = 0, 0, 0
  local bkg_r, bkg_g, bkg_b = 0, 0, 0
  local border_r, border_g, border_b = 0, 0, 0
  local alpha = self.alpha * self.parent_alpha

  if cur_state == kHover or cur_state == kPressed then

    bkg_r, bkg_g, bkg_b = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b
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

  ui:DrawFilledRectangle(0, 0, self.width - 1, self.height - 1, bkg_r, bkg_g, bkg_b, alpha)

  ui:FlushGeometry()

  local prev_hover_index = self.hover_index
  self.hover_index = -1

  local y = self.height + self.scroll_offset
  local initial_y = y

  for i = 0, self.num_options - 1 do

    local option = self.options[i]
    local width, height = ui:MeasureTextScaled(font, option, self.scale)

    y = y - height

    local text_r, text_g, text_b = r, g, b

    if self.mouse_y >= y - 2 and self.mouse_y < y + height then
      self.hover_index = i
    end

    if self.mouse_in and i == self.hover_index then

      if i == self.selected_index then
        ui:DrawFilledRectangle(1, y - 2, self.width - 3, height, self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, alpha)
        ui:DrawRectangle(1, y - 2, self.width - 3, height, self.border_hover_r, self.border_hover_g, self.border_hover_b, alpha)
      else
        ui:DrawFilledRectangle(1, y - 2, self.width - 3, height, self.bkg_selected_hover_r, self.bkg_selected_hover_g, self.bkg_selected_hover_b, alpha)
        ui:DrawRectangle(1, y - 2, self.width - 3, height, self.border_selected_hover_r, self.border_selected_hover_g, self.border_selected_hover_b, alpha)
      end
      
      ui:FlushGeometry()

      text_r, text_g, text_b = self.text_hover_r, self.text_hover_g, self.text_hover_b

    elseif i == self.selected_index then

      ui:DrawFilledRectangle(1, y - 2, self.width - 3, height, self.bkg_selected_r, self.bkg_selected_g, self.bkg_selected_b, alpha)
      ui:DrawRectangle(1, y - 2, self.width - 3, height, self.border_selected_r, self.border_selected_g, self.border_selected_b, alpha)
      ui:FlushGeometry()

      text_r, text_g, text_b = self.text_selected_r, self.text_selected_g, self.text_selected_b
    end

    ui:DrawTextScaled(font, option, self.width / 2 - width / 2, y, text_r, text_g, text_b, alpha, kNormal, self.scale)

    y = y - 2
  end


  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, border_r, border_g, border_b, alpha)
  ui:FlushGeometry()

  self.content_height = initial_y - y

  if self.hover_index ~= prev_hover_index and self.hover_index ~= -1 then
    ui:PlayAudio(hover_audio)
  end
end

function ListBox:Update()
  self.scrollbar:SetParent(self.parent)
  self.scrollbar:SetScrollArea(self.height, self.content_height)
  self.scrollbar.x = self.x + self.width
  self.scrollbar.y = self.y + 1
  self.scrollbar.width = 16
  self.scrollbar.height = self.height
end

function ListBox:SetSelectedOption(option_index)
  self.selected_index = option_index
end

function ListBox:PushOption(option)
  self.options[self.num_options] = option
  self.num_options = self.num_options + 1
end

function ListBox:Clicked()
  if self.hover_index ~= -1 then
    self.selected_index = self.hover_index
    ui:PlayAudio(click_audio)
  end
end

function ListBox:MouseEntered(x, y)
  self.mouse_in = true
end

function ListBox:MouseMoved(x, y)
  self.mouse_y = y
end

function ListBox:MouseLeft()
  self.mouse_in = false
end
