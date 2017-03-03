//
// Created by Lewis on 2017/3/3.
//

#ifndef ELFBOX_ISCENEFACTORY_H
#define ELFBOX_ISCENEFACTORY_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace common
{
class IFactory : public common::IObject
{
ELF_OBJECT(IFactory, common::IObject);
public:
    virtual ~IFactory() = default;

    virtual common::IObjectPtr createObject(common::ContextPtr contextParam) = 0;
};

typedef std::shared_ptr<IFactory> FactoryPtr;

class IObjectFactory : public common::IObject
{
ELF_OBJECT(IObjectFactory, common::IObject);
public:
    virtual ~IObjectFactory() = default;

    virtual common::IObjectPtr getFactory(const std::string& type) = 0;
    virtual void registerFactory(const std::string& type,
                                 common::IObjectPtr factory) = 0;

    template <class ObjectType>
    common::IObjectPtr getFactory()
    {
        return getFactory(ObjectType::GetTypeNameStatic());
    }

    template <class ObjectType>
    void registerFactory(common::IObjectPtr factory)
    {
        registerFactory(ObjectType::GetTypeNameStatic(), factory);
    }

    template <class ObjectType>
    std::shared_ptr<ObjectType> createObject(common::ContextPtr contextParam)
    {
        elfbox::common::IObjectPtr factoryObject = getFactory<ObjectType>();
        elfbox::common::FactoryPtr factory = std::dynamic_pointer_cast<elfbox::common::IFactory>(factoryObject);
        if (factory)
        {
            return std::dynamic_pointer_cast<ObjectType>(
                factory->createObject(contextParam));
        }

        return std::shared_ptr<ObjectType>();
    }

};
typedef std::shared_ptr<IObjectFactory> ObjectFactoryPtr;

template <class ObjectType>
class ObjectFactoryWrapper: public IFactory
{
ELF_OBJECT(ObjectFactoryWrapper, IFactory);
public:
    virtual common::IObjectPtr createObject(common::ContextPtr contextParam)
    {
        return std::make_shared<ObjectType>(contextParam);
    }
};

}
}

#endif //ELFBOX_SCENEFACTORY_H
