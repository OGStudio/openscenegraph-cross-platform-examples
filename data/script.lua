print("This is a message from Lua")

function printStrings(strings)
    for id, string in pairs(strings) do
        print(string)
    end
end

-- Register mouse client to receive mouse events.
mouseClient = EnvironmentClient.new()
ENV:addClient(mouseClient);
mouseClient.respondsToKey = function(key)
    return key == "application.mouse.pressedButtons"
end
mouseClient.call = function(key, values)
    -- Make sure there are pressed buttons.
    if (next(values) == nil) then
        return {}
    end

    print("Mouse clicked. Toggle background color")
    toggleBackgroundColor({"0.2", "0.7"})

    return {}
end

function toggleBackgroundColor(rComponents)
    key = "application.camera.clearColor"
    -- Get current color.
    color = ENV:call(key, {})
    -- Toggle R component.
    if (tonumber(color[1]) == tonumber(rComponents[1])) then
        color[1] = rComponents[2]
    else
        color[1] = rComponents[1]
    end
    -- Apply color.
    ENV:call(key, color)
end

