#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <common/IElfBoxEngine.h>
#include <common/Context.h>

namespace elfbox
{
namespace common
{
class ElfBoxEngine : public IElfBoxEngine
{
ELF_OBJECT(ElfBoxEngine, IElfBoxEngine);
public:
    ElfBoxEngine(ContextPtr context);

    virtual ~ElfBoxEngine();

    virtual bool Initialize();

    virtual void run();

private:
    ContextPtr context_;
};
}
}
#endif
