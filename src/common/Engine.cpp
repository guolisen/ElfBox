#include <SDL.h>
#include <common/Engine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>
#include <system/ITimeService.h>

#include <common/IMessageBroadcaster.h>
#include <render/ImageDrawable.h>
#include <system/IResource.h>
#include <system/IResourceCache.h>

namespace elfbox
{
namespace common
{
Engine::Engine(ContextPtr context) :
    context_(context), log_(context_->getComponent<ILogger>(nullptr)),
    timeStep_(0.0), timeStepSmoothing_(2),
    renderDevice_(context_->getComponent<render::IRenderDevice>(nullptr)),
    scene_(context_)
{
    ELFBOX_LOGERROR(log_, "Test!!!!");
}

Engine::~Engine()
{
    ELFBOX_LOGERROR(log_, "D!!!!");
}

void Engine::threadTest(unsigned id)
{
    drawable2_->getData().worldRect.x += 10;
    if (drawable2_->getData().worldRect.x > 400)
        drawable2_->getData().worldRect.x = 0;

    drawable2_->getData().worldRect.y += 1;
    if (drawable2_->getData().worldRect.y > 400)
        drawable2_->getData().worldRect.y = 0;
}

bool Engine::initialize()
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

    scene_.initialize();
    scene_.load("E:/code/s/map/T22.tmx");
    scene_.update(0.0);

#if 0
    //////1
    drawable1_ = std::make_shared<render::ImageDrawable>(context_);

    elfbox::system::ResourceCachePtr cache =
        context_->getComponent<elfbox::system::IResourceCache>(nullptr);
    elfbox::render::RenderMaterialPtr material =
        cache->getResource<elfbox::render::IRenderMaterial>(
            std::string("E:/code/ElfClion/ElfBox/cmake-build-debug/res/1.jpg"));
    if (!material)
    {
        ELFBOX_LOGERROR(log_, "1.jpg read error!");
        return false;
    }
    drawable1_->setMaterial(material);
    renderDevice_->addDrawable(drawable1_);

    ////2
    drawable2_ = std::make_shared<render::ImageDrawable>(context_);
    elfbox::render::RenderMaterialPtr material2 =
        cache->getResource<elfbox::render::IRenderMaterial>(
            std::string("E:/code/ElfClion/ElfBox/cmake-build-debug/res/2.jpg"));
    if (!material2)
    {
        ELFBOX_LOGERROR(log_, "2.jpg read error!");
        return false;
    }
    drawable2_->setMaterial(material2);
    drawable2_->getData().worldRect.x = 200;
    renderDevice_->addDrawable(drawable2_);

    //////3
    drawable3_ = std::make_shared<render::ImageDrawable>(context_);

    elfbox::render::RenderMaterialPtr material3 =
        cache->getResource<elfbox::render::IRenderMaterial>(
        std::string("E:/code/ElfClion/ElfBox/cmake-build-debug/res/1.jpg"));
    if (!material3)
    {
        ELFBOX_LOGERROR(log_, "1.jpg 2 read error!");
        return false;
    }
    drawable3_->setMaterial(material3);
    drawable3_->getData().worldRect.x = 100;
    drawable3_->getData().worldRect.y = 200;

    renderDevice_->addDrawable(drawable3_);

    system::TimeServicePtr timeService =
        context_->getComponent<system::ITimeService>(nullptr);
    timeService->createTimer(std::bind(&Engine::threadTest,
                                       this, std::placeholders::_1), 1000, true);
#endif


    return true;
}

void Engine::applyTimeStep()
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

void Engine::run()
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

void Engine::render()
{

}

void Engine::update()
{

}

}
}