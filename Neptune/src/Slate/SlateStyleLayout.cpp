/**
* @file SlateStyleLayout.cpp.
* @brief The SlateStyleLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SlateStyleLayout.h"
#include "Imgui/ImguiHelper.h"
#include "Core/Library/FileLibrary.h"
#include "..\Core\Thread\ThreadModel.h"

namespace Neptune {

	std::shared_ptr<SlateStyleLayout> SlateStyleLayout::m_Layout = nullptr;

	std::shared_ptr<SlateStyleLayout> SlateStyleLayout::Get()
	{
		NEPTUNE_PROFILE_ZONE;

		if (!m_Layout)
		{
			m_Layout = std::make_shared<SlateStyleLayout>();
		}

		return m_Layout;
	}

	void SlateStyleLayout::SetLayout(StyleLayoutEnum layout)
	{
		NEPTUNE_PROFILE_ZONE;

		switch (layout)
		{
			case StyleLayoutEnum::Default:
			{
				std::stringstream ss;
				ss << NEPTUNE_ASSETS_PATH << "SlateLayout/DefaultLayout.ini";
				ImGui::LoadIniSettingsFromDisk(ss.str().c_str());
			}
			default:
			{
				std::stringstream ss;
				ss << NEPTUNE_ASSETS_PATH << "SlateLayout/DefaultLayout.ini";
				ImGui::LoadIniSettingsFromDisk(ss.str().c_str());
			}
		}
	}

	void SlateStyleLayout::LoadLayout()
	{
		NEPTUNE_PROFILE_ZONE;


	}

	void SlateStyleLayout::StoreLayout()
	{
		NEPTUNE_PROFILE_ZONE;


	}

	void SlateStyleLayout::StoreLayoutCache()
	{
		NEPTUNE_PROFILE_ZONE;

		std::stringstream ss;

		ss << "saved/SlateCache/";
		std::filesystem::create_directory(ss.str());

		ss << "CacheLayout.ini";
		ImGui::SaveIniSettingsToDisk(ss.str().c_str());
	}

	void SlateStyleLayout::LoadLayoutCache()
	{
		NEPTUNE_PROFILE_ZONE;

		std::stringstream ss;
		ss << "saved/SlateCache/CacheLayout.ini";

		ImGui::LoadIniSettingsFromDisk(ss.str().c_str());
	}

	void SlateStyleLayout::QuickStoreLayout()
	{
		NEPTUNE_PROFILE_ZONE;

		std::stringstream ss;

		ss << "saved/SlateCache/";
		std::filesystem::create_directory(ss.str());

		ss << "QuickLayout.ini";
		ImGui::SaveIniSettingsToDisk(ss.str().c_str());
	}

	void SlateStyleLayout::QuickLoadLayout()
	{
		NEPTUNE_PROFILE_ZONE;

		std::stringstream ss;
		ss << "saved/SlateCache/QuickLayout.ini";

		ImGui::LoadIniSettingsFromDisk(ss.str().c_str());
	}
}