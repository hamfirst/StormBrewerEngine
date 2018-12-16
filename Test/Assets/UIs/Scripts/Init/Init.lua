
io.write("Hello from lua!\n")

logo = loader:LoadTexture("./Images/stormbrewers_logo.png")
font = loader:LoadFont("./Fonts/FFF.ttf", 10);
test_clickable = Clickable:new()
test_clickable.X = 100
test_clickable.Y = 10;
test_clickable.Width = 100
test_clickable.Height = 30

test_clickable.OnRender = function()
    ui:DrawRectangle(0, 0, test_clickable.Width, test_clickable.Height, 0, 0, 0, 1)
    ui:FlushGeometry()
end

function FinalizeLoad()

end
