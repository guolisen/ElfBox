#ifndef system_Window
#define system_Window

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <system/IWindow.h>

namespace elfbox
{
namespace system
{
namespace detail
{
class WindowImpl;
}
class Window : public IWindow
{
ELF_OBJECT(Window, IWindow);
public:
    Window(std::shared_ptr<detail::WindowImpl> impl);

    virtual ~Window() = default;

    virtual bool initialize();

    virtual bool createWindow(const std::string &winName,
                      int width, int height, unsigned int winflag);
    virtual windowHandle getWindowHandle() const;
private:
    std::shared_ptr<detail::WindowImpl> impl_;
};
}
}
#endif
