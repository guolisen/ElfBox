#include <system/Window.h>
#include <system/detail/WindowSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace system
{

Window::Window(std::shared_ptr<detail::WindowImpl> impl) :
        impl_(impl)
{
}

bool Window::initialize()
{
    return impl_->initialize();
}

bool Window::createWindow(const std::string &winName,
                          int width, int height, unsigned int winflag)
{
    return impl_->createWindow(winName, width, height, winflag);
}

windowHandle Window::getWindowHandle() const
{
    return impl_->getWindowHandle();
}

int Window::getWindowWidth() const
{
    return impl_->getWindowWidth();
}

int Window::getWindowHeight() const
{
    return impl_->getWindowHeight();
}
}
}