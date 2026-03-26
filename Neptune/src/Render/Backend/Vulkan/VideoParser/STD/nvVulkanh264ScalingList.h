#pragma once
#include <stdint.h>

namespace Neptune::Vulkan {

    enum NvScalingListTypeH264 {
        SCALING_LIST_NOT_PRESENT = 0,
        SCALING_LIST_PRESENT,
        SCALING_LIST_USE_DEFAULT,
    };

    struct NvScalingListH264
    {
        int32_t scaling_matrix_present_flag : 1;
        uint8_t scaling_list_type[8]; // scaling_list_type_e
        uint8_t ScalingList4x4[6][16];
        uint8_t ScalingList8x8[2][64];
    };

    bool SetSeqPicScalingListsH264(const NvScalingListH264* pSeqScalingList,
        const NvScalingListH264* pPicScalingList,
        uint8_t pWeightScale4x4[6][4][4],
        uint8_t pWeightScale8x8[2][8][8]);

}