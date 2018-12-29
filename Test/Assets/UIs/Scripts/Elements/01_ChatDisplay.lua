
ChatDisplay = Elem:construct()
ChatDisplay.total_height = 0
ChatDisplay.elements = {}
ChatDisplay.next_element_id = 0
ChatDisplay.scroll_offset = 0


function ChatDisplay:AddElement(name, text)
  local first_line = name .. ": " .. text
  local line_height = ui:GetLineHeight(font)
  local wrapped_first_line, height = ui:WrapText(font, first_line, self.width)
  
  local first_line_end = string.find(wrapped_first_line, "\n")
  local remainder = nil


  local total_height = line_height

  if first_line_end ~= nil then
    remainder = string.sub(first_line, first_line_end, -1)
    first_line = string.sub(first_line, 1, first_line_end - 1)
    remainder, height = ui:WrapText(font, remainder, self.width - 20)
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
  local line_height = ui:GetLineHeight(font)
  local y_offset = self.height + self.scroll_offset

  if self.height > self.total_height then
    y_offset = self.total_height
  end

  for k, v in pairs(self.elements) do
    local elem_top = y_offset
    local elem_bot = elem_top - v.total_height 
    if elem_top < 0 then
      return
    end

    if elem_bot < self.height then
      ui:DrawText(font, v.first_line, 0, elem_top - line_height, 0, 0, 0, 1, kNormal)

      if v.remainder ~= nil then
        ui:DrawText(font, v.remainder, 20, elem_top - line_height * 2, 0, 0, 0, 1, kNormal)
      end
    end

    y_offset = elem_bot
  end
end

