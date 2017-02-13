#include <system/Window.h>
#include <system/WindowSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace system
{
WindowImpl::WindowImpl(common::ContextPtr context) : context_(context),
                                                     log_(context_->getComponent<ILogger>(nullptr))
{
    ELFBOX_LOGERROR(log_, "Test!!!!");
}

bool WindowImpl::Initialize()
{
    return true;
}

bool WindowImpl::CreateWindow(const std::string &winName,
                              int width, int height, unsigned int winflag)
{
    window_ = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr)
    {
        ELFBOX_LOGERROR(log_, "Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
}
}