#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <vector>
#include <common/IEngine.h>
#include <common/Context.h>
#include <render/RenderDevice.h>
#include <render/detail/RenderDeviceImpl.h>
#include <util/BaseLogger.h>
#include <render/ImageDrawable.h>

#include <scene/Scene.h>

namespace elfbox
{
namespace common
{
class Engine : public IEngine
{
ELF_OBJECT(Engine, IEngine);
public:
    Engine(ContextPtr context);
    virtual ~Engine();

    virtual bool initialize();
    virtual void run();
    virtual void applyTimeStep();
    virtual void render();
    virtual void update();

    void threadTest(unsigned id);
private:
    ContextPtr context_;
    LoggerPtr log_;
    render::RenderDevicePtr renderDevice_;

    float timeStep_;
    std::vector<float> lastTimeSteps_;
    unsigned int timeStepSmoothing_;

    render::StaticDrawablePtr drawable1_;
    render::StaticDrawablePtr drawable2_;
    render::StaticDrawablePtr drawable3_;

    scene::Scene scene_;
};
}
}
#endif
