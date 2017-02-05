#ifndef system_WindowImpl
#define system_WindowImpl

#include <SDL.h>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>

namespace elfbox
{
    class WindowImpl : public IObject
    {
        ELF_OBJECT(WindowImpl, IObject);
    public:
        WindowImpl(ContextPtr context);
        virtual ~WindowImpl() = default;

        virtual bool Initialize();
        bool CreateWindow(const std::string& winName,
            int width, int height, unsigned int winflag);
    private:
        ContextPtr context_;
        SDL_Window* window_;
        LoggerPtr log_;
    };
}
#endif
