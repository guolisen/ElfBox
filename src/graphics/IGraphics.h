#ifndef Graphics_IGraphics
#define Graphics_IGraphics

#include <common/IObject.h>

namespace elfbox
{
namespace graphics
{

class IGraphics : public common::IObject
{
ELF_OBJECT(IGraphics, common::IObject);
public:
    IGraphics() = default;

    virtual ~IGraphics() = default;

    virtual bool Initialize() = 0;
};

typedef std::shared_ptr<IGraphics> GraphicsPtr;
}
}
#endif
