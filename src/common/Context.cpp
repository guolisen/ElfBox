#include <memory>
#include <common/Context.h>

namespace elfbox
{
    void Context::addComponent(std::shared_ptr<IObject> obj)
    {
        ComponentMapType::iterator iter = componentMap_.find(obj->GetTypeName());
        if (iter != componentMap_.end())
            return;

        componentMap_.insert(std::make_pair(obj->GetTypeName(), obj));
    }
}
