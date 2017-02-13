#include <graphics/Graphics.h>
#include <graphics/GraphicsSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace graphics
{
Graphics::Graphics(std::shared_ptr<GraphicsImpl> impl) :
        impl_(impl)
{
}

bool Graphics::Initialize()
{
    impl_->Initialize();
    return true;
}
}
}