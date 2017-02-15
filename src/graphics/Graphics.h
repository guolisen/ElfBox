#ifndef Graphics_Graphics
#define Graphics_Graphics

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <graphics/IGraphics.h>

namespace elfbox
{
namespace graphics
{
namespace detail
{
class GraphicsImpl;
}

class Graphics : public IGraphics
{
ELF_OBJECT(Graphics, IGraphics);
public:
    Graphics(std::shared_ptr<detail::GraphicsImpl> impl);

    virtual ~Graphics() = default;

    virtual bool initialize();

private:
    std::shared_ptr<detail::GraphicsImpl> impl_;
};
}
}
#endif
