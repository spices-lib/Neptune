#pragma once
#include "Core/Core.h"
#include <unordered_map>

namespace Neptune {

	// TODO: Remove it.
	template<typename T>
	class ResourcePool
	{
	public:

		static ResourcePool& Instance()
		{
			static ResourcePool instance;

			return instance;
		}

	public:

		ResourcePool() = default;
		virtual ~ResourcePool() = default;

		void Reset() { m_Resources.clear(); }

		template<typename... Args>
		SP<T> CreateResource(const std::string& name, Args&&... args)
		{
			auto sp = CreateSP<T>(std::forward<Args>(args)...);
			sp->SetName(name);
			m_Resources[name] = sp;
			
			return sp;
		}

		bool HasResource(const std::string& name) { return m_Resources.contains(name); }

		SP<T> GetResource(const std::string& name) { return m_Resources[name]; }

	private:

		std::unordered_map<std::string, SP<T>> m_Resources;
	};
}
