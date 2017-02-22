//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_IDRAWABLE_H
#define ELFBOX_IDRAWABLE_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IRenderMaterial.h"
#include "DrawableData.h"

namespace elfbox
{
namespace render
{

class IDrawable : public common::IObject
{
ELF_OBJECT(IDrawable, common::IObject);
public:
    virtual ~IDrawable() = default;

    virtual DrawableData<>& getData() = 0;
};

typedef std::shared_ptr<IDrawable> DrawablePtr;

}
}

#endif //ELFBOX_IDRAWABLE_H
