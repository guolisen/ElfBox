//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_RESOURCEWRAPPER_H
#define ELFBOX_RESOURCEWRAPPER_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IResourceWrapper.h"
#include "../ITimeService.h"

namespace elfbox
{
namespace system
{
namespace detail
{

class ResourceWrapper : public IResourceWrapper
{
ELF_OBJECT(ResourceWrapper, IResourceWrapper);
public:
    ResourceWrapper(common::ContextPtr context,
                    common::IObjectPtr resource);
    virtual ~ResourceWrapper() = default;

    virtual uint32_ getElapsed();
    virtual common::IObjectPtr getObject()
    {
        return resource_;
    }

    static IResourceWrapper::Factory getFactory()
    {
        return [](common::ContextPtr context,
                  common::IObjectPtr resource)
        {
            return std::make_shared<ResourceWrapper>(context, resource);
        }; // NOLINT
    }
private:
    common::ContextPtr context_;
    TimeServicePtr timeService_;
    common::IObjectPtr resource_;
    uint32_ startTick;
};

}
}
}
#endif //ELFBOX_RESOURCEWRAPPER_H
