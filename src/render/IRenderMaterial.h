//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_IRENDERMATERIAL_H
#define ELFBOX_IRENDERMATERIAL_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace render
{

class IRenderMaterial : public common::IObject
{
ELF_OBJECT(IRenderMaterial, common::IObject);
    typedef std::function<std::shared_ptr<IRenderMaterial>(
        const std::string fileName)> Factory;
public:
    virtual ~IRenderMaterial() = default;

    virtual bool LoadMaterial() = 0;
    virtual bool isLoad() = 0;
};

typedef std::shared_ptr<IRenderMaterial> RenderMaterialPtr;

}
}

#endif //ELFBOX_RENDERMATERIAL_H
