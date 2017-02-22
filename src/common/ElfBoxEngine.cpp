#include <SDL.h>
#include <common/ElfBoxEngine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>
#include <system/ITimeService.h>
#include <util/BaseLogger.h>
#include <common/IMessageBroadcaster.h>
#include <render/ImageDrawable.h>

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

void ElfBoxEngine::threadTest(unsigned id)
{
    drawable2_->getData().worldRect.x += 10;
    if (drawable2_->getData().worldRect.x > 400)
        drawable2_->getData().worldRect.x = 0;

    drawable2_->getData().worldRect.y += 1;
    if (drawable2_->getData().worldRect.y > 400)
        drawable2_->getData().worldRect.y = 0;
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

    drawable1_ = std::make_shared<render::ImageDrawable>(
        context_, "E:/code/ElfClion/ElfBox/cmake-build-debug/res/1.jpg");
    drawable1_->loadMaterial();
    renderDevice_->addDrawable(drawable1_);

    drawable2_ = std::make_shared<render::ImageDrawable>(
        context_, "E:/code/ElfClion/ElfBox/cmake-build-debug/res/2.jpg");
    drawable2_->loadMaterial();
    drawable2_->getData().worldRect.x = 200;
    drawable2_->getData().worldRect.y = 0;
    renderDevice_->addDrawable(drawable2_);

    system::TimeServicePtr timeService =
        context_->getComponent<system::ITimeService>(nullptr);
    timeService->createTimer(std::bind(&ElfBoxEngine::threadTest,
                                       this, std::placeholders::_1), 1000, true);
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

    elapsed = timeService->getMicroseconds() - lastTime;
    lastTime = timeService->getMicroseconds();

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
    common::MessageBroadcasterPtr messageBroadcaster =
        context_->getComponent<common::IMessageBroadcaster>(nullptr);

    SDL_Event Event;
    while(true) {
        while(SDL_PollEvent(&Event)) {
            //OnEvent(&Event);
        }

        messageBroadcaster->notifyMessage(-1);
        renderDevice_->render(timeStep_);
        applyTimeStep();
    }
}

void ElfBoxEngine::render()
{

}

void ElfBoxEngine::update()
{

}

}
}