#include <memory>
#include <common/Context.h>

namespace elfbox
{
    void Context::addComponent(std::shared_ptr<IObject> obj)
    {
        ComponentMapType::iterator iter = componentMap_.find(obj->GetTypeName());
        if (iter != componentMap_.end())
            return;

        std::string objName = obj->GetTypeName();
        const TypeInfo* baseTypeInfo = obj->GetTypeInfo()->GetBaseTypeInfo();
        if (baseTypeInfo)
            objName = baseTypeInfo->GetTypeName();

        componentMap_.insert(std::make_pair(objName, obj));
    }
}
