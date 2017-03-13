//
// Created by Lewis on 2017/3/7.
//

#ifndef ELFBOX_SCRIPTCENTERIMPL_H
#define ELFBOX_SCRIPTCENTERIMPL_H

#include <vector>
#include <string>
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <common/IObject.h>
#include <common/Context.h>
#include "../IScriptFunction.h"
#include "../IScriptCenter.h"

namespace elfbox
{
namespace script
{
namespace detail
{
class ScriptCenterImpl : public IScriptCenter
{
ELF_OBJECT(ScriptCenterImpl, IScriptCenter);
public:
    ScriptCenterImpl(common::ContextPtr context);
    virtual ~ScriptCenterImpl() = default;

    virtual bool initialize();

    virtual bool execute(const std::string &fileName);
    virtual bool executeString(const std::string &codeStr);

    virtual ScriptFunctionPtr getFunction(int index);
    virtual ScriptFunctionPtr getFunction(const std::string &functionName);

private:
    void setContext();
    bool findLuaFunction(const std::string &fileName);
    std::vector<std::string> stringSplit(const std::string& str, const std::string& flag);

    common::ContextPtr context_;
    lua_State* luaState_;
};

}

}
}

#endif //ELFBOX_SCRIPTCENTERIMPL_H
