#pragma once
#include <stdint.h>

namespace Neptune::Vulkan {

    enum class SIMD_ISA : uint8_t
    {
        NOSIMD = 0,
        SSSE3,
        AVX2,
        AVX512,
        NEON,
        SVE,

        Count
    };

    static int inline count_trailing_zeros(unsigned long long resmask)
    {
#ifdef _WIN64
        unsigned long offset = 0;
        const unsigned char dummyIsNonZero = _BitScanForward64(&offset, resmask); // resmask can't be 0 in this if
#elif _WIN32
        unsigned long offset = 0;
        const unsigned char isNonZero = _BitScanForward(&offset, (unsigned long)(resmask >> 32U)); // resmask can't be 0 in this if
        if (isNonZero) {
            offset += 32U;
        }
        else {
            _BitScanForward(&offset, (unsigned long)resmask); // resmask can't be 0 in this if
        }
#else
        int offset = __builtin_ctzll(resmask);
#endif
        return offset;
    }

    SIMD_ISA GetSIMD();

}