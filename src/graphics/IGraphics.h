#ifndef Graphics_IGraphics
#define Graphics_IGraphics

#include <common/IObject.h>

namespace elfbox
{
    class IGraphics : public IObject
    {
        ELF_OBJECT(IGraphics, IObject);
    public:
        IGraphics() = default;
        virtual ~IGraphics() = default;

        virtual bool Initialize() = 0;
    };

    typedef std::shared_ptr<IGraphics> GraphicsPtr;
}
#endif
