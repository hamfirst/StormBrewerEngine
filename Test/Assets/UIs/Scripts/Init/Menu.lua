
cur_menu_elements = {}
cur_menu_index = 0

function PushMenuElement(elem)
    cur_menu_elements[cur_menu_index] = elem
    cur_menu_index = cur_menu_index + 1
    return elem
end

function ClearMenuElements()
    for k, v in pairs(cur_menu_elements) do
        v:Destroyed()

        if v.clickable ~= nil then
            v.clickable:delete()
            v.clickable = nil
        end

        if v.context ~= nil then
            v.context:delete()
            v.context = nil
        end
    end

    cur_menu_elements = {}
    cur_menu_index = 0
end

function CleanupMenu()
    print("Cleaning up menu")
    ClearMenuElements()
  end
  
