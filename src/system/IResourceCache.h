//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_IRESOURCECACHE_H
#define ELFBOX_IRESOURCECACHE_H

#include <list>
#include <functional>
#include <common/IObject.h>
#include <common/Context.h>
#include "detail/IResourceWrapper.h"

namespace elfbox
{
namespace system
{

typedef std::function<common::IObjectPtr(common::ContextPtr,
    const std::string&)> ResourceFactory;

class IResourceCache : public common::IObject
{
ELF_OBJECT(IResourceCache, common::IObject);
public:
    virtual ~IResourceCache() = default;

    virtual common::IObjectPtr getResource(const std::string& type,
                                   const std::string& fileName) = 0;
    virtual void registerResourceFactory(const std::string& type,
                                 ResourceFactory factory) = 0;
};

typedef std::shared_ptr<IResourceCache> ResourceCachePtr;

}
}

#endif //ELFBOX_RESOURCECACHE_H
