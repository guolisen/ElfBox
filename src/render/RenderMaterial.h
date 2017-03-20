//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERMATERIAL_H
#define ELFBOX_RENDERMATERIAL_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include "IRenderMaterial.h"

namespace elfbox
{
namespace render
{

class RenderMaterial : public IRenderMaterial
{
ELF_OBJECT(RenderMaterial, IRenderMaterial);
public:
    RenderMaterial(RenderMaterialPtr renderMaterialImpl);
    virtual ~RenderMaterial() = default;

    virtual bool loadResource();
    virtual bool releaseResource();
    virtual int getMemorySize();
    virtual bool isLoad();
    virtual bool setFileName(const std::string& fileName);
    virtual std::string& getFileName()
    {
        return impl_->getFileName();
    }

    virtual MaterialTextureHandle getMaterial();
    virtual RectFloat getRect();

    virtual bool isTextureLoad();
    virtual bool loadToTexture();
    virtual bool releaseFromTexture();

    static system::ResourceFactory getFactory();
private:

    RenderMaterialPtr impl_;
};
}
}

#endif //ELFBOX_RENDERMATERIAL_H
