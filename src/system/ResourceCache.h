//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_RESOURCECACHE_H
#define ELFBOX_RESOURCECACHE_H

#include <map>
#include <list>
#include <functional>
#include <common/IObject.h>
#include <common/Context.h>
#include "detail/IResourceWrapper.h"
#include "IResourceCache.h"

namespace elfbox
{
namespace system
{

typedef std::map<std::string, ResourceFactory> ResourceFactoryMap;
typedef std::map<std::string, detail::ResourceWrapperPtr> ResourceDbMap;

namespace detail
{
class ResourceWrapper;
}

class ResourceCache : public IResourceCache
{
ELF_OBJECT(ResourceCache, IResourceCache);
public:
    ResourceCache(common::ContextPtr context,
                  detail::IResourceWrapper::Factory factory);
    virtual ~ResourceCache() = default;

    virtual common::IObjectPtr getResource(const std::string& type,
                                   const std::string& fileName);
    virtual void registerResourceFactory(const std::string& type,
                                 ResourceFactory factory);

    //TODO: Using timer to check memory and release resource
    //TODO: Resource Clone
private:
    common::ContextPtr context_;
    ResourceFactoryMap resourceFactoryMap_;
    ResourceDbMap resourceDbList_;
    detail::IResourceWrapper::Factory factory_;
};
}
}

#endif //ELFBOX_RESOURCECACHE_H
