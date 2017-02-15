#include <common/ElfBoxEngine.h>
#include <graphics/IGraphics.h>
#include <system/IWindow.h>

#include <util/BaseLogger.h>

namespace elfbox
{
namespace common
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

bool ElfBoxEngine::initialize()
{
    graphics::GraphicsPtr graphics = context_->getComponent<graphics::IGraphics>(nullptr);
    ELFBOX_ASSERT(graphics);
    graphics->initialize();

    system::WindowPtr window = context_->getComponent<system::IWindow>(nullptr);
    ELFBOX_ASSERT(window);
    window->initialize();

    window->createWindow("Test1", 800, 600, 0);
    return true;
}

void ElfBoxEngine::run()
{
    LoggerPtr log = context_->getComponent<ILogger>(nullptr);

    ELFBOX_LOGERROR(log, "run!!!!");
}
}
}