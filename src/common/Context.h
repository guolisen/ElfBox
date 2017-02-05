#ifndef common_Context
#define common_Context

#include <memory>
#include <map>
#include <common/IObject.h>

namespace elfbox
{
    class Context :public IObject
    {
        ELF_OBJECT(Context, IObject);
        typedef std::map<std::string, std::shared_ptr<IObject>> ComponentMapType;
    public:
        Context() = default;
        virtual ~Context() = default;

        void addComponent(std::shared_ptr<IObject> obj);

        template <class T>
        std::shared_ptr<T> getComponent()
        {
            ComponentMapType::iterator iter = componentMap_.find(T::GetTypeNameStatic());
            if (iter == componentMap_.end())
                return std::shared_ptr<T>();
            return std::dynamic_pointer_cast<T>(iter->second);
        }

    private:
        ComponentMapType componentMap_;
    };

    typedef std::shared_ptr<Context> ContextPtr;
}

#endif