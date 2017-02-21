#ifndef Graphics_GraphicsImpl
#define Graphics_GraphicsImpl

#include <SDL.h>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace graphics
{
namespace detail
{

class GraphicsImpl : public common::IObject
{
ELF_OBJECT(GraphicsImpl, common::IObject);
public:
    GraphicsImpl(common::ContextPtr context);

    virtual ~GraphicsImpl() = default;

    virtual bool initialize();
    virtual RendererHandle getRendererHandle() const
    {
        return rendererHandle_;
    }
    virtual void setRendererHandle(RendererHandle handle)
    {
        rendererHandle_ = handle;
    }
private:
    common::ContextPtr context_;
    RendererHandle rendererHandle_;
    LoggerPtr log_;
};
}
}
}
#endif
