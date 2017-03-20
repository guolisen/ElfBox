//
// Created by Lewis on 2017/2/23.
//

#ifndef ELFBOX_IRESOURCE_H
#define ELFBOX_IRESOURCE_H

#include <memory>
#include <common/IObject.h>

namespace elfbox
{
namespace system
{

class IResource : public common::IObject
{
ELF_OBJECT(IResource, common::IObject);
public:
    virtual ~IResource() = default;

    virtual bool loadResource() = 0;
    virtual bool releaseResource() = 0;
    virtual int getMemorySize() = 0;
    virtual bool isLoad() = 0;
    virtual bool setFileName(const std::string& fileName) = 0;
    virtual std::string& getFileName() = 0;
};

typedef std::shared_ptr<IResource> ResourcePtr;
typedef std::function<ResourcePtr(common::ContextPtr,
                                  const std::string&)> ResourceFactory;

}
}

#endif //ELFBOX_IRESOURCE_H
