#include <EntryPoint.h>
#include <World/Scene/Scene.h>

namespace Neptune {

    SP<Scene> CreateDocument()
    {
        return CreateSP<Scene>();
    }

}