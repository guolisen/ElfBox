
#include <graphics/IGraphics.h>
#include <system/Window.h>
#include <system/detail/WindowSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace system
{
namespace detail
{
WindowImpl::WindowImpl(common::ContextPtr context) : context_(context),
                                                     log_(context_->getComponent<ILogger>(nullptr))
{
    ELFBOX_LOGERROR(log_, "Test!!!!");
}

bool WindowImpl::initialize()
{
    return true;
}

bool WindowImpl::createWindow(const std::string &winName,
                              int width, int height, unsigned int winflag)
{
    window_ = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr)
    {
        ELFBOX_LOGERROR(log_, "Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }


    SDL_Renderer* rendererHandle = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (rendererHandle == nullptr)
    {
        ELFBOX_LOGERROR(log_, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    graphics::GraphicsPtr graphics =
        context_->getComponent<graphics::IGraphics>(nullptr);
    ELFBOX_ASSERT(graphics);
    graphics->setRendererHandle(rendererHandle);

    return true;
}
}
}
}