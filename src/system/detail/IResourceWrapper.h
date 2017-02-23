//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_IRESOURCEWRAPPER_H
#define ELFBOX_IRESOURCEWRAPPER_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace system
{
namespace detail
{

class IResourceWrapper : public common::IObject
{
ELF_OBJECT(IResourceWrapper, common::IObject);
public:
    typedef std::function<std::shared_ptr<IResourceWrapper>(common::ContextPtr,
        common::IObjectPtr)> Factory;

    virtual ~IResourceWrapper() = default;

    virtual uint32_ getElapsed() = 0;
    virtual common::IObjectPtr getObject() = 0;

};

typedef std::shared_ptr<IResourceWrapper> ResourceWrapperPtr;

}
}
}
#endif //ELFBOX_IRESOURCEWRAPPER_H
