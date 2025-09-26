/**
* @file BitSet.hpp.
* @brief The BitSet Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <bitset>
#include <shared_mutex>

namespace Neptune {

    /**
    * @brief Bit Set.
    * 
    * @tparam T specific stored type.
    */
    template<typename T>
    class BitSet
    {
    public:

        /**
        * @brief Size Type of T.
        */
        using TSize = std::underlying_type_t<T>;

    private:

        /**
        * @brief Stoted bitset.
        */
        std::bitset<static_cast<size_t>(T::ALL)> m_Bits{};

        /**
        * @brief Mutex.
        */
        mutable std::shared_mutex m_Mutex;

    public:

        /**
        * @brief Constructor Function.
        */
        BitSet() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~BitSet() = default;

        /**
        * @brief Copy Constructor Function.
        *
        * @param[in] other BitSet.
        */
        BitSet(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = other.m_Bits;
        }

        /**
        * @brief Copy Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = other.m_Bits;

            return *this;
        }

        /**
        * @brief Move Constructor Function.
        *
        * @param[in] other BitSet.
        */
        BitSet(BitSet&& other) noexcept
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = std::move(other.m_Bits);
        }

        /**
        * @brief Move Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(BitSet&& other) noexcept
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = std::move(other.m_Bits);

            return *this;
        }

        /**
        * @brief | Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns new BitSet.
        */
        BitSet operator|(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            BitSet result;

            result.m_Bits = m_Bits | other.m_Bits;

            return result;
        }

        /**
        * @brief & Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns new BitSet.
        */
        BitSet operator&(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            BitSet result;

            result.m_Bits = m_Bits & other.m_Bits;

            return result;
        }

        /**
        * @brief |= Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet& operator|=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits |= other.m_Bits;

            return *this;
        }

        /**
        * @brief &= Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet& operator&=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits &= other.m_Bits;

            return *this;
        }

        /**
        * @brief == Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns true if equal.
        */
        bool operator==(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits == other.m_Bits;
        }

        /**
        * @brief != Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns true if not equal.
        */
        bool operator!=(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits != other.m_Bits;
        }

        /**
        * @brief To TSize.
        *
        * @return Returns TSize.
        */
        explicit operator TSize() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return static_cast<TSize>(m_Bits.to_ulong());
        }

        /**
        * @brief Set bit with value.
        *
        * @param[in] bit Bit item.
        * @param[in] value Bit value.
        */
        void Set(T bit, bool value)
        {
            if (bit == T::ALL)
            {
                Reset();

                if (value)
                {
                    Flip();
                }
            }
            else 
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.set(static_cast<size_t>(static_cast<TSize>(bit)), value);
            }
        }

        /**
        * @brief Test bit.
        *
        * @param[in] bit Bit item.
        *
        * @return Returns bit value.
        */
        bool Test(T bit) const
        {
            if (bit == T::ALL)
            {
                return !None();
            }
            else
            {
                std::shared_lock<std::shared_mutex> lock(m_Mutex);

                return m_Bits.test(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        /**
        * @brief Reset all bits.
        */
        void Reset()
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits.reset();
        }

        /**
        * @brief Reset bit.
        *
        * @param[in] bit Bit item.
        */
        void Reset(T bit)
        {
            if (bit == T::ALL)
            {
                Reset();
            }
            else
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.reset(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        /**
        * @brief Flip all bits.
        */
        void Flip()
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits.flip();
        }

        /**
        * @brief Flip bit.
        *
        * @param[in] bit Bit item.
        */
        void Flip(T bit)
        {
            if (bit == T::ALL)
            {
                Flip();
            }
            else
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.flip(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        /**
        * @brief Is any bit set.
        *
        * @return Returns true if exist bit not set.
        */
        bool Any() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits.any();
        }

        /**
        * @brief Is all bits not set.
        *
        * @return Returns true if all bits not set.
        */
        bool None() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits.none();
        }

    };

}
