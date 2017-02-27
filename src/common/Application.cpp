#include <SDL.h>
#include <memory>

#include "IApplicationCore.h"
#include <common/Application.h>
#include <common/IEngine.h>
#include <common/Engine.h>
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

namespace elfbox
{
namespace common
{
Application::Application(
        std::shared_ptr<common::IApplicationCore> applicationCore,
        std::shared_ptr<Context> context) :
        context_(context),
        elfBoxEngine_(context_->getComponent<IEngine>(nullptr)),
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

    context->addComponent(std::make_shared<elfbox::common::Engine>(context));


    elfbox::system::ResourceCachePtr cache =
        context->getComponent<elfbox::system::IResourceCache>(nullptr);
    cache->registerResourceFactory<elfbox::render::IRenderMaterial>(
        elfbox::render::RenderMaterial::getFactory());


    elfbox::common::Application app(0, context);
    app.run();

    /////////////////////////////////////////////////////////
#if 0
    elfbox::system::ThreadPoolPtr pool = context->getComponent<elfbox::system::IThreadPool>(nullptr);
    //pool->createThreads(3);

    pool->attach(std::bind(&testkk), -1);
    pool->attach(std::bind(&test2), -1);
    //pool->attach(std::bind(&elfbox::common::Application::start, &app), -1);
    pool->attach(std::bind(&test3), -1);
    pool->attach(std::bind(&test4), -1);
    pool->attach(std::bind(&test5), -1);

    pool->complete(-1);

    auto item = pool->attach(std::bind(&test6), -1);
    pool->attach(std::bind(&test3), -1);
    pool->attach(std::bind(&test4), -1);
    pool->attach(std::bind(&test5), -1);

    pool->waitForJob(item);
#endif

#if 0
    elfbox::common::MessageBroadcasterPtr mbp =
            context->getComponent<elfbox::common::IMessageBroadcaster>(nullptr);
    mbp->subscribe(elfbox::common::TEST_MESSAGE,
                   std::bind(&messageHandler, std::placeholders::_1));
    mbp->subscribe(elfbox::common::TEST_MESSAGE,
                   std::bind(&messageHandler, std::placeholders::_1));


    elfbox::system::ThreadPoolPtr pool =
            context->getComponent<elfbox::system::IThreadPool>(nullptr);

    pool->attach(std::bind(&testSend, std::placeholders::_1), -1);
    pool->complete(-1);
#endif

#if 0
    elfbox::system::TimeServicePtr time =
        context->getComponent<elfbox::system::ITimeService>(nullptr);
    time->reset();
    uint32_ start = time->getMilliseconds();
    time->sleep(1000);
    uint32_ end = time->getMilliseconds();
    printf("GetMilliseconds: %d\n", end - start);

    start = time->getMilliseconds();
    time->sleep(1000);
    end = time->getMilliseconds();
    printf("GetMilliseconds: %d\n", end - start);

    start = time->getMicroseconds();
    time->sleep(1000);
    end = time->getMicroseconds();
    printf("GetMicroseconds: %d\n", end - start);

    printf("!!!!Start TimeOut1\n");
    gStart = time->getMicroseconds();
    time->createTimer(std::bind(&TimerHandler, std::placeholders::_1), 5000, true);

    //printf("!!!!Start TimeOut2\n");
    //gStart2 = time->getMicroseconds();
    //time->createTimer(std::bind(&TimerHandler2, std::placeholders::_1), 3000, true);

    //gStart2 = time->getMicroseconds();
    //time->createTimer(std::bind(&TimerHandler3, std::placeholders::_1), 7000, false);
    //time->createTimer(std::bind(&TimerHandler3, std::placeholders::_1), 2000, true);
    //time->createTimer(std::bind(&TimerHandler3, std::placeholders::_1), 9000, true);

    elfbox::system::ThreadPoolPtr pool =
        context->getComponent<elfbox::system::IThreadPool>(nullptr);

    pool->complete(-1);
#endif

    printf("sddddd\n");
}
