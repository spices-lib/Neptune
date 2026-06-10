-- @file platform.lua.
-- @brief Defines all Solutions platform Includes.
-- @author Spices.

local common  = require "common.lua"
local linux   = require "linux.lua"
local macos   = require "macos.lua"
local wasm    = require "wasm.lua"
local windows = require "windows.lua"

-- Define module
local module = {}

-- Combine platforms
module.common  = common
module.linux   = linux
module.macos   = macos
module.wasm    = wasm
module.windows = windows

return module