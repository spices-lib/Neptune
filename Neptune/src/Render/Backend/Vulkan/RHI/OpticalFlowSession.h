#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/OpticalFlowSession.h"
#include "Render/Frontend/RHI/OpticalFlow.h"
#include <unordered_map>

namespace Neptune::RHI {

	class RenderTarget;
}

namespace Neptune::Vulkan {

	class OpticalFlowSession : public ContextAccessor, public RHI::RHIOpticalFlow::Impl
	{
	public:

		OpticalFlowSession(Context& context);
		~OpticalFlowSession() override = default;

		const Unit::OpticalFlowSession::Handle& Handle() const { return m_Session.GetHandle(); }

		void SetInputRenderTarget(SP<RHI::RenderTarget> rt) override;

		void SetReferenceRenderTarget(SP<RHI::RenderTarget> rt) override;

		void SetFlowVectorRenderTarget(SP<RHI::RenderTarget> rt) override;

		bool CreateOpticalFlowSession() override;

		void OpticalFlowExecute() override;

	private:

		void BindSessionImages();

	private:

		Unit::OpticalFlowSession m_Session;
		std::unordered_map<VkOpticalFlowSessionBindingPointNV, class Image*> m_SessionImages;
	};
}