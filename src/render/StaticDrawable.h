//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_STATICDRAWABLE_H
#define ELFBOX_STATICDRAWABLE_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include "IDrawable.h"
#include "DrawableData.h"

namespace elfbox
{
namespace render
{

typedef DrawableData<SingleMaterialType,
    WorldRectPositionUint, SourceRectPositionUint> StaticDrawableData;

class StaticDrawable : public IDrawable, StaticDrawableData
{
ELF_OBJECT(StaticDrawable, IDrawable);
public:
    StaticDrawable(common::ContextPtr context):
        context_(context) {}
    virtual ~StaticDrawable() = default;

    virtual void update();
    virtual void render();

private:
    common::ContextPtr context_;
};

}
}

#endif //ELFBOX_RENDERDRAWABLE_H
