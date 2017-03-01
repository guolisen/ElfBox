#ifndef system_WindowImpl
#define system_WindowImpl

#include <SDL.h>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace system
{
namespace detail
{
class WindowImpl : public common::IObject
{
ELF_OBJECT(WindowImpl, common::IObject);
public:
    WindowImpl(common::ContextPtr context);

    virtual ~WindowImpl() = default;

    virtual bool initialize();

    virtual bool createWindow(const std::string &winName,
                      int width, int height, unsigned int winflag);
    virtual windowHandle getWindowHandle() const
    {
        return (windowHandle)window_;
    }
    virtual int getWindowWidth() const;
    virtual int getWindowHeight() const;
private:
    common::ContextPtr context_;
    SDL_Window* window_;
    LoggerPtr log_;
    int windowWidth_;
    int windowHeight_;
};
}
}
}
#endif
