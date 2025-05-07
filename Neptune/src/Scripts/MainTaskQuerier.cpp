/**
* @file MainTaskQuerier.cpp.
* @brief The MainTaskQuerier & NativeScriptRegister Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "MainTaskQuerier.h"
#include "Core/Thread/ThreadModel.h"

namespace Neptune {

	void MainTaskQuerier::OnTick(TimeStep& ts)
	{
		NEPTUNE_PROFILE_ZONE;

		auto& taskQueue = ThreadModel::Get()->GetMainTaskQueue();

		while (!taskQueue.IsEmpty())
		{
			auto task = taskQueue.Pop();
			task();
		}
	}
}