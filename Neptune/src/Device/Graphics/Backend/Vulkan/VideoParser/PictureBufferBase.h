#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include <assert.h>
#include <atomic>
#include <stdint.h>
#include <string.h>
#include <any>

namespace Neptune::Vulkan {

    class VkPicIf {
    public:
        virtual void AddRef() = 0;
        virtual void Release() = 0;
    protected:
        virtual ~VkPicIf() {}
    public:
        uint32_t decodeWidth;
        uint32_t decodeHeight;
        uint32_t decodeSuperResWidth;
    };

    class vkPicBuffBase : public VkPicIf {
    private:
        std::atomic<int32_t> m_refCount;

    public:
        int32_t  m_picIdx;
        uint32_t m_displayOrder;
        uint64_t m_decodeOrder;
        uint64_t m_timestamp;

    public:
        virtual void AddRef()
        {
            assert(m_refCount >= 0);
            ++m_refCount;
        }
        virtual void Release()
        {
            assert(m_refCount > 0);
            int32_t ref = --m_refCount;
            if (ref == 0) {
                Reset();
            }
        }

        vkPicBuffBase()
            : m_refCount(0)
            , m_picIdx(-1)
            , m_displayOrder((uint32_t)-1)
            , m_decodeOrder(0)
            , m_timestamp(0)
        {
        }

        virtual bool IsAvailable() const
        {
            assert(m_refCount >= 0);
            return (m_refCount == 0);
        }

        int32_t Reset()
        {
            int32_t ref = m_refCount;
            m_refCount = 0;
            return ref;
        }

        virtual ~vkPicBuffBase()
        {
            Reset();
        }
    };

    class VkPicIf2 : public vkPicBuffBase {
    public:

        void AddRef() override {}
        void Release() override {}

        bool IsAvailable() const override { return true; }

    public:
        virtual ~VkPicIf2() {}
    };

}

#endif