//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDERDRAWABLE_H
#define ELFBOX_RENDERDRAWABLE_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IDrawable.h"
#include "IRenderMaterial.h"
#include "RenderMaterial.h"

namespace elfbox
{
namespace render
{

template <class DrawableType, class DrawableDataType>
class RenderDrawable : public IDrawable, DrawableDataType,
                       std::enable_shared_from_this<RenderDrawable<
                           DrawableType, DrawableDataType>>
{
ELF_OBJECT(RenderDrawable, IDrawable);
public:
    RenderDrawable():
        drawable_(std::make_shared<DrawableType>(this->shared_from_this())) {}
    virtual ~RenderDrawable() = default;

    virtual void update()
    {
        drawable_->update();
    }
    virtual void render()
    {
        drawable_->render();
    }

    virtual std::shared_ptr<DrawableType> advance()
    {
        return drawable_;
    }

private:
    std::shared_ptr<DrawableType> drawable_;
};
}
}

#endif //ELFBOX_RENDERDRAWABLE_H
