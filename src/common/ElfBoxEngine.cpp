#include <common/ElfBoxEngine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>

#include <util/BaseLogger.h>

namespace elfbox
{
    ElfBoxEngine::ElfBoxEngine(ContextPtr context) : context_(context)
    {
        LoggerPtr log = context_->getComponent<ILogger>(nullptr);

        ELFBOX_LOGERROR(log, "Test!!!!");
    }

    ElfBoxEngine::~ElfBoxEngine()
    {
        LoggerPtr log = context_->getComponent<ILogger>(nullptr);
        ELFBOX_LOGERROR(log, "D!!!!");
    }

    bool ElfBoxEngine::Initialize()
    {
        GraphicsPtr graphics = context_->getComponent<IGraphics>(nullptr);
        ELFBOX_ASSERT(graphics);
        graphics->Initialize();

        WindowPtr window = context_->getComponent<IWindow>(nullptr);
        ELFBOX_ASSERT(window);
        window->Initialize();

        window->CreateWindow("Test1", 800, 600, 0);
        return true;
    }

    void ElfBoxEngine::run()
    {
        LoggerPtr log = context_->getComponent<ILogger>(nullptr);

        ELFBOX_LOGERROR(log, "Run!!!!");
    }
}