
ScrollBar = Elem:construct()
ScrollBar.value = 10
ScrollBar.visible_size = 50
ScrollBar.content_size = 100
ScrollBar.highlight = 0
ScrollBar.mouse_in = false
ScrollBar.dragging = false
ScrollBar.button_active = false
ScrollBar.bar_rel = 0
ScrollBar.bar_start = 0
ScrollBar.bar_end = 0
ScrollBar.drag_start_y = 0
ScrollBar.drag_start_val = 0
ScrollBar.border_r = default_widget_border_r
ScrollBar.border_g = default_widget_border_g
ScrollBar.border_b = default_widget_border_b
ScrollBar.border_hover_r = default_widget_border_highlighted_r
ScrollBar.border_hover_g = default_widget_border_highlighted_g
ScrollBar.border_hover_b = default_widget_border_highlighted_r
ScrollBar.bkg_r = default_widget_bkg_r
ScrollBar.bkg_g = default_widget_bkg_g
ScrollBar.bkg_b = default_widget_bkg_b
ScrollBar.bkg_hover_r = default_widget_bkg_highlighted_r
ScrollBar.bkg_hover_g = default_widget_bkg_highlighted_b
ScrollBar.bkg_hover_b = default_widget_bkg_highlighted_g
ScrollBar.alpha = 1


function ScrollBar:Draw()
  local cur_state = self:GetState()
  local bkg_r, bkg_g, bkg_b, bkg_a = self.bkg_r, self.bkg_g, self.bkg_b, self.alpha
  local border_r, border_g, border_b, border_a = self.border_r, self.border_g, self.border_b, self.alpha

  local bar_bkg_size = self.height - 23
  local bar_height = bar_bkg_size * (self.visible_size / self.content_size)
  local bar_start = (bar_bkg_size - bar_height - 1) * (self.value / (self.content_size - self.visible_size)) - 1

  if self.mouse_in and self.highlight == 0 and self.bar_rel ~= 0 then
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha
  else
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_r, self.bkg_g, self.bkg_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_r, self.border_g, self.border_b, self.alpha
  end

  ui:DrawFilledRectangle(0, 10, self.width - 1, self.height - 21, bkg_r, bkg_g, bkg_b, bkg_a)
  ui:DrawRectangle(0, 10, self.width - 1, self.height - 21, border_r, border_g, border_b, border_a)

  if self.mouse_in and self.highlight == 0 and self.bar_rel == 0 then
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha
  else
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_r, self.bkg_g, self.bkg_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_r, self.border_g, self.border_b, self.alpha
  end

  self.bar_start = 10 + bar_bkg_size - bar_start - bar_height
  self.bar_end = self.bar_start + bar_height
  ui:DrawFilledRectangle(2, self.bar_start, self.width - 5, bar_height, bkg_r, bkg_g, bkg_b, bkg_a)
  ui:DrawRectangle(2, self.bar_start, self.width - 5, bar_height, border_r, border_g, border_g, border_a)          

  if self.mouse_in and self.highlight == -1 then
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha
  else
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_r, self.bkg_g, self.bkg_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_r, self.border_g, self.border_b, self.alpha
  end

  ui:DrawFilledRectangle(0, 0, self.width - 1, 10, bkg_r, bkg_g, bkg_b, bkg_a)
  ui:DrawRectangle(0, 0, self.width - 1, 10, border_r, border_g, border_b, border_a)
  ui:DrawLine(5, 7, (self.width - 12) / 2 + 5, 3, border_r, border_g, border_b, border_a)
  ui:DrawLine((self.width - 12) / 2 + 5, 3, self.width - 7, 7, border_r, border_g, border_b, border_a)           

  if self.mouse_in and self.highlight == 1 then
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_hover_r, self.bkg_hover_g, self.bkg_hover_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_hover_r, self.border_hover_g, self.border_hover_b, self.alpha
  else
    bkg_r, bkg_g, bkg_b, border_a = self.bkg_r, self.bkg_g, self.bkg_b, self.alpha
    border_r, border_g, border_b, border_a = self.border_r, self.border_g, self.border_b, self.alpha
  end

  ui:DrawFilledRectangle(0, self.height - 11, self.width - 1, 10, bkg_r, bkg_g, bkg_b, bkg_a)
  ui:DrawRectangle(0, self.height - 11, self.width - 1, 10, border_r, border_g, border_b, border_a)
  ui:DrawLine(5, self.height - 9, (self.width - 12) / 2 + 5, self.height - 5, border_r, border_g, border_b, border_a)
  ui:DrawLine((self.width - 12) / 2 + 5, self.height - 5, self.width - 7, self.height - 9, border_r, border_g, border_b, border_a)

  ui:FlushGeometry()
end

function ScrollBar:StateChanged(old_state, new_state)
  if new_state == kPressed then
    if self.highlight == 0 then
      if self.bar_rel < 0 then
        self:SetValue(self.value - self.visible_size)
      elseif self.bar_rel > 0 then
        self:SetValue(self.value + self.visible_size)
      else
        self.dragging = true
      end
    else
      self.button_active = true
    end
  end

  if new_state == kActive or new_state == kHover then
    self.dragging = false
    self.button_active = false
  end
end

function ScrollBar:SetValue(val)
  local prev_value = self.value

  self.value = val
  if self.value > self.content_size - self.visible_size then
    self.value = self.content_size - self.visible_size
  end
  if self.value < 0 then
    self.value = 0
  end

  if prev_value ~= self.value then
    self:ValueChanged()
  end
end

function ScrollBar:ScrollToBottom()
  self:SetValue(self.content_size - self.visible_size)
end

function ScrollBar:IsScrolledToBottom()
  return self.visible_size >= self.content_size or self.value == self.content_size - self.visible_size
end

function ScrollBar:SetScrollArea(visible_size, content_size)
  self.visible_size = visible_size
  self.content_size = content_size
  self:SetValue(self.value)
  self:SetEnabled(self.visible_size < self.content_size)
end

function ScrollBar:MouseMoved(x, y)
  if self.dragging then

    local bar_bkg_size = self.height - 24
    local bar_height = bar_bkg_size * (self.visible_size / self.content_size)

    local value_per_pixel = (self.content_size - self.visible_size) / (bar_bkg_size - bar_height)
    local dv = value_per_pixel * (y - self.drag_start_y)
    self:SetValue(self.drag_start_val - dv)

  elseif self.button_active == false then

    self.drag_start_y = y
    self.drag_start_val = self.value

    if y < 14 then 
      self.highlight = -1
    elseif y >= self.height - 14 then
      self.highlight = 1
    else
      if y < self.bar_start then
        self.bar_rel = 1
      elseif y > self.bar_end then
        self.bar_rel = -1
      else
        self.bar_rel = 0
      end

      self.highlight = 0
    end 
  end
end

function ScrollBar:MouseEntered(x, y)
  self.mouse_in = true
end

function ScrollBar:MouseLeft()
  self.mouse_in = false
  self.highlight = 0
  self.bar_rel = 0
end

function ScrollBar:MouseScrolled(dv)
  self:SetValue(self.value + dv / -4)
end

function ScrollBar:Clicked()
  if self.highlight < 0 then
    self:SetValue(self.value + 10)
  elseif self.highlight > 0 then
    self:SetValue(self.value - 10)
  end
end

function ScrollBar:ValueChanged()

end
