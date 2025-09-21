/**
* @file Profiler.h file.
* @brief The Profiler Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NEPTUNE_DEBUG && NP_PLATFORM_WINDOWS
#include "Debugger/Profiler/Tracy/ProfilerImpl.h"
#else

/**
* @brief Mark Frame End.
*/
#define NEPTUNE_PROFILE_FRAME

/**
* @brief Mark Function Zone.
*/
#define NEPTUNE_PROFILE_ZONE

/**
* @brief Mark Function Zone with name.
* 
* @param[in] name Function Zone name.
*/
#define NEPTUNE_PROFILE_ZONEN(name)

/**
* @brief Mark Memory alloc.
*
* @param[in] ptr Memory pointer.
* @param[in] size Memory size.
*/
#define NEPTUNE_PROFILE_ALLOC(ptr, size)

/**
* @brief Mark Memory free.
*
* @param[in] ptr Memory pointer.
*/
#define NEPTUNE_PROFILE_FREE(ptr)

/**
* @brief Mark Memory alloc with name.
*
* @param[in] ptr Memory pointer.
* @param[in] size Memory size.
* @param[in] name Memory name.
*/
#define NEPTUNE_PROFILE_ALLOC_N(ptr, size, name)

/**
* @brief Mark Memory free with name.
*
* @param[in] ptr Memory pointer.
* @param[in] name Memory name.
*/
#define NEPTUNE_PROFILE_FREE_N(ptr, name)

/**
* @brief Mark a message.
*
* @param[in] text Any message.
*/
#define NEPTUNE_PROFILE_MARK(text)

/**
* @brief Mark a image.
*
* @param[in] image Image data pointer.
*/
#define NEPTUNE_PROFILE_IMAGE(image)

/**
* @brief Mark a Thread name.
*
* @param[in] name Thread name.
*/
#define NEPTUNE_PROFILE_THREAD_N(name)

/**
* @brief Mark a Thread name and group.
*
* @param[in] name Thread name.
* @param[in] group Thread group.
*/
#define NEPTUNE_PROFILE_THREAD_N_G(name, group)

/**
* @brief Mark a Lock.
*
* @param[in] name Lock name.
*/
#define NEPTUNE_PROFILE_LOCK(name)

/**
* @brief Mark a Lock Base.
*/
#define NEPTUNE_PROFILE_LOCK_B

/**
* @brief Mark a Shared Lock.
*
* @param[in] name Shared Lock name.
*/
#define NEPTUNE_PROFILE_SLOCK(name)

/**
* @brief Mark a Shared Lock Base.
*/
#define NEPTUNE_PROFILE_SLOCK_B

/**
* @brief Mark Enter a thread.
* 
* @param[in] name Thread name.
* @param[in] group Thread group.
*/
#define NEPTUNE_PROFILE_THREAD_ENTER(name, group)

/**
* @brief Mark Leave a thread.
*
* @param[in] name Thread name.
*/
#define NEPTUNE_PROFILE_THREAD_LEAVE(name)

#endif
