#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <vector>
#include <common/IElfBoxEngine.h>
#include <common/Context.h>
#include <render/RenderDevice.h>
#include <render/detail/RenderDeviceImpl.h>

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

    virtual bool initialize();
    virtual void run();
    virtual void applyTimeStep();
    virtual void render();
    virtual void update();
private:
    ContextPtr context_;
    render::RenderDevicePtr renderDevice_;

    float timeStep_;
    std::vector<float> lastTimeSteps_;
    unsigned int timeStepSmoothing_;
};
}
}
#endif
