//
// Created by Lewis on 2017/3/3.
//

#ifndef ELFBOX_SCENEFACTORY_H
#define ELFBOX_SCENEFACTORY_H

#include <map>
#include <common/IObject.h>
#include "IObjectFactory.h"

namespace elfbox
{
namespace common
{

typedef std::map<std::string, common::IObjectPtr> FactoryMapType;
class ObjectFactory : public IObjectFactory
{
ELF_OBJECT(ObjectFactory, IObjectFactory);
public:
    virtual ~ObjectFactory() = default;

    virtual common::IObjectPtr getFactory(const std::string& type);
    virtual void registerFactory(
        const std::string& type, common::IObjectPtr factory);

private:
    FactoryMapType factoryMap_;
};
}
}

#endif //ELFBOX_SCENEFACTORY_H
