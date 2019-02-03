
ChatDisplay = Elem:construct()
ChatDisplay.total_height = 0
ChatDisplay.elements = {}
ChatDisplay.next_element_id = 0
ChatDisplay.scroll_offset = 0
ChatDisplay.font = chat_font

function ChatDisplay:AddElement(name, text)
  local first_line = name .. ": " .. text
  local line_height = ui:GetLineHeight(self.font)
  local wrapped_first_line, height = ui:WrapText(self.font, first_line, self.width)
  
  local first_line_end = string.find(wrapped_first_line, "\n")
  local remainder = nil

  local total_height = line_height

  if first_line_end ~= nil then
    remainder = string.sub(first_line, first_line_end, -1)
    first_line = string.sub(first_line, 1, first_line_end - 1)
    remainder, height = ui:WrapText(self.font, remainder, self.width - 20)
    total_height = line_height + height
  end
  
  local elem_data = {
    first_line = first_line,
    remainder = remainder,
    total_height = total_height,
    name = name,
    text = text
  }

  self.elements[self.next_element_id] = elem_data
  self.next_element_id = self.next_element_id + 1
  self.total_height = self.total_height + total_height
end

function ChatDisplay:Draw()

  local line_height = ui:GetLineHeight(self.font)
  local y_offset = self.height + self.scroll_offset

  if self.height > self.total_height then
    y_offset = self.total_height
  end

  local r, g, b = default_text_r, default_text_g, default_text_b

  for i = 0, self.next_element_id - 1 do
    local v = self.elements[i]
    local elem_top = y_offset
    local elem_bot = elem_top - v.total_height 
    if elem_top < 0 then
      return
    end

    if elem_bot < self.height then
      ui:DrawText(self.font, v.first_line, 0, elem_top - line_height, r, g, b, 1, kNormal)

      if v.remainder ~= nil then
        ui:DrawText(self.font, v.remainder, 20, elem_top - line_height * 2, r, g, b, 1, kNormal)
      end
    end

    y_offset = elem_bot
  end
end

