/**
* @file main.cpp.
* @brief The main function Implementation.
* @author Spices.
*/

#include <Core/MetaProperty.h>

#ifdef MetaProperty(...)
#undef MetaProperty(...)
#define MetaProperty(...) public:
#endif

#include "Instrumentor.h"

#include "Core/Container/BitSetTest.h"
#include "Core/Container/TreeTest.h"

#include "GPURuntime/Graphics/Backend/Common/CommonTest.h"
#include "GPURuntime/Graphics/Backend/Direct3D11/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/Direct3D12/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/Metal/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/OpenGL/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/Vulkan/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/WebGL/GraphicsBackendTest.h"
#include "GPURuntime/Graphics/Backend/WebGPU/GraphicsBackendTest.h"

#include <Core/Log/Log.h>

/**
* @brief The Entry of NeptuneUnitTest.
*/
int main(int argc, char** argv)
{
    try
    {
        NEPTUNE_TEST_PROFILE_BEGIN_SESSION("Instruments", "NeptuneProfile-UnitTest.json")

        // Init GoogleMock.
        testing::InitGoogleMock(&argc, argv);

        // Execute all unit tests.
        const int result = RUN_ALL_TESTS();

        NEPTUNE_TEST_PROFILE_END_SESSION
    }
    catch (const std::exception& ex)
    {
        NEPTUNE_CORE_ERROR(ex.what())

        Neptune::Log::Reset();
        
        return EXIT_FAILURE;
    }

    Neptune::Log::Reset();
    
    return EXIT_SUCCESS;
}