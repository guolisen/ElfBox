#ifndef Graphics_GraphicsImpl
#define Graphics_GraphicsImpl

#include <SDL.h>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>

namespace elfbox
{
    class GraphicsImpl : public IObject
    {
        ELF_OBJECT(GraphicsImpl, IObject);
    public:
        GraphicsImpl(ContextPtr context);
        virtual ~GraphicsImpl() = default;

        virtual bool Initialize();
    private:
        ContextPtr context_;
        LoggerPtr log_;
    };
}
#endif
