//
// Created by Lewis on 2017/2/20.
//

#include "RenderMaterial.h"
#include "detail/RenderMaterialImpl.h"

namespace elfbox
{
namespace render
{

RenderMaterial::RenderMaterial(RenderMaterialPtr renderMaterialImpl):
    impl_(renderMaterialImpl)
{
}

IRenderMaterial::Factory RenderMaterial::getFactory()
{
    return [](const std::string fileName)
    {
        return std::make_shared<RenderMaterial>(
            std::make_shared<detail::RenderMaterialImpl>(fileName));
    };
}

bool RenderMaterial::LoadMaterial()
{
    return impl_->LoadMaterial();
}

bool RenderMaterial::isLoad()
{
    return impl_->isLoad();
}

}
}