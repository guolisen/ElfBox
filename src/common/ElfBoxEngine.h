#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <common/IElfBoxEngine.h>
#include <common/Context.h>

namespace elfbox
{
    class ElfBoxEngine : public IElfBoxEngine
    {
        ELF_OBJECT(ElfBoxEngine, IElfBoxEngine);
    public:
        ElfBoxEngine(ContextPtr context);
        virtual ~ElfBoxEngine();
        virtual void run();

    private:
        ContextPtr context_;
    };
}
#endif
