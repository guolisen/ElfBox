//
// Created by Lewis on 2017/3/8.
//

#ifndef ELFBOX_ISCRIPTFUNCTION_H
#define ELFBOX_ISCRIPTFUNCTION_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace script
{
class IScriptFunction : public common::IObject
{
ELF_OBJECT(IScriptFunction, common::IObject);
public:
    virtual ~IScriptFunction() = default;

    virtual bool isValid() const = 0;
    virtual bool beginCall() = 0;
    virtual bool endCall(int numReturns = 0) = 0;
    virtual void pushInt(int value) = 0;
    virtual void pushBool(bool value) = 0;
    virtual void pushFloat(float value) = 0;
    virtual void pushDouble(double value) = 0;
    virtual void pushString(const std::string& string) = 0;
    virtual void pushUserType(void* userType, const char* typeName) = 0;

    template <typename T> void pushUserType(const T* userType)
    {
        pushUserType((void*)userType, T::GetTypeName().CString());
    }

    template <typename T> void pushUserType(const T& userType)
    {
        pushUserType((void*)&userType, T::GetTypeName().CString());
    }

    template <typename T> void pushUserType(const T* userType, const char* typeName)
    {
        pushUserType((void*)userType, typeName);
    }

    template <typename T> void pushUserType(const T& userType, const char* typeName)
    {
        pushUserType((void*)&userType, typeName);
    }

    //void PushVariant(const Variant& variant, const char* asType = 0);
    virtual void pushLuaTable(const std::string& tableName) = 0;
    virtual int getFunctionRef() const = 0;
};

typedef std::shared_ptr<IScriptFunction> ScriptFunctionPtr;

}
}

#endif //ELFBOX_ISCRIPTFUNCTION_H
