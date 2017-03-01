#ifndef system_IWindow
#define system_IWindow

#include <string>
#include <common/IObject.h>

namespace elfbox
{
namespace system
{

typedef void* windowHandle;

class IWindow : public common::IObject
{
ELF_OBJECT(IWindow, common::IObject);
public:
    IWindow() = default;
    virtual ~IWindow() = default;

    virtual bool initialize() = 0;
    virtual bool createWindow(const std::string &winName,
                              int width, int height, unsigned int winflag) = 0;
    virtual windowHandle getWindowHandle() const = 0;
    virtual int getWindowWidth() const = 0;
    virtual int getWindowHeight() const = 0;
};

typedef std::shared_ptr<IWindow> WindowPtr;
}
}
#endif
