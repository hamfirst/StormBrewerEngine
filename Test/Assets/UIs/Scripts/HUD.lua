
hud_info = {}

tutorial_atlas = loader:LoadAtlas("./UIs/Tutorial.atlas")

function DrawHud()

  if hud_info.timer ~= "" then

    if hud_info.timer_pre_round then
      ui:DrawCenteredTextScaled(large_header_font, hud_info.timer, 0, 10, 
        1, 1, 1, 1 - hud_info.timer_scale, kNormal, 1 + hud_info.timer_scale);
    else
      ui:DrawCenteredTextScaled(large_header_font, hud_info.timer, 0, screen_end_y - large_header_font_height, 
        1, 1, 1, 1, kOutlined, 1);      
    end
  end

  if hud_info.tutorial_hint ~= "" then
    local width, height = ui:MeasureText(font, hud_info.tutorial_hint)

    ui:DrawAtlas(tutorial_atlas, "Bubble", hud_info.tutorial_hint_x, hud_info.tutorial_hint_y, 64 + width, 64 + height);
    ui:DrawText(font, hud_info.tutorial_hint, hud_info.tutorial_hint_x + 32, hud_info.tutorial_hint_y + 38, 0, 0, 0, 1, kNormal)
  end
end

