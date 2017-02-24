//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_IRESOURCECACHE_H
#define ELFBOX_IRESOURCECACHE_H

#include <memory>
#include <list>
#include <functional>
#include <common/IObject.h>
#include <common/Context.h>
#include "detail/IResourceWrapper.h"
#include "IResource.h"

namespace elfbox
{
namespace system
{

class IResourceCache : public common::IObject
{
ELF_OBJECT(IResourceCache, common::IObject);
public:
    virtual ~IResourceCache() = default;

    virtual common::IObjectPtr getResource(const std::string& type,
                                   const std::string& fileName) = 0;
    virtual void registerResourceFactory(const std::string& type,
                                 ResourceFactory factory) = 0;

    template <class ResType>
    std::shared_ptr<ResType> getResource(const std::string& fileName)
    {
        return std::dynamic_pointer_cast<ResType>(
            getResource(ResType::GetTypeNameStatic(), fileName));
    }

    template <class ResType>
    void registerResourceFactory(ResourceFactory factory)
    {
        registerResourceFactory(ResType::GetTypeNameStatic(), factory);
    }
};

typedef std::shared_ptr<IResourceCache> ResourceCachePtr;



}
}

#endif //ELFBOX_RESOURCECACHE_H
