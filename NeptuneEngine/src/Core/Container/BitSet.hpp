/**
* @file BitSet.hpp.
* @brief The BitSet Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include <bitset>

#include "Core/Core.h"

namespace Neptune::Container {

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
        std::bitset<static_cast<size_t>(T::Count)> m_Bits{};

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
            m_Bits = other.m_Bits;
        }

        /**
        * @brief Copy Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(const BitSet& other)
        {
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
            m_Bits = std::move(other.m_Bits);
        }

        /**
        * @brief Move Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(BitSet&& other) noexcept
        {
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
        BitSet operator|(const BitSet& other)
        {
            BitSet result;

            result.m_Bits = m_Bits | other.m_Bits;

            return result;
        }

        /**
        * @brief & Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet operator&(const BitSet& other)
        {
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
            return m_Bits != other.m_Bits;
        }

        /**
        * @brief To TSize.
        *
        * @return Returns TSize.
        */
        explicit operator TSize() const
        {
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
            m_Bits.set(static_cast<size_t>(static_cast<TSize>(bit)), value);
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
            return m_Bits.test(static_cast<size_t>(static_cast<TSize>(bit)));
        }

        /**
        * @brief Reset all bits.
        */
        void Reset()
        {
            m_Bits.reset();
        }

        /**
        * @brief Reset bit.
        *
        * @param[in] bit Bit item.
        */
        void Reset(T bit)
        {
            m_Bits.reset(static_cast<size_t>(static_cast<TSize>(bit)));
        }

        /**
        * @brief Flip all bits.
        */
        void Flip()
        {
            m_Bits.flip();
        }

        /**
        * @brief Flip bit.
        *
        * @param[in] bit Bit item.
        */
        void Flip(T bit)
        {
            m_Bits.flip(static_cast<size_t>(static_cast<TSize>(bit)));
        }

        /**
        * @brief Is any bit set.
        *
        * @return Returns true if exist bit not set.
        */
        bool Any() const
        {
            return m_Bits.any();
        }

        /**
        * @brief Is all bits set.
        *
        * @return Returns true if all bits set.
        */
        bool None() const
        {
            return m_Bits.none();
        }
    };

}
