#ifndef Graphics_Graphics
#define Graphics_Graphics

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <graphics/IGraphics.h>

namespace elfbox
{
    class GraphicsImpl;
    class Graphics : public IGraphics
    {
        ELF_OBJECT(Graphics, IGraphics);
    public:
        Graphics(std::shared_ptr<GraphicsImpl> impl);
        virtual ~Graphics() = default;

        virtual bool Initialize();
    private:
        std::shared_ptr<GraphicsImpl> impl_;
    };
}
#endif
