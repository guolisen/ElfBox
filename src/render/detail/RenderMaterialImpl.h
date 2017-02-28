//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERMATERIALIMPL_H
#define ELFBOX_RENDERMATERIALIMPL_H

#include <string>
#include <common/IObject.h>
#include <common/Context.h>
#include "../IRenderMaterial.h"

namespace elfbox
{
namespace render
{
namespace detail
{
class RenderMaterialImpl : public IRenderMaterial
{
ELF_OBJECT(RenderMaterialImpl, IRenderMaterial);
public:
    RenderMaterialImpl(common::ContextPtr context,
                       const std::string& fileName);
    virtual ~RenderMaterialImpl() = default;

    virtual int getMemorySize()
    {
        return 0;
    };

    virtual bool loadResource();

    virtual bool isLoad()
    {
        return isLoad_;
    };
    virtual bool setFileName(const std::string& fileName);
    virtual std::string& getFileName()
    {
        return fileName_;
    }

    virtual MaterialTextureHandle getMaterial();

    virtual RectFloat getRect()
    {
        return RectFloat(0.0, 0.0, (float)materialWidth_, (float)materialHeight_);
    }

private:
    common::ContextPtr context_;
    std::string fileName_;
    int materialWidth_;
    int materialHeight_;
    bool isLoad_;
    MaterialTextureHandle materialTextureHandle_;
    MaterialSurfaceHandle materialSurfaceHandle_;
};
}
}
}
#endif //ELFBOX_RENDERMATERIAL_H
