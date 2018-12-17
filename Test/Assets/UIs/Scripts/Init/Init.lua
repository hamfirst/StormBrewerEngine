
logo = loader:LoadTexture("./Images/stormbrewers_logo.png")
font = loader:LoadFont("./Fonts/FFF.ttf", 10);

hover_audio = loader:LoadAudio("./Sounds/ButtonHover.wav")
click_audio = loader:LoadAudio("./Sounds/ButtonClick.wav")

test_clickable = Clickable:new()
test_clickable.X = 0
test_clickable.Y = 0;
test_clickable.Width = 400
test_clickable.Height = 30

test_input = TextInput:new()
--test_input:MakeCurrent(test_clickable)

test_clickable.OnRender = function()
    ui:DrawRectangle(0, 0, test_clickable.Width, test_clickable.Height, 0, 0, 0, 1)
    ui:FlushGeometry()

    local r, g, b = 0, 0, 0
    if test_clickable:GetState() == kHover then
        r = 0.3
        g = 0.4
        b = 1.0
    end

    ui:DrawCenteredTextInput(font, test_input, test_clickable.Width / 2, test_clickable.Height / 2, r, g, b, 1, kNormal);
end

test_clickable.OnStateChange = function(prev_state, new_state)

    if prev_state == kActive and new_state == kHover then
        ui:PlayAudio(hover_audio)
    end
end

test_clickable.OnClick = function()
    ui:PlayAudio(click_audio)
    test_input:MakeCurrent(test_clickable)
end

function FinalizeLoad()

end
