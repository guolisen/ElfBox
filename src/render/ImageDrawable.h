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

class ImageDrawable : public IDrawable
{
ELF_OBJECT(ImageDrawable, IDrawable);
public:
    ImageDrawable(common::ContextPtr context):
        data_(context),
        context_(context) {}
    virtual ~ImageDrawable() = default;

    virtual DrawableData<>& getData()
    {
        return data_;
    }
    void setMaterial(RenderMaterialPtr material);

    static IDrawable::Factory getFactory()
    {
        return [](common::ContextPtr context)
        {
            return std::make_shared<ImageDrawable>(context);
        }; // NOLINT
    }
private:
    common::ContextPtr context_;
    DrawableData<> data_;
};

typedef std::shared_ptr<ImageDrawable> StaticDrawablePtr;

}
}

#endif //ELFBOX_RENDERDRAWABLE_H
