//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_IRENDERMATERIAL_H
#define ELFBOX_IRENDERMATERIAL_H

#include <memory>
#include <string>
#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace render
{

typedef void* MaterialTextureHandle;
typedef void* MaterialSurfaceHandle;

class IRenderMaterial : public common::IObject
{
ELF_OBJECT(IRenderMaterial, common::IObject);
    typedef std::function<std::shared_ptr<IRenderMaterial>(common::ContextPtr,
        const std::string&)> Factory;
public:
    virtual ~IRenderMaterial() = default;

    virtual bool loadMaterial() = 0;
    virtual bool isLoad() = 0;
    virtual bool setFileName(const std::string& fileName) = 0;
    virtual MaterialTextureHandle getMaterial() = 0;
    virtual RectInt getRect() = 0;
};

typedef std::shared_ptr<IRenderMaterial> RenderMaterialPtr;

}
}

#endif //ELFBOX_RENDERMATERIAL_H
