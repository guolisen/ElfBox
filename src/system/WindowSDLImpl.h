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
class WindowImpl : public common::IObject
{
ELF_OBJECT(WindowImpl, common::IObject);
public:
    WindowImpl(common::ContextPtr context);

    virtual ~WindowImpl() = default;

    virtual bool Initialize();

    bool CreateWindow(const std::string &winName,
                      int width, int height, unsigned int winflag);

private:
    common::ContextPtr context_;
    SDL_Window *window_;
    LoggerPtr log_;
};
}
}
#endif
