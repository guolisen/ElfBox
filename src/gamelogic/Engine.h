#ifndef common_ElfBoxEngine
#define common_ElfBoxEngine

#include <vector>
#include <gamelogic/IEngine.h>
#include <common/Context.h>
#include <render/RenderDevice.h>
#include <render/detail/RenderDeviceImpl.h>
#include <util/BaseLogger.h>
#include <render/ImageDrawable.h>
#include <scene/Scene.h>
#include <sm/IStateMachine.h>
#include <system/IWindow.h>
#include <script/IScriptCenter.h>
#include <gamelogic/IGameDirector.h>
#include <gamelogic/IGameData.h>
#include <gamelogic/IGameManager.h>
#include <system/ITimeService.h>
#include <scene/ISceneManager.h>

namespace elfbox
{
namespace gamelogic
{
class Engine : public IEngine
{
ELF_OBJECT(Engine, IEngine);
public:
    Engine(common::ContextPtr context,
           GameDirectorPtr gameDirector,
           GameDataPtr gameData,
           scene::SceneManagerPtr sceneManager);
    virtual ~Engine();

    virtual bool initialize();
    virtual void start();
    virtual void run();

    virtual void render();
    virtual void update();

private:
    virtual void applyTimeStep();

    common::ContextPtr context_;
    GameDirectorPtr gameDirector_;
    GameDataPtr gameData_;
    scene::SceneManagerPtr sceneManager_;
    LoggerPtr log_;
    render::RenderDevicePtr renderDevice_;

    float timeStep_;
    std::vector<float> lastTimeSteps_;
    unsigned int timeStepSmoothing_;

    script::ScriptCenterPtr scriptCenter_;
    sm::StateMachinePtr mainStateMachine_;
    system::WindowPtr window_;
    graphics::GraphicsPtr graphics_;
    system::TimeServicePtr timeService_;

    scene::Scene scene_;
};
}
}
#endif
