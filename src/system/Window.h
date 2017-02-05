#ifndef system_Window
#define system_Window

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <system/IWindow.h>

namespace elfbox
{
    class WindowImpl;
    class Window : public IWindow
    {
        ELF_OBJECT(Window, IWindow);
    public:
        Window(std::shared_ptr<WindowImpl> impl);
        virtual ~Window() = default;

        virtual bool Initialize();
        bool CreateWindow(const std::string& winName,
            int width, int height, unsigned int winflag);
    private:
        std::shared_ptr<WindowImpl> impl_;
    };
}
#endif
