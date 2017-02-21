#ifndef Graphics_IGraphics
#define Graphics_IGraphics

#include <common/IObject.h>

namespace elfbox
{
namespace graphics
{

typedef void* RendererHandle;

class IGraphics : public common::IObject
{
ELF_OBJECT(IGraphics, common::IObject);
public:
    IGraphics() = default;

    virtual ~IGraphics() = default;

    virtual bool initialize() = 0;
    virtual RendererHandle getRendererHandle() const = 0;
    virtual void setRendererHandle(RendererHandle handle) = 0;
};

typedef std::shared_ptr<IGraphics> GraphicsPtr;
}
}
#endif
