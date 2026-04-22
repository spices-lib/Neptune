/**
* @file PhysicalDevice.h.
* @brief The PhysicalDevice Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/PhysicalDevice.h"

#include <vector>
#include <optional>

namespace Neptune::Vulkan {
	
	/**
	* @brief Queue Families.
	*/
	struct QueueFamilies
	{
		std::optional<uint32_t> graphic;                    // @brief Graphic Queue Family.
		std::optional<uint32_t> present;                    // @brief Present Queue Family.
		std::optional<uint32_t> transfer;                   // @brief Transfer Queue Family.
		std::optional<uint32_t> compute;                    // @brief Compute Queue Family.
		std::optional<uint32_t> videoEncode;                // @brief VideoEncode Queue Family.
		std::optional<uint32_t> videoDecode;                // @brief VideoDecode Queue Family.
		std::optional<uint32_t> opticalFlow;                // @brief OpticalFlow Queue Family.

		/**
		* @brief Is all familites are found.
		* 
		* @return Returns true if found.
		*/
		bool isComplete() const
		{
			return graphic && present && transfer && compute && videoEncode && videoDecode && opticalFlow;
		}
	};

	/**
	* @brief SwapChain Property.
	*/
	struct SwapChainProperty
	{
		VkSurfaceCapabilitiesKHR        capabilities;       // @brief VkSurfaceCapabilitiesKHR.
		std::vector<VkSurfaceFormatKHR> formats;            // @brief VkSurfaceFormatKHR.
		std::vector<VkPresentModeKHR>   presentModes;       // @brief VkPresentModeKHR.
		VkSurfaceFormatKHR              format;             // @brief VkSurfaceFormatKHR.
		VkPresentModeKHR                presentMode;        // @brief VkPresentModeKHR.
		VkExtent2D                      surfaceSize;        // @brief VkExtent2D.
		VkExtent2D                      viewPortSize;       // @brief VkExtent2D.
	};

	/**
	* @brief VideoSession Property.
	*/
	struct VideoSessionProperty
	{
		VkVideoCapabilitiesKHR          capabilities;       // @brief VkVideoCapabilitiesKHR.
		VkFormat                        dpbFormat;          // @brief VkFormat.
		VkFormat                        dstFormat;          // @brief VkFormat.
	};

	using IPhysicalDevice = IInfrastructure<class PhysicalDevice, EInfrastructure::PhysicalDevice>;

	/**
	* @brief Vulkan::PhysicalDevice Class.
	* This class defines the Vulkan::PhysicalDevice behaves.
	*/
	class PhysicalDevice : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		PhysicalDevice(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~PhysicalDevice() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::PhysicalDevice::Handle& Handle() const { return m_PhysicalDevice.GetHandle(); }

		/**
		* @brief Get Extensions.
		*
		* @return Returns Extensions.
		*/
		const std::vector<const char*>& GetExtensionRequirements() const;

		/**
		* @brief Get QueueFamilies.
		*
		* @return Returns QueueFamilies.
		*/
		const QueueFamilies& GetQueueFamilies() const { return m_QueueFamilies; }

		/**
		* @brief Get Properties.
		*
		* @return Returns Properties.
		*/
		const VkPhysicalDeviceProperties& GetProperties() const { return m_Properties; };

		/**
		* @brief Get SwapChain Properties.
		*
		* @return Returns SwapChain Properties.
		*/
		const SwapChainProperty& GetSwapChainProperty() { return m_SwapChainProperty; }

		/**
		* @brief Get VideoSession Properties.
		*
		* @return Returns VideoSession Properties.
		*/
		VideoSessionProperty QueryVideoSessionProperty(const VkVideoProfileInfoKHR& videoProfile);

		/**
		* @brief Is OpticalFlow Session Support.
		*
		* @param[in] inputFormat VkFormat.
		* @param[in] outFormat VkFormat.
		* 
		* @return Returns true if supported.
		*/
		bool IsOpticalFlowSessionSupport(VkFormat inputFormat, VkFormat outFormat);

		/**
		* @brief Query SwapChain Property.
		*
		* @return Returns SwapChain Property.
		*/
		const SwapChainProperty& QuerySwapChainProperty();

	private:

		/**
		* @brief Create Instance.
		*/
		void Create();

		/**
		* @brief Is Extension Meet Demand.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if meets.
		*/
		bool IsExtensionMeetDemand(const VkPhysicalDevice& device) const;

		/**
		* @brief Is Property Meet Demand.
		*
		* @param[in] device VkPhysicalDevice.
		*
		* @return Returns true if meets.
		*/
		bool IsPropertyMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Is Feature Meet Demand.
		*
		* @param[in] device VkPhysicalDevice.
		*
		* @return Returns true if meets.
		*/
		bool IsFeatureMeetDemand(const VkPhysicalDevice& device) const;

		/**
		* @brief Is Queue Meet Demand.
		*
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		*
		* @return Returns true if meets.
		*/
		bool IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

		/**
		* @brief Is Queue OpticalFlow Session Supported.
		*
		* @param[in] inputformat VkFormat.
		* @param[in] usage VkOpticalFlowUsageFlagsNV.
		*
		* @return Returns true if supported.
		*/
		bool IsOpticalFlowSessionSupport(VkFormat inputformat, VkOpticalFlowUsageFlagsNV usage);

		/**
		* @brief Get Video supported formats.
		*
		* @param[in] imageUsage VkImageUsageFlags.
		* @param[in] videoProfile VkVideoProfileInfoKHR.
		*
		* @return Returns supported formats.
		*/
		std::vector<VkFormat> GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile);

	private:

		Unit::PhysicalDevice m_PhysicalDevice;              // @brief This PhysicalDevice.
		std::vector<const char*> m_ExtensionProperties;     // @brief Extensions.
		QueueFamilies m_QueueFamilies;                      // @brief QueueFamilies.
		VkPhysicalDeviceProperties m_Properties;            // @brief VkPhysicalDeviceProperties.
		SwapChainProperty m_SwapChainProperty;              // @brief SwapChainProperty.
	};

}

#endif