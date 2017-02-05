#ifndef common_IObject
#define common_IObject

#include <memory>
#include <string>

#define ELFBOX_API 

namespace elfbox
{
    class ELFBOX_API TypeInfo
    {
    public:
        TypeInfo(const std::string& typeName, const TypeInfo* baseTypeInfo) :
            typeName_(typeName),
            baseTypeInfo_(baseTypeInfo) {}

        ~TypeInfo() = default;

        bool IsTypeOf(const TypeInfo* typeInfo) const
        {
            const TypeInfo* current = this;
            while (current)
            {
                if (current == typeInfo)
                    return true;

                current = current->GetBaseTypeInfo();
            }

            return false;
        }

        template<typename T> 
        bool IsTypeOf() const 
        {
            return IsTypeOf(T::GetTypeInfoStatic());
        }

        const std::string& GetTypeName() const 
        {
            return typeName_;
        }
        const TypeInfo* GetBaseTypeInfo() const 
        {
            return baseTypeInfo_;
        }

    private:
        std::string typeName_;
        const TypeInfo* baseTypeInfo_;
    };

#define ELF_OBJECT(typeName, baseTypeName) \
    public: \
        typedef typeName ClassName; \
        typedef baseTypeName BaseClassName; \
        virtual const std::string& GetTypeName() const { return GetTypeInfoStatic()->GetTypeName(); } \
        virtual const TypeInfo* GetTypeInfo() const { return GetTypeInfoStatic(); } \
        static const std::string& GetTypeNameStatic() { return GetTypeInfoStatic()->GetTypeName(); } \
        static const TypeInfo* GetTypeInfoStatic() { static const TypeInfo typeInfoStatic(#typeName, BaseClassName::GetTypeInfoStatic()); return &typeInfoStatic; } \

    class ELFBOX_API IObject
    {
    public:
        IObject() = default;
        virtual ~IObject() = default;

        virtual const std::string& GetTypeName() const = 0;
        virtual const TypeInfo* GetTypeInfo() const = 0;

        static const TypeInfo* GetTypeInfoStatic() { return 0; }
        static bool IsTypeOf(const TypeInfo* typeInfo)
        {
            return GetTypeInfoStatic()->IsTypeOf(typeInfo);
        }

        template<typename T> 
        static bool IsTypeOf() 
        {
            return IsTypeOf(T::GetTypeInfoStatic()); 
        }
    };

    typedef std::shared_ptr<IObject> IObjectPtr;
}
#endif