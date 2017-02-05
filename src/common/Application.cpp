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

namespace elfbox
{
    Application::Application(
        std::shared_ptr<IApplicationCore> applicationCore,
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

void appMain()
{
    elfbox::ContextPtr context = std::make_shared<elfbox::Context>();
    
    context->addComponent(std::make_shared<elfbox::BaseLogger>());
    context->addComponent(std::make_shared<elfbox::ElfBoxEngine>(context));

    elfbox::GraphicsPtr graphics = std::make_shared<elfbox::Graphics>(
        std::make_shared<elfbox::GraphicsImpl>(context));
    context->addComponent(graphics);

    elfbox::WindowPtr window = std::make_shared<elfbox::Window>(
        std::make_shared<elfbox::WindowImpl>(context));
    context->addComponent(window);

    elfbox::Application app(0, context);
    app.run();
}