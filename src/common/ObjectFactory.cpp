//
// Created by Lewis on 2017/3/3.
//

#include "ObjectFactory.h"

namespace elfbox
{
namespace common
{

common::IObjectPtr ObjectFactory::getFactory(const std::string& type)
{
    auto it = factoryMap_.find(type);
    if (it == factoryMap_.end())
        return common::IObjectPtr();

    return it->second;
}

void ObjectFactory::registerFactory(const std::string &type, common::IObjectPtr factory)
{
    auto it = factoryMap_.find(type);
    if (it != factoryMap_.end())
        return;
    factoryMap_.insert(std::make_pair(type, factory));
}
}
}