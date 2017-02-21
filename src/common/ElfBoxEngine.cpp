#include <common/ElfBoxEngine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>
#include <system/ITimeService.h>
#include <util/BaseLogger.h>
#include <render/StaticDrawable.h>

namespace elfbox
{
namespace common
{
ElfBoxEngine::ElfBoxEngine(ContextPtr context) :
    context_(context), timeStep_(0.0), timeStepSmoothing_(2),
    renderDevice_(context_->getComponent<render::IRenderDevice>(nullptr))
{
    LoggerPtr log = context_->getComponent<ILogger>(nullptr);

    ELFBOX_LOGERROR(log, "Test!!!!");
}

ElfBoxEngine::~ElfBoxEngine()
{
    LoggerPtr log = context_->getComponent<ILogger>(nullptr);
    ELFBOX_LOGERROR(log, "D!!!!");
}

bool ElfBoxEngine::initialize()
{
    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    ELFBOX_ASSERT(graphics);
    graphics->initialize();

    system::WindowPtr window =
        context_->getComponent<system::IWindow>(nullptr);
    ELFBOX_ASSERT(window);
    window->initialize();

    window->createWindow("Test1", 1024, 768, 0);

    render::StaticDrawablePtr drawable1 = std::make_shared<render::StaticDrawable>(context_);
    drawable1->material->setFileName("E:/code/ElfClion/ElfBox/cmake-build-debug/res/1.jpg");
    drawable1->material->loadMaterial();
    drawable1->sourceRect = drawable1->material->getRect();
    drawable1->worldRect.x = 0;
    drawable1->worldRect.y = 0;
    drawable1->worldRect.w = drawable1->sourceRect.w;
    drawable1->worldRect.h = drawable1->sourceRect.h;
    renderDevice_->addDrawable(drawable1);

    render::StaticDrawablePtr drawable2 = std::make_shared<render::StaticDrawable>(context_);
    drawable2->material->setFileName("E:/code/ElfClion/ElfBox/cmake-build-debug/res/2.jpg");
    drawable2->material->loadMaterial();
    drawable2->sourceRect = drawable2->material->getRect();
    drawable2->worldRect.x = 200;
    drawable2->worldRect.y = 0;
    drawable2->worldRect.w = drawable2->sourceRect.w;
    drawable2->worldRect.h = drawable2->sourceRect.h;
    renderDevice_->addDrawable(drawable2);

    return true;
}

void ElfBoxEngine::applyTimeStep()
{
    system::TimeServicePtr timeService =
        context_->getComponent<system::ITimeService>(nullptr);
    static long long lastTime = timeService->getMicroseconds();
    long long elapsed = 0;
    unsigned maxFps = 60;

    long long targetMax = 1000000LL / maxFps;

    for (;;)
    {
        elapsed = timeService->getMicroseconds() - lastTime;
        if (elapsed >= targetMax)
            break;

        // Sleep if 1 ms or more off the frame limiting goal
        if (targetMax - elapsed >= 1000LL)
        {
            unsigned sleepTime = (unsigned)((targetMax - elapsed) / 1000LL);
            timeService->sleep(sleepTime);
        }
    }

    elapsed = timeService->getMicroseconds()- lastTime;
    lastTime = timeService->getMicroseconds();

#if 0
    if (minFps_)
    {
        long long targetMin = 1000000LL / minFps_;
        if (elapsed > targetMin)
            elapsed = targetMin;
    }
#endif

    // Perform timestep smoothing
    timeStep_ = 0.0f;
    lastTimeSteps_.push_back(elapsed / 1000000.0f);
    if (lastTimeSteps_.size() > timeStepSmoothing_)
    {
        // If the smoothing configuration was changed, ensure correct amount of samples
        lastTimeSteps_.erase(lastTimeSteps_.begin(), lastTimeSteps_.begin() +
            lastTimeSteps_.size() - timeStepSmoothing_);
        for (auto i = 0; i < lastTimeSteps_.size(); ++i)
            timeStep_ += lastTimeSteps_[i];
        timeStep_ /= lastTimeSteps_.size();
    }
    else
        timeStep_ = lastTimeSteps_.back();
}

void ElfBoxEngine::run()
{
    renderDevice_->render(timeStep_);
    applyTimeStep();
}

void ElfBoxEngine::render()
{

}

void ElfBoxEngine::update()
{

}

}
}