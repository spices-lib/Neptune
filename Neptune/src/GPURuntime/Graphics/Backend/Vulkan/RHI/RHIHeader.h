/**
* @file RHIHeader.h.
* @brief The RHIHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "GPURuntime/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/DescriptorList.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/Pipeline.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/Shader.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/VertexBuffer.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/IndexBuffer.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/CmdList.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/CmdList2.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/Video/Decode/Decoder.h"
#include "GPURuntime/Graphics/Backend/Vulkan/RHI/OpticalFlowSession.h"

#endif