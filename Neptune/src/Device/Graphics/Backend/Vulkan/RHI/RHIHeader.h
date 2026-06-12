/**
* @file RHIHeader.h.
* @brief The RHIHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Device/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/RHI/DescriptorList.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Pipeline.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Shader.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderTarget.h"
#include "Device/Graphics/Backend/Vulkan/RHI/VertexBuffer.h"
#include "Device/Graphics/Backend/Vulkan/RHI/IndexBuffer.h"
#include "Device/Graphics/Backend/Vulkan/RHI/CmdList.h"
#include "Device/Graphics/Backend/Vulkan/RHI/CmdList2.h"
#include "Device/Graphics/Backend/Vulkan/RHI/Video/Decode/Decoder.h"
#include "Device/Graphics/Backend/Vulkan/RHI/OpticalFlowSession.h"

#endif