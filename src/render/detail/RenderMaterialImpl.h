//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERMATERIALIMPL_H
#define ELFBOX_RENDERMATERIALIMPL_H

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
    RenderMaterialImpl(const std::string fileName);
    virtual ~RenderMaterialImpl() = default;

    bool LoadMaterial();

    bool isLoad()
    {
        return isLoad_;
    };

private:
    std::string fileName_;
    unsigned int materialWidth_;
    unsigned int materialHeight_;
    bool isLoad_;
};
}
}
}
#endif //ELFBOX_RENDERMATERIAL_H
