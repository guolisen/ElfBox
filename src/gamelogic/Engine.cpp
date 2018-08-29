

#include <gamelogic/Engine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>
#include <system/ITimeService.h>
#include <common/IMessageBroadcaster.h>
#include <render/ImageDrawable.h>
#include <system/IResource.h>
#include <system/IResourceCache.h>
#include <system/ISystemEventProcess.h>
#include <sm/State.h>
#include <sm/StateEvent.h>
#include <sm/StateMachine.h>
#include <sm/detail/StateMachineImpl.h>
#include <script/ScriptCenter.h>
#include <script/detail/ScriptCenterImpl.h>

namespace elfbox
{
namespace gamelogic
{
Engine::Engine(common::ContextPtr context, GameDirectorPtr gameDirector,
               GameDataPtr gameData, scene::SceneManagerPtr sceneManager) :
    context_(context), gameDirector_(gameDirector), gameData_(gameData),
    sceneManager_(sceneManager),
    log_(context_->getComponent<ILogger>(nullptr)),
    timeStep_(0.0), timeStepSmoothing_(2),
    scriptCenter_(context_->getComponent<script::IScriptCenter>(nullptr)),
    mainStateMachine_(context_->getComponent<sm::IStateMachine>(nullptr)),
    window_(context_->getComponent<system::IWindow>(nullptr)),
    graphics_(context_->getComponent<graphics::IGraphics>(nullptr)),
    timeService_(context_->getComponent<system::ITimeService>(nullptr)),
    renderDevice_(context_->getComponent<render::IRenderDevice>(nullptr)),
    scene_(context_)
{
    ELFBOX_LOGERROR(log_, "Test!!!!");
}

Engine::~Engine()
{
    ELFBOX_LOGERROR(log_, "D!!!!");
}

bool Engine::initialize()
{
    ELFBOX_ASSERT(graphics_);
    graphics_->initialize();

    ELFBOX_ASSERT(window_);
    window_->initialize();

    scriptCenter_->initialize();
    sceneManager_->initialize();
    renderDevice_->initialize();

    mainStateMachine_->load("E:/code/ElfClion/ElfBox/res/MainStateMachine.xml");

    return true;
}

void Engine::applyTimeStep()
{
    static long long lastTime = timeService_->getMicroseconds();
    long long elapsed = 0;
    unsigned maxFps = 60;

    long long targetMax = 1000000LL / maxFps;

    for (;;)
    {
        elapsed = timeService_->getMicroseconds() - lastTime;
        if (elapsed >= targetMax)
            break;

        // Sleep if 1 ms or more off the frame limiting goal
        if (targetMax - elapsed >= 1000LL)
        {
            unsigned sleepTime = (unsigned)((targetMax - elapsed) / 1000LL);
            timeService_->sleep(sleepTime);
        }
    }

    elapsed = timeService_->getMicroseconds() - lastTime;
    lastTime = timeService_->getMicroseconds();

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

    system::SystemEventProcessPtr systemEventProcess =
        context_->getComponent<system::ISystemEventProcess>(nullptr);

    while(true) {
        systemEventProcess->run();
        messageBroadcaster->notifyMessage(-1);

        update();
        render();
        applyTimeStep();
    }
}

void Engine::render()
{
    renderDevice_->render(timeStep_);
}

void Engine::update()
{
    mainStateMachine_->update(timeStep_);
    gameDirector_->update(timeStep_);
    sceneManager_->update(timeStep_);
}

void Engine::start()
{
    mainStateMachine_->start();
}
}
}