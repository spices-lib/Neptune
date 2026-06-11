-- @file platform.lua.
-- @brief Defines all Solutions Platform behavies.
-- @author Spices.

-- Define module
local module = {}

-- @brief Get Compute Feature Lists.
-- 
-- @param[in] toolset ToolSet.
--
-- @return Returns Compute Feature Lists.
module.GetComputeFeatures = function(toolset)

    local list = {}

    if toolset == "clang" then
        table.insert(list, "NP_COMPUTE_SYCL")
    end

    return list

end

-- @brief Get Graphics Feature Lists.
-- 
-- @return Returns Graphics Feature Lists.
module.GetGraphicsFeatures = function()

    local list = {}

    if os.target() == "emscripten" then
        table.insert(list, "NP_GRAPHICS_WEBGL")
        table.insert(list, "NP_GRAPHICS_WEBGPU")
    end

    if os.target() ~= "emscripten" then
        table.insert(list, "NP_GRAPHICS_OPENGL")
        table.insert(list, "NP_GRAPHICS_VULKAN")
    end

    if os.target() == "windows" then
        table.insert(list, "NP_GRAPHICS_DIRECT3D11")
        table.insert(list, "NP_GRAPHICS_DIRECT3D12")
    end

    if os.target() == "macos" then
        table.insert(list, "NP_GRAPHICS_METAL")
    end

    return list

end

-- @brief Get Profile Feature Lists.
-- 
-- @return Returns Profile Feature Lists.
module.GetProfileFeatures = function()

    local list = {}

    if os.target() == "windows" then
        table.insert(list, "NP_PROFILE_TRACY")
        table.insert(list, "TRACY_ENABLE")                -- tracy Feature Enable.
        table.insert(list, "TRACY_ON_DEMAND")             -- Used if want profile on demand.
        table.insert(list, "TRACY_FIBERS")                -- Enable fiber thread.
        table.insert(list, "TRACY_IMPORT")                -- Multi dll.
    end

    return list

end

return module