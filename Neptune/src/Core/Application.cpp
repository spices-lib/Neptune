/**
* @file Application.cpp.
* @brief The Application Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Application.h"
#include "Render/FrameInfo.h"
#include "Render/Vulkan/VulkanRenderBackend.h"
#include "Thread\ThreadModel.h"

// System Header.
#include "Systems/SystemManager.h"
#include "Systems/RenderSystem.h"
#include "Systems/NativeScriptSystem.h"
#include "Systems/ResourceSystem.h"
#include "Systems/SlateSystem.h"
#include "Core/Memory/MemoryPool.h"

namespace Neptune {

	Application::Application()
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Init Log Class.
		*/
		Log::Init();

		/**
		* @brief Init General ThreadPool.
		*/
		ThreadModel::Get()->InitCustomThreadPool();
		ThreadModel::Get()->InitGameThreadPool();

		/**
		* @brief Init all Systems.
		*/
		SystemManager().Get()
		.PushSystem<NativeScriptSystem>()
		.PushSystem<RenderSystem>()
		.PushSystem<ResourceSystem>()
		.PushSystem<SlateSystem>();
	}

	Application::~Application()
	{
		NEPTUNE_PROFILE_ZONE;

		/**
		* @brief Destroy our Specific World.
		*/
		FrameInfo::Get().m_World = nullptr;

		/**
		* @brief Release ThreadPool.
		*/
		ThreadModel::Get()->ShutDownThreadModel();

		/**
		* @brief Destroy all Systems.
		*/
		SystemManager::Get()
		.PopSystem("SlateSystem")
		.PopSystem("ResourceSystem")
		.PopSystem("RenderSystem")
		.PopSystem("NativeScriptSystem");

		/**
		* @brief Shutdown Log Class.
		*/
		Log::ShutDown();
	}

	void Application::Run()
	{
		/**
		* @brief Specify the current World, which created from Game.
		* @todo Mult World Support.
		*/
		FrameInfo::Get().m_World = CreateWorld();

		/**
		* @brief World OnPreActivate.
		* @todo Remove.
		*/
		FrameInfo::Get().m_World->OnPreActivate();

		/**
		* @brief Init Golbal TimeStep Class.
		*/
		TimeStep ts;

		/**
		* @brief Golbal While Loop.
		* @todo Multithreading.
		*/
		while (!glfwWindowShouldClose(VulkanRenderBackend::GetState().m_Windows))
		{
			NEPTUNE_PROFILE_ZONEN("MainLoop");

			/**
			* @brief Wait for glfw events.
			*/
			glfwPollEvents();

			/**
			* @brief Update TimeStep.
			*/
			ts.Flush();
			
			/**
			* @brief Update Aftermath frame cut.
			*/
			NSIGHTAFTERMATH_GPUCRASHTRACKER_SETFRAMECUT(ts.fs())

			/**
			* @brief Activete Our Specific World.
			*/
			FrameInfo::Get().m_World->OnActivate(ts);

			SPICES_PROFILE_FRAME;
		}

		/**
		* @brief Vulkan Device Idle.
		*/
		vkDeviceWaitIdle(VulkanRenderBackend::GetState().m_Device);

		/**
		* @brief Deactivate Our Specific World.
		*/
		FrameInfo::Get().m_World->OnDeactivate();
	}
}