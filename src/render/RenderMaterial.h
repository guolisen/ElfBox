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

    virtual bool LoadMaterial();
    virtual bool isLoad();

    static IRenderMaterial::Factory getFactory();
private:

    RenderMaterialPtr impl_;
};
}
}

#endif //ELFBOX_RENDERMATERIAL_H
