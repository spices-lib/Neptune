/**
* @file ProcessLibrary.cpp
* @brief The ProcessLibrary Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ProcessLibrary.h"
#include "StringLibrary.h"

#include <stdio.h>

namespace Neptune {

	bool ProcessLibrary::OpenProcess(const char* processPath, const char* commandLine)
	{
		NEPTUNE_PROFILE_ZONE;


		return true;
	}

	bool ProcessLibrary::CloseProcess(const char* processName)
	{
		NEPTUNE_PROFILE_ZONE;


		return true;
	}

	float ProcessLibrary::ProcessMemoryInUsed()
	{
		NEPTUNE_PROFILE_ZONE;



		return 0;
	}
}