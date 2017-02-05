#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <common/IElfBoxEngine.h>
namespace elfbox
{
    class ElfBoxEngine : public IElfBoxEngine
    {
        ELF_OBJECT(ElfBoxEngine, IElfBoxEngine);
    public:
        ElfBoxEngine();
        virtual ~ElfBoxEngine();
        virtual void run();
    };
}
#endif
