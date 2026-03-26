#pragma once
#include "Core/Core.h"
#include "NativeScript.h"
#include <filesystem>

namespace Neptune {

	class VideoPlayer : public NativeScript
	{
	public:

		VideoPlayer(const std::filesystem::path path) : m_InFile{ path } {}
		~VideoPlayer() override = default;

		void OnAttached() override;
		void OnTick() override;

	private:

		std::filesystem::path m_InFile;
		SP<class Demuxer> m_Demuxer = nullptr;
		SP<class Decoder> m_Decoder = nullptr;
		SP<class OpticalFlow> m_OpticalFlow = nullptr;
		uint32_t m_FrameCount = 0;
	};
}