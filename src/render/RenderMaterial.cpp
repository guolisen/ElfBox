//
// Created by Lewis on 2017/2/20.
//
#include <memory>
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
    return [](common::ContextPtr context, const std::string& fileName)
    {
        return std::make_shared<RenderMaterial>(
            std::make_shared<detail::RenderMaterialImpl>(context, fileName));
    };
}

bool RenderMaterial::loadResource()
{
    return impl_->loadResource();
}

bool RenderMaterial::isLoad()
{
    return impl_->isLoad();
}

bool RenderMaterial::setFileName(const std::string& fileName)
{
    return impl_->setFileName(fileName);
}

MaterialTextureHandle RenderMaterial::getMaterial()
{
    return impl_->getMaterial();
}
RectInt RenderMaterial::getRect()
{
    return impl_->getRect();
}
}
}