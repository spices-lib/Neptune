/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Direct3D12/Unit/SwapChain.h"
#include "Window/Enum.h"

namespace Neptune::Direct3D12 {

	using ISwapChain = IInfrastructure<class SwapChain, EInfrastructure::SwapChain>;

	/**
	* @brief Direct3D12::SwapChain Class.
	* This class defines the Direct3D12::SwapChain behaves.
	*/
	class SwapChain : public Infrastructure
	{
	public:

		/**
		* @brief Factory of Create Surface with SwapChain implement.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count SwapChain image Count.
		* @param[in] implement WindowImplement.
		* @param[in] window Native Window.
		*/
		static SP<SwapChain> Create(Context& context, EInfrastructure e, uint32_t count, WindowImplement implement, void* window);

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		SwapChain(Context& context, EInfrastructure e) : Infrastructure(context, e) {}

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::SwapChain::Handle& Handle() const { return m_SwapChain->GetHandle(); }

		/**
		* @brief Present to surface.
		*
		* @return Returns true if succeed.
		*/
		bool Present() const;

	protected:

		/**
		* @brief Create SwapChain.
		*
		* @param[in] desc DXGI_SWAP_CHAIN_DESC1.
		* @param[in] count SwapChain image Count.
		* @param[in] hwnd Window HWND.
		*/
		void Create(DXGI_SWAP_CHAIN_DESC1& desc, uint32_t count, HWND hwnd);

	protected:

		SP<Unit::SwapChain> m_SwapChain;           // @brief This SwapChain.
		BOOL m_AllowTearing;                       // @brief Feature of AllowTearing.

	};

}

#endif