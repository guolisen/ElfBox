#ifndef system_IWindow
#define system_IWindow

#include <string>
#include <common/IObject.h>

namespace elfbox
{
namespace system
{
class IWindow : public common::IObject
{
ELF_OBJECT(IWindow, common::IObject);
public:
    IWindow() = default;

    virtual ~IWindow() = default;

    virtual bool Initialize() = 0;

    virtual bool CreateWindow(const std::string &winName,
                              int width, int height, unsigned int winflag) = 0;
};

typedef std::shared_ptr<IWindow> WindowPtr;
}
}
#endif
