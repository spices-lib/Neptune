/**
* @file RenderTarget.h.
* @brief The RenderTarget Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Texture/Texture.h"

namespace Neptune {

	struct RenderTargetCreateInfo;
}

namespace Neptune::RHI {
	
	using RHIRenderTarget = RHI<ERHI::RenderTarget>;

	/**
	* @brief Specialization of RHIRenderTarget::Impl
	*/
	template<>
	class RHIRenderTarget::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Impl() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Impl() = default;

		/**
		* @brief Interface of Create RenderTarget.
		* 
		* @param[in] info RenderTargetCreateInfo.
		*/
		virtual void CreateRenderTarget(const RenderTargetCreateInfo& info) = 0;

		/**
		* @brief Interface of Create BindingID.
		*
		* @return Returns BindingID.
		*/
		virtual void* CreateBindingID() = 0;

		/**
		* @brief Interface of Copy To RenderTarget.
		*
		* @param[in] target RenderTarget.
		* 
		* @return Returns true if succeeded.
		*/
		virtual bool CopyToRenderTarget(SP<class RenderTarget> target) = 0;

		/**
		* @brief Interface of Get Format.
		*
		* @return Returns format.
		*/
		virtual TextureFormat GetFormat() const = 0;

		/**
		* @brief Interface of Get Width.
		*
		* @return Returns width.
		*/
		virtual uint32_t GetWidth() const = 0;

		/**
		* @brief Interface of Get Height.
		*
		* @return Returns height.
		*/
		virtual uint32_t GetHeight() const = 0;
	};

	/**
	* @brief RHI of ERHI::RenderTarget
	*/
	class RenderTarget : public RHIRenderTarget
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		RenderTarget() = default;

		/**
		* @brief Destructor Function.
		*/
		~RenderTarget() override = default;

		/**
		* @brief Interface of Create RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateRenderTarget(const RenderTargetCreateInfo& info) { RHIRenderTarget::m_Impl->CreateRenderTarget(info); }

		/**
		* @brief Interface of Create BindingID.
		*
		* @return Returns BindingID.
		*/
		void* CreateBindingID() const { return RHIRenderTarget::m_Impl->CreateBindingID(); }

		/**
		* @brief Interface of Copy To RenderTarget.
		*
		* @param[in] target RenderTarget.
		*
		* @return Returns true if succeeded.
		*/
		bool CopyToRenderTarget(SP<RenderTarget> target) const { return RHIRenderTarget::m_Impl->CopyToRenderTarget(target); }

		/**
		* @brief Interface of Get Format.
		*
		* @return Returns format.
		*/
		TextureFormat GetFormat() const { return RHIRenderTarget::m_Impl->GetFormat(); }

		/**
		* @brief Interface of Get Width.
		*
		* @return Returns width.
		*/
		uint32_t GetWidth() const { return RHIRenderTarget::m_Impl->GetWidth(); }

		/**
		* @brief Interface of Get Height.
		*
		* @return Returns height.
		*/
		uint32_t GetHeight() const { return RHIRenderTarget::m_Impl->GetHeight(); }

	};
}