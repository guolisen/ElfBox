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

system::ResourceFactory RenderMaterial::getFactory()
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
RectFloat RenderMaterial::getRect()
{
    return impl_->getRect();
}

int RenderMaterial::getMemorySize()
{
    return 0;
}

bool RenderMaterial::isTextureLoad()
{
    return impl_->isTextureLoad();
}

bool RenderMaterial::loadToTexture()
{
    return impl_->loadToTexture();
}

bool RenderMaterial::releaseFromTexture()
{
    return impl_->releaseFromTexture();
}

bool RenderMaterial::releaseResource()
{
    return impl_->releaseResource();
}
}
}