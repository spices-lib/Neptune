#include "Pchheader.h"
#include "Sample.h"

#ifdef NP_COMPUTE_SYCL

#include <CL/sycl.hpp>

namespace Neptune::SYCL {
	
	void Sample()
    {
        cl::sycl::queue q;

        std::stringstream ss;
        ss << "SYCL Device: " << q.get_device().get_info<cl::sycl::info::device::name>();
		
        NEPTUNE_CORE_INFO(ss.str())
    }
	
}

#endif