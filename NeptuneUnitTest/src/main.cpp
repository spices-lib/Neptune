/**
* @file main.cpp.
* @brief The main function Implementation.
* @author Spices.
*/

#include "Core/Log/Log.h"
#include "Instrumentor.h"

#include <gmock/gmock.h>
#include <memory>

/**
* @brief The Entry of NeptuneUnitTest.
*/
int main(int argc, char** argv)
{
    try
    {
        NEPTUNE_TEST_PROFILE_BEGIN_SESSION("Instruments", "NeptuneProfile-UnitTest.json");

        // Init GoogleMock.
        testing::InitGoogleMock(&argc, argv);

        // Execute all unit tests.
        const int result = RUN_ALL_TESTS();

        NEPTUNE_TEST_PROFILE_END_SESSION();
    }
    catch (const std::exception& ex)
    {
        NEPTUNE_CORE_ERROR(ex.what())

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}