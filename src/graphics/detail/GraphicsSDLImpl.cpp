#include <SDL.h>
#include <SDL_image.h>

#include <util/BaseLogger.h>
#include <graphics/Graphics.h>
#include <graphics/detail/GraphicsSDLImpl.h>
#include <system/Window.h>

namespace elfbox
{
namespace graphics
{
namespace detail
{
GraphicsImpl::GraphicsImpl(common::ContextPtr context) :
        context_(context), rendererHandle_(nullptr),
        log_(context_->getComponent<ILogger>(nullptr))
{
    ELFBOX_LOGERROR(log_, "Test!!!!");
}

bool GraphicsImpl::initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        ELFBOX_LOGERROR(log_, "SDL_Init return %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        ELFBOX_LOGWARNING(log_, "Warning: Linear texture filtering not enabled!");
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        ELFBOX_LOGERROR(log_, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}
}
}
}