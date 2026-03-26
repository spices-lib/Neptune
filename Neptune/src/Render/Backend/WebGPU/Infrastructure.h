/**
* @file Infrastructure.h.
* @brief The Infrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Utils.h"

namespace Neptune::WebGPU {

    /**
    * @brief InfrastructureBase Class.
    */
    class InfrastructureBase : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPU Context.
        */
        explicit InfrastructureBase(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~InfrastructureBase() override;

    protected:

        /**
        * @brief Template of Add Ref.
        *
        * @tparam T The WebGPUObject.
        */
        template<typename T>
        static void AddRef(T*);

        /**
        * @brief Template of Release WebGPU Object.
        *
        * @tparam T The WebGPUObject.
        */
        template<typename T>
        static void Release(T*);

        /**
        * @brief Template of SetLabel WebGPU Object.
        *
        * @tparam T The WebGPUObject.
        * @param[in] label Label.
        */
        template<typename T>
        static void SetLabel(T*, const std::string& label) {}

    protected:

        /**
        * @brief Wait delegate to be down.
        *
        * @param[in] future WGPUFuture.
        */
        void Wait(const WGPUFuture& future);

    protected:

        /**
        * @brief The global WebGPU Context Referenced from WebGPU RenderBackend.
        */
        Context& m_Context;

    };

    /**
    * @brief Infrastructure Class.
    * This class defines the basic behaves of Infrastructure.
    * When we create an new Infrastructure, we need inherit from this.
    */
    template<typename H, EInfrastructure T>
    class Infrastructure : public InfrastructureBase
    {
    public:

        /**
        * @brief Mark as Infrastructure Type.
        */
        static constexpr EInfrastructure Type = T;

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPU Context.
        */
        explicit Infrastructure(Context& context)
            : InfrastructureBase(context)
        {}

        /**
        * @brief Destructor Function.
        */
    	~Infrastructure() override = default;

    public:

        /**
        * @brief Get WebGPU Infrastructure Handle.
        *
        * @return Returns WebGPU Infrastructure Handle.
        */
        const H& Handle() { return m_Handle; }

        /**
        * @brief Set WebGPU Infrastructure Handle to nullptr.
        */
        void SetHandleNullptr() { m_Handle = nullptr; }

    protected:

        /**
        * @brief WebGPU Handle.
        */
        H m_Handle = nullptr;

    };

    template <typename T>
    void InfrastructureBase::AddRef(T*)
    {
        NEPTUNE_CORE_WARN("WebGPU Infrastructure Not implement AddRef API.")
    }

    template <typename T>
    void InfrastructureBase::Release(T*)
    {
        NEPTUNE_CORE_WARN("WebGPU Infrastructure Not implement Release API.")
    }
    
}

#endif