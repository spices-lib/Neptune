#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include <CL/sycl.hpp>

namespace Neptune::SYCL {

	int test()
	{
		cl::sycl::queue q;

		std::cout << "Running on " << q.get_device().get_info<cl::sycl::info::device::name>();
	}

}

#endif