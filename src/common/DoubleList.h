//
// Created by Lewis on 2018/8/1.
//

#ifndef ELFBOX_DOUBLELIST_H
#define ELFBOX_DOUBLELIST_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class DoubleList : public common::IObject
{
ELF_OBJECT(DoubleList, common::IObject);
public:
    DoubleList() = default;
    virtual ~DoubleList() = default;

private:

};
}
}

#endif //ELFBOX_DOUBLELIST_H
