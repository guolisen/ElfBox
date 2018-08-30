#include <SDL.h>
#include <memory>

#include "IApplicationCore.h"
#include <common/Application.h>
#include <gamelogic/IEngine.h>
#include <gamelogic/Engine.h>
#include <common/Context.h>
#include <common/MessageBroadcaster.h>
#include <graphics/Graphics.h>
#include <graphics/detail/GraphicsSDLImpl.h>
#include <system/Window.h>
#include <system/detail/WindowSDLImpl.h>
#include <system/ThreadPool.h>
#include <system/TimeService.h>
#include <system/detail/TimeServiceImpl.h>
#include <render/RenderDevice.h>
#include <render/detail/RenderDeviceImpl.h>
#include <system/ResourceCache.h>
#include <system/detail/ResourceWrapper.h>
#include <render/RenderMaterial.h>
#include <system/SystemEventProcess.h>
#include <system/detail/SystemEventProcessImpl.h>
#include <common/ObjectFactory.h>
#include <gamelogic/scene/Scene.h>
#include <gamelogic/scene/SceneNodeFactory.h>
#include <gamelogic/scene/SceneManager.h>
#include <sm/State.h>
#include <sm/StateEvent.h>
#include <sm/StateMachine.h>
#include <sm/detail/StateMachineImpl.h>
#include <script/ScriptCenter.h>
#include <script/detail/ScriptCenterImpl.h>
#include <gamelogic/GameDirector.h>
#include <gamelogic/IGameDirector.h>
#include <gamelogic/GameData.h>
#include <gamelogic/IGameData.h>
#include <gamelogic/IGameManager.h>
#include <gamelogic/GameManager.h>

namespace elfbox
{
namespace common
{
Application::Application(
        std::shared_ptr<common::IApplicationCore> applicationCore,
        std::shared_ptr<Context> context) :
        context_(context),
        elfBoxEngine_(context_->getComponent<gamelogic::IEngine>(nullptr)),
        applicationCore_(applicationCore),
        log_(context_->getComponent<ILogger>(nullptr))
{
    ELFBOX_LOGDEBUG(log_, "Application::Application() %d %s", 111, "OK");
}

Application::~Application()
{
    ELFBOX_LOGDEBUG(log_, "~Application::Application() %d %s", 111, "OK");
}

void Application::run()
{
    ELFBOX_LOGDEBUG(log_, "Application::run() %d %s", 111, "OK");
    setup();
    start();

    elfBoxEngine_->run();

    terminat();
}

bool Application::setup()
{
    ELFBOX_LOGDEBUG(log_, "Application::setup() %d %s", 111, "OK");
    //TODO: configure by xml
    system::ThreadPoolPtr threadPool =
        context_->getComponent<system::IThreadPool>(nullptr);
    threadPool->createThreads(4);

    common::MessageBroadcasterPtr messageBroadcaster =
        context_->getComponent<common::IMessageBroadcaster>(nullptr);
    messageBroadcaster->initialize();

    system::TimeServicePtr timeService =
        context_->getComponent<system::ITimeService>(nullptr);
    timeService->initialize();
    timeService->reset();
    
    elfBoxEngine_->initialize();

    if (applicationCore_)
        applicationCore_->setup();

    return false;
}

bool Application::start()
{
    ELFBOX_LOGDEBUG(log_, "Application::start() %d %s", 111, "OK");

    elfBoxEngine_->start();
    if (applicationCore_)
        applicationCore_->start();
    return false;
}

bool Application::terminat()
{
    ELFBOX_LOGDEBUG(log_, "Application::terminat() %d %s", 111, "OK");
    if (applicationCore_)
        applicationCore_->terminat();
    return false;
}
}
}

void appMain()
{
    elfbox::common::ContextPtr context = std::make_shared<elfbox::common::Context>();
    context->addComponent(std::make_shared<elfbox::BaseLogger>());

    elfbox::common::ObjectFactoryPtr objectFactory =
        std::make_shared<elfbox::common::ObjectFactory>();
    context->addComponent(objectFactory);

    objectFactory->registerFactory<elfbox::scene::IScene>(
        elfbox::scene::Scene::getFactory());
    objectFactory->registerFactory<elfbox::scene::ISceneNode>(
        std::make_shared<elfbox::scene::SceneNodeFactory>(context));
    objectFactory->registerFactory<elfbox::sm::IState>(
        elfbox::sm::State::getFactory());
    //objectFactory->registerFactory<elfbox::sm::IStateEvent>(
    //    elfbox::sm::StateEvent::getFactory());

    elfbox::graphics::GraphicsPtr graphics = std::make_shared<elfbox::graphics::Graphics>(
            std::make_shared<elfbox::graphics::detail::GraphicsImpl>(context));
    context->addComponent(graphics);

    elfbox::system::WindowPtr window = std::make_shared<elfbox::system::Window>(
            std::make_shared<elfbox::system::detail::WindowImpl>(context));
    context->addComponent(window);

    elfbox::system::ThreadPoolPtr threadPool = std::make_shared<elfbox::system::ThreadPool>(
        context, elfbox::system::detail::Thread::getFactory());
    context->addComponent(threadPool);

    elfbox::common::MessageBroadcasterPtr messageBroadcaster =
            std::make_shared<elfbox::common::MessageBroadcaster>(context);
    context->addComponent(messageBroadcaster);

    elfbox::system::TimeServicePtr timeService =
        std::make_shared<elfbox::system::TimeService>(threadPool, messageBroadcaster,
            std::make_shared<elfbox::system::detail::TimeServiceImpl>(context));
    context->addComponent(timeService);

    elfbox::render::RenderDevicePtr renderDevice =
        std::make_shared<elfbox::render::RenderDevice>(
            std::make_shared<elfbox::render::detail::RenderDeviceImpl>(context));
    context->addComponent(renderDevice);

    elfbox::system::ResourceCachePtr resourceCache =
        std::make_shared<elfbox::system::ResourceCache>(
            context, elfbox::system::detail::ResourceWrapper::getFactory());
    context->addComponent(resourceCache);

    elfbox::system::ResourceCachePtr cache =
        context->getComponent<elfbox::system::IResourceCache>(nullptr);
    cache->registerResourceFactory<elfbox::render::IRenderMaterial>(
        elfbox::render::RenderMaterial::getFactory());

    elfbox::system::SystemEventProcessPtr systemEventProcess =
        std::make_shared<elfbox::system::SystemEventProcess>(
            std::make_shared<elfbox::system::detail::SystemEventProcessImpl>(context));
    context->addComponent(systemEventProcess);

    elfbox::script::ScriptCenterPtr scriptCenter =
        std::make_shared<elfbox::script::ScriptCenter>(context,
            std::make_shared<elfbox::script::detail::ScriptCenterImpl>(context));
    context->addComponent(scriptCenter);

    elfbox::sm::StateMachinePtr stateMachine =
        std::make_shared<elfbox::sm::StateMachine>(
        std::make_shared<elfbox::sm::detail::StateMachineImpl>(context));
    context->addComponent(stateMachine);

    elfbox::gamelogic::GameDirectorPtr gameDirector =
        std::make_shared<elfbox::gamelogic::GameDirector>(context);
    context->addComponent(gameDirector);

    elfbox::gamelogic::GameDataPtr gameData =
        std::make_shared<elfbox::gamelogic::GameData>(context);
    elfbox::scene::SceneManagerPtr sceneManager =
        std::make_shared<elfbox::scene::SceneManager>(context);
    context->addComponent(std::make_shared<elfbox::gamelogic::Engine>(
        context, gameDirector, gameData, sceneManager));

    elfbox::gamelogic::GameManagerPtr gameManager =
        std::make_shared<elfbox::gamelogic::GameManager>(
            context, gameDirector, gameData, sceneManager);
    context->addComponent(gameManager);

    elfbox::common::Application app(0, context);
    app.run();

    printf("sddddd\n");
}
