-- Main Lua Script

main = {
    [1] = {
        OnConstruct = function() 
            print("OnConstruct")
        end
    },
    [2] = {
        OnDestroy = function()
            print("OnDestroy")
        end
    },
    [3] = {
        OnAttached = function()
            print("OnAttached")
        end
    },
    [4] = {
        OnDetached = function()
            print("OnDetached")
        end
    },
    [5] = {
        OnTick = function()
            print("OnTick")
        end
    },
    [6] = {
        OnEvent = function()
            print("OnEvent")
        end
    },
}