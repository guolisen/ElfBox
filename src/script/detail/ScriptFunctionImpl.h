//
// Created by Lewis on 2017/3/8.
//

#ifndef ELFBOX_SCRIPTFUNCTION_H
#define ELFBOX_SCRIPTFUNCTION_H

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <common/IObject.h>
#include <common/Context.h>
#include "../IScriptFunction.h"

namespace elfbox
{
namespace script
{
namespace detail
{
class ScriptFunctionImpl : public IScriptFunction
{
ELF_OBJECT(ScriptFunctionImpl, IScriptFunction);
public:
    ScriptFunctionImpl(lua_State* L, int index);
    virtual ~ScriptFunctionImpl();

    virtual bool isValid() const;
    virtual bool beginCall();
    virtual bool endCall(int numReturns = 0);
    virtual void pushInt(int value);
    virtual void pushBool(bool value);
    virtual void pushFloat(float value);
    virtual void pushDouble(double value);
    virtual void pushString(const std::string& string);
    virtual void pushUserType(void* userType, const char* typeName);

    //void PushVariant(const Variant& variant, const char* asType = 0);
    virtual void pushLuaTable(const std::string& tableName);
    virtual int getFunctionRef() const { return functionRef_; }

private:
    lua_State* luaState_;
    int numArguments_;
    int functionRef_;
};
}
}
}
#endif //ELFBOX_ISCRIPTFUNCTION_H
