/**
* @file Log.h
* @brief The Log Class Definitions.
* @author Spices.
*/

#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // This Macro must be defined.
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Neptune {

	/**
	* brief Log Class defines log behaves.
	*/
	class Log
	{
	public:

		static bool m_IsInitialized;

	public:

		/**
		* @brief Init Log.
		*/
		static void Init();

		/**
		* @brief Shutdown Log.
		*/
		static void ShutDown();

		/**
		* @brief Get Engine Stage Logger.
		* @return Returns Engine Stage Logger.
		*/
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/**
		* @brief Get Game Stage Logger.
		* @return Returns Game Stage Logger.
		*/
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	public:

		/**
		* @brief using format_string_t instanced of fmt::format_string<Args...>;
		*/
		template <typename... Args>
		using format_string_t = fmt::format_string<Args...>;

		/**
		* @brief Post handle with log message.
		* @param[in] fmt format string.
		* @param[in] args any param.
		*/
		template <typename... Args>
		static void PostHandle(format_string_t<Args...> fmt, Args &&...args);

	private:

		/**
		* @brief Engine Stage Logger.
		*/
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

		/**
		* @brief Game Stage Logger.
		*/
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	template<typename ...Args>
	inline void Log::PostHandle(format_string_t<Args...> fmt, Args && ...args)
	{}
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

#ifdef NEPTUNE_DEBUG

// Core log macros
#define NEPTUNE_CORE_TRACE(...)    { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetCoreLogger()->trace      (__VA_ARGS__); Neptune:Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_INFO(...)     { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetCoreLogger()->info       (__VA_ARGS__); Neptune:Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_WARN(...)     { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetCoreLogger()->warn       (__VA_ARGS__); Neptune:Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_ERROR(...)    { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetCoreLogger()->error      (__VA_ARGS__); Neptune:Log::PostHandle(__VA_ARGS__);  /*throw std::runtime_error(__VA_ARGS__)*/    } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CORE_CRITICAL(...) { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetCoreLogger()->critical   (__VA_ARGS__); Neptune:Log::PostHandle(__VA_ARGS__);  /*throw std::runtime_error(__VA_ARGS__)*/    } else { std::cout << __VA_ARGS__ << std::endl; } }
																															
// Client log macros																										
#define NEPTUNE_TRACE(...)         { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetClientLogger()->trace    (__VA_ARGS__); Neptune::Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_INFO(...)          { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetClientLogger()->info     (__VA_ARGS__); Neptune::Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_WARN(...)          { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetClientLogger()->warn     (__VA_ARGS__); Neptune::Log::PostHandle(__VA_ARGS__);											   } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_ERROR(...)         { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetClientLogger()->error    (__VA_ARGS__); Neptune::Log::PostHandle(__VA_ARGS__);  /*throw std::runtime_error(__VA_ARGS__)*/    } else { std::cout << __VA_ARGS__ << std::endl; } }
#define NEPTUNE_CRITICAL(...)      { if(Neptune::Log::m_IsInitialized) { Neptune::Log::GetClientLogger()->critical (__VA_ARGS__); Neptune::Log::PostHandle(__VA_ARGS__);  /*throw std::runtime_error(__VA_ARGS__)*/    } else { std::cout << __VA_ARGS__ << std::endl; } }

#endif // NEPTUNE_DEBUG

#ifdef NEPTUNE_RELEASE

// Core log macros
#define SPICES_CORE_TRACE(...)    
#define SPICES_CORE_INFO(...)     
#define SPICES_CORE_WARN(...)     
#define SPICES_CORE_ERROR(...)    
#define SPICES_CORE_CRITICAL(...) 

// Client log macros
#define NEPTUNE_TRACE(...)
#define NEPTUNE_INFO(...)
#define NEPTUNE_WARN(...)
#define NEPTUNE_ERROR(...)
#define NEPTUNE_CRITICAL(...)

#endif // NEPTUNE_RELEASE