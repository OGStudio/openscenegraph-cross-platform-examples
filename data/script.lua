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
-- Call newly registered client.
values = ENV:call("lua", {"X", "Y"})
printStrings(values)
