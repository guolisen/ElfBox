//
// Created by Lewis on 2017/2/23.
//
#include "detail/ResourceWrapper.h"
#include "ResourceCache.h"

namespace elfbox
{
namespace system
{

ResourceCache::ResourceCache(common::ContextPtr context,
                             detail::IResourceWrapper::Factory factory):
    context_(context), factory_(factory)
{
}

common::IObjectPtr ResourceCache::getResource(
    const std::string &type, const std::string& fileName)
{
    auto existResourceIt = resourceDbList_.find(fileName);
    if (existResourceIt != resourceDbList_.end())
        return existResourceIt->second->getObject();

    auto it = resourceFactoryMap_.find(type);
    if (it == resourceFactoryMap_.end())
        return common::IObjectPtr();

    common::IObjectPtr resourceObject = it->second(context_, fileName);
    resourceDbList_.insert(std::make_pair(
        fileName, factory_(context_, resourceObject)));

    return resourceObject;
}

void ResourceCache::registerResourceFactory(
    const std::string &type, ResourceFactory factory)
{
    auto it = resourceFactoryMap_.find(type);
    if (it == resourceFactoryMap_.end())
        return;

    resourceFactoryMap_.insert(std::make_pair(type, factory));
}
}
}