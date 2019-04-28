
cur_menu_elements = {}
cur_menu_index = 0

function PushMenuElement(elem)
  cur_menu_elements[cur_menu_index] = elem
  cur_menu_index = cur_menu_index + 1
  return elem
end

function ClearMenuElements()
  for k, v in pairs(cur_menu_elements) do
  v:destroy()
end

cur_menu_elements = {}
cur_menu_index = 0
end

function CleanupMenu()
  print("Cleaning up menu")
  ClearMenuElements()
end
  
