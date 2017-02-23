//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_RESOURCECACHE_H
#define ELFBOX_RESOURCECACHE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{

class IResourceCache : public common::IObject
{
ELF_OBJECT(IResourceCache, common::IObject);
public:
    virtual ~IResourceCache() = default;

    template <class T>
    virtual T getResource() = 0;
private:
    common::ContextPtr context_;
};

class ResourceCache : public IResourceCache
{
ELF_OBJECT(ResourceCache, IResourceCache);
public:
    ResourceCache(common::ContextPtr context);
    virtual ~ResourceCache() = default;

    template <class T>
    T getResource();
private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_RESOURCECACHE_H
