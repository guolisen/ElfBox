#include <memory>

#include "IApplicationCore.h"
#include <common/Application.h>
#include <common/IElfBoxEngine.h>
#include <common/ElfBoxEngine.h>
#include <common/Context.h>
#include <common/MessageBroadcaster.h>
#include <graphics/IGraphics.h>
#include <graphics/Graphics.h>
#include <graphics/detail/GraphicsSDLImpl.h>
#include <system/IWindow.h>
#include <system/Window.h>
#include <system/detail/WindowSDLImpl.h>
#include <system/ThreadPool.h>
#include <Windows.h>

namespace elfbox
{
namespace common
{
Application::Application(
        std::shared_ptr<common::IApplicationCore> applicationCore,
        std::shared_ptr<Context> context) :
        context_(context),
        elfBoxEngine_(context_->getComponent<IElfBoxEngine>(nullptr)),
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

    //system::ThreadPoolPtr threadPool = context_->getComponent<system::IThreadPool>(nullptr);
    //threadPool->complete(-1);

    terminat();
}

bool Application::setup()
{
    ELFBOX_LOGDEBUG(log_, "Application::setup() %d %s", 111, "OK");

    system::ThreadPoolPtr threadPool = context_->getComponent<system::IThreadPool>(nullptr);
    threadPool->createThreads(4);

    elfbox::common::MessageBroadcasterPtr messageBroadcaster =
            context_->getComponent<elfbox::common::IMessageBroadcaster>(nullptr);
    messageBroadcaster->initialize();

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


struct TestNum
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;

} gVar;

void testkk()
{
    for (int a = 1; a < 10; a++)
    {
        printf("ddddddddddddd\n");
        gVar.a++;
        ::Sleep(1);
    }

}

void test2()
{
    for (int a = 1; a < 10; a++)
    {
        printf("dsdfsfd\n");
        gVar.b++;
        ::Sleep(1);
    }

}

void test3()
{
    for (int a = 1; a < 5; a++)
    {
        printf("3333333333333\n");
        gVar.c++;
        ::Sleep(1);
    }

}

void test4()
{
    for (int a = 1; a < 2; a++)
    {
        printf("444444444444\n");
        gVar.d++;
        ::Sleep(1);
    }

}

void test5()
{
    for (int a = 1; a < 3; a++)
    {
        printf("55555555555\n");
        gVar.e++;
        ::Sleep(1);
    }

}

void test6()
{
    for (int a = 1; a < 20; a++)
    {
        printf("55555555555\n");
        gVar.e++;
        ::Sleep(1000);
    }

}

elfbox::common::ContextPtr gContext = nullptr;
void messageHandler(elfbox::common::detail::MessageData data)
{
    printf("!!!Message: %d \n", (int)data["test"]);
}

void testSend(unsigned id)
{
    elfbox::common::MessageBroadcasterPtr mbp =
            gContext->getComponent<elfbox::common::IMessageBroadcaster>(nullptr);

    for (int i = 0; i<10; i++)
    {
        elfbox::common::detail::MessageData data;
        data["test"] = 12345123;
        mbp->sendMessage(elfbox::common::TEST_MESSAGE, data);
        ::Sleep(700);
    }
}

void appMain()
{
    elfbox::common::ContextPtr context = std::make_shared<elfbox::common::Context>();
    gContext = context;
    context->addComponent(std::make_shared<elfbox::BaseLogger>());
    context->addComponent(std::make_shared<elfbox::common::ElfBoxEngine>(context));

    elfbox::graphics::GraphicsPtr graphics = std::make_shared<elfbox::graphics::Graphics>(
            std::make_shared<elfbox::graphics::detail::GraphicsImpl>(context));
    context->addComponent(graphics);

    elfbox::system::WindowPtr window = std::make_shared<elfbox::system::Window>(
            std::make_shared<elfbox::system::detail::WindowImpl>(context));
    context->addComponent(window);

    elfbox::system::ThreadPoolPtr threadPool = std::make_shared<elfbox::system::ThreadPool>(
            elfbox::system::detail::Thread::getFactory());
    context->addComponent(threadPool);

    elfbox::common::MessageBroadcasterPtr messageBroadcaster =
            std::make_shared<elfbox::common::MessageBroadcaster>(context);
    context->addComponent(messageBroadcaster);

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
    printf("sddddd\n");
}
