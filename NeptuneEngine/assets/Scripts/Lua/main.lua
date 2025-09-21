-- Main Lua Script

main = {
    ["ScriptInterface"] = {
        OnConstruct = function()
            print("OnConstruct")
        end,
        OnDestroy = function()
            print("OnDestroy")
        end,
        OnAttached = function()
            print("OnAttached")
        end,
        OnDetached = function()
            print("OnDetached")
        end,
        OnTick = function()
            print("OnTick")
        end,
        OnEvent = function()
            print("OnEvent")
        end
    }
}