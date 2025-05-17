#include <EntryPoint.h>
#include "SandBoxDocument.h"

namespace Neptune {

    SP<Document> CreateDocument()
    {
        return CreateSP<SandBoxDocument>();
    }

}