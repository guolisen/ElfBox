//
// Created by Lewis on 2017/2/20.
//

#ifndef ELFBOX_RENDER_H
#define ELFBOX_RENDER_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class Render : public common::IObject
{
ELF_OBJECT(Render, common::IObject);
public:
    Render(common::ContextPtr context);
    virtual ~Render() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_RENDER_H
