//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_IRENDERMATERIAL_H
#define ELFBOX_IRENDERMATERIAL_H

#include <memory>
#include <string>
#include <common/IObject.h>
#include <common/Context.h>
#include <system/IResource.h>

namespace elfbox
{
namespace render
{

typedef void* MaterialTextureHandle;
typedef void* MaterialSurfaceHandle;

class IRenderMaterial : public system::IResource
{
ELF_OBJECT(IRenderMaterial, common::IObject);
public:
    virtual ~IRenderMaterial() = default;

    virtual MaterialTextureHandle getMaterial() = 0;
    virtual RectInt getRect() = 0;
};

typedef std::shared_ptr<IRenderMaterial> RenderMaterialPtr;

}
}

#endif //ELFBOX_RENDERMATERIAL_H
