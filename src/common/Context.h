#ifndef common_Context
#define common_Context

#include <functional>
#include <memory>
#include <map>
#include <common/IObject.h>
#include <common/Error.h>

namespace elfbox
{
namespace common
{
class Context : public IObject
{
ELF_OBJECT(Context, IObject);
    typedef std::map<std::string, std::shared_ptr<IObject>> ComponentMapType;
public:
    Context() = default;

    virtual ~Context() = default;

    void addComponent(std::shared_ptr<IObject> obj);
    IObjectPtr getComponent(const std::string& compoentType);

    template<class T>
    std::shared_ptr<T> getComponent(std::function<void(IObjectPtr)> func)
    {
        IObjectPtr object = getComponent(T::GetTypeNameStatic());
        std::shared_ptr<T> targetObject = std::dynamic_pointer_cast<T>(object);
        if (func)
            func(targetObject);

        return targetObject;
    }

    template<class T>
    std::shared_ptr<T> operator[] (const std::string& component)
    {
        IObjectPtr object = getComponent(component);
        std::shared_ptr<T> targetObject = std::dynamic_pointer_cast<T>(object);
        return targetObject;
    }
private:
    ComponentMapType componentMap_;
};

typedef std::shared_ptr<Context> ContextPtr;
}
}
#endif