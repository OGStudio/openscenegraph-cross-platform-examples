print("This is a message from Lua")

function printStrings(strings)
    for id, string in pairs(strings) do
        print(string)
    end
end


-- Call sample environment client registered at C++ side.
values = ENV:call("sample", {"One", "Two"})
printStrings(values)

-- Register new client that responds to 'lua' key.
luaClient = EnvironmentClient.new()
luaClient.respondsToKey = function(key)
    return key == "lua"
end
luaClient.call = function(key, values)
    return {"Wow", "Nah"}
end
-- Add it to Environemnt.
ENV:addClient(luaClient)
-- 'lua' client is called by parent.

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

    print("mouse clicked")

    return {}
end

