#include <graphics/Graphics.h>
#include <graphics/detail/GraphicsSDLImpl.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace graphics
{
Graphics::Graphics(std::shared_ptr<detail::GraphicsImpl> impl) :
        impl_(impl)
{
}

bool Graphics::initialize()
{
    impl_->initialize();
    return true;
}
}
}