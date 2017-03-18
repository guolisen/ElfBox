//
// Created by Lewis on 2017/3/15.
//

#ifndef ELFBOX_KEYCOMPONENT_H
#define ELFBOX_KEYCOMPONENT_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class KeyComponent : public common::IObject
{
ELF_OBJECT(KeyComponent, common::IObject);
public:
    KeyComponent(common::ContextPtr context);
    virtual ~KeyComponent() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_KEYCOMPONENT_H
