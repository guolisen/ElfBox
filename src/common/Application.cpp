#include <memory>

#include "IApplicationCore.h"
#include <common/Application.h>
#include <common/IElfBoxEngine.h>
#include <common/ElfBoxEngine.h>
#include <common/Context.h>
#include <graphics/IGraphics.h>
#include <graphics/Graphics.h>
#include <graphics/GraphicsSDLImpl.h>
#include <system/IWindow.h>
#include <system/Window.h>
#include <system/WindowSDLImpl.h>
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

    terminat();
}

bool Application::setup()
{
    ELFBOX_LOGDEBUG(log_, "Application::setup() %d %s", 111, "OK");

    elfBoxEngine_->Initialize();

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
void appMain()
{
    elfbox::common::ContextPtr context = std::make_shared<elfbox::common::Context>();

    context->addComponent(std::make_shared<elfbox::BaseLogger>());
    context->addComponent(std::make_shared<elfbox::common::ElfBoxEngine>(context));

    elfbox::graphics::GraphicsPtr graphics = std::make_shared<elfbox::graphics::Graphics>(
            std::make_shared<elfbox::graphics::GraphicsImpl>(context));
    context->addComponent(graphics);

    elfbox::system::WindowPtr window = std::make_shared<elfbox::system::Window>(
            std::make_shared<elfbox::system::WindowImpl>(context));
    context->addComponent(window);

    elfbox::common::Application app(0, context);
    app.run();

    elfbox::system::ThreadPool pool;
    pool.createThreads(3);

    pool.attach(std::bind(&testkk), -1);
    pool.attach(std::bind(&test2), -1);
    pool.attach(std::bind(&elfbox::common::Application::run, &app), -1);
    pool.attach(std::bind(&test3), -1);
    pool.attach(std::bind(&test4), -1);
    pool.attach(std::bind(&test5), -1);

    pool.complete(-1);

    auto item = pool.attach(std::bind(&test6), -1);
    pool.attach(std::bind(&test3), -1);
    pool.attach(std::bind(&test4), -1);
    pool.attach(std::bind(&test5), -1);

    pool.waitForJob(item);
    printf("sddddd\n");
}
