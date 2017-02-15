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

private:
    common::ContextPtr context_;
    LoggerPtr log_;
};
}
}
}
#endif
