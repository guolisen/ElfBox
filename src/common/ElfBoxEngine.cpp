#include <common/ElfBoxEngine.h>
#include <util/BaseLogger.h>
namespace elfbox
{
    ElfBoxEngine::ElfBoxEngine(ContextPtr context) : context_(context)
    {
        LoggerPtr log =  context_->getComponent<BaseLogger>(nullptr);

        ELFBOX_LOGERROR(log, "Test!!!!");
    }

    ElfBoxEngine::~ElfBoxEngine()
    {
    }

    void ElfBoxEngine::run()
    {
        LoggerPtr log = context_->getComponent<BaseLogger>(nullptr);

        ELFBOX_LOGERROR(log, "Run!!!!");
    }
}