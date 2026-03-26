#include "Pchheader.h"
#include "OpticalFlowSession.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/Functions.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/RHI/RenderTarget.h"
#include "Render/Backend/Vulkan/Resource/Image.h"
#include "Render/Backend/Vulkan/RHI/CmdList2.h"

namespace Neptune::Vulkan {

	OpticalFlowSession::OpticalFlowSession(Context& context)
		: ContextAccessor(context)
	{
		m_Session.SetFunctor(
			GetContext().Get<IFunctions>()->vkCreateOpticalFlowSessionNV,
			GetContext().Get<IFunctions>()->vkDestroyOpticalFlowSessionNV,
			GetContext().Get<IFunctions>()->vkBindOpticalFlowSessionImageNV
		);
	}

	void OpticalFlowSession::SetInputRenderTarget(SP<RHI::RenderTarget> rt)
	{
		auto rhi = rt->GetRHIImpl<RenderTarget>();

		m_SessionImages[VK_OPTICAL_FLOW_SESSION_BINDING_POINT_INPUT_NV] = rhi->IHandle().get();
	}

	void OpticalFlowSession::SetReferenceRenderTarget(SP<RHI::RenderTarget> rt)
	{
		auto rhi = rt->GetRHIImpl<RenderTarget>();

		m_SessionImages[VK_OPTICAL_FLOW_SESSION_BINDING_POINT_REFERENCE_NV] = rhi->IHandle().get();
	}

	void OpticalFlowSession::SetFlowVectorRenderTarget(SP<RHI::RenderTarget> rt)
	{
		auto rhi = rt->GetRHIImpl<RenderTarget>();

		m_SessionImages[VK_OPTICAL_FLOW_SESSION_BINDING_POINT_FLOW_VECTOR_NV] = rhi->IHandle().get();
	}

	void OpticalFlowSession::OpticalFlowExecute()
	{
		CmdList2 cmdList(GetContext());

		cmdList.SetOpticalFlowCmdList();

        cmdList.Begin();

		cmdList.SetOpticalFlowSession(this);

		cmdList.CmdOpticalFlowExecute();

        cmdList.End();

        cmdList.SubmitWait();
	}

	bool OpticalFlowSession::CreateOpticalFlowSession()
	{
		auto reference = m_SessionImages[VK_OPTICAL_FLOW_SESSION_BINDING_POINT_REFERENCE_NV];
		auto output    = m_SessionImages[VK_OPTICAL_FLOW_SESSION_BINDING_POINT_FLOW_VECTOR_NV];

		if (!GetContext().Get<IPhysicalDevice>()->IsOpticalFlowSessionSupport(reference->GetFormat(), VK_FORMAT_R16G16_SFIXED5_NV))
		{
			return false;
		}

		VkOpticalFlowSessionCreateInfoNV               info{};
		info.sType                                   = VK_STRUCTURE_TYPE_OPTICAL_FLOW_SESSION_CREATE_INFO_NV;
		info.width                                   = reference->Width();
		info.height                                  = reference->Height();
		info.imageFormat                             = reference->GetFormat();
		info.flowVectorFormat                        = reference->GetFormat();
		info.outputGridSize                          = VkOpticalFlowGridSizeFlagsNV(reference->Width() / output->Width());
		info.performanceLevel                        = VK_OPTICAL_FLOW_PERFORMANCE_LEVEL_SLOW_NV;
		info.costFormat                              = VK_FORMAT_UNDEFINED;
		info.flags                                   = 0;

		m_Session.CreateOpticalFlowSession(GetContext().Get<IDevice>()->Handle(), info);

		BindSessionImages();

		return true;
	}

	void OpticalFlowSession::BindSessionImages()
	{
		for (const auto& image : m_SessionImages)
		{
			m_Session.BindOpticalFlowSessionImage(image.first, image.second->GetView(), image.second->GetLayout());
		}
	}
}