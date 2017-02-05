#include <system/Window.h>
#include <system/WindowSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
    Window::Window(std::shared_ptr<WindowImpl> impl) :
        impl_(impl)
    {
    }

    bool Window::Initialize()
    {
        return impl_->Initialize();
    }

    bool Window::CreateWindow(const std::string& winName,
        int width, int height, unsigned int winflag)
    {
        return impl_->CreateWindow(winName, width, height, winflag);
    }
}