//
// Created by Lewis on 2017/3/8.
//

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <tolua++.h>
#include "ScriptFunctionImpl.h"

namespace elfbox
{
namespace script
{
namespace detail
{
ScriptFunctionImpl::ScriptFunctionImpl(lua_State* L, int index):
    luaState_(L), numArguments_(-1)
{
    lua_pushvalue(L, index);
    functionRef_ = luaL_ref(L, LUA_REGISTRYINDEX);
}

ScriptFunctionImpl::~ScriptFunctionImpl()
{
    luaL_unref(luaState_, LUA_REGISTRYINDEX, functionRef_);
    functionRef_ = LUA_NOREF;
}

bool ScriptFunctionImpl::isValid() const
{
    return functionRef_ != LUA_REFNIL && functionRef_ != LUA_NOREF;
}

bool ScriptFunctionImpl::beginCall()
{
    if (!isValid())
        return false;

    lua_rawgeti(luaState_, LUA_REGISTRYINDEX, functionRef_);
    numArguments_ = 0;

    return true;
}

bool ScriptFunctionImpl::endCall(int numReturns)
{
    int numArguments = numArguments_;
    numArguments_ = -1;

    if (lua_pcall(luaState_, numArguments, numReturns, 0) != 0)
    {
        const char* message = lua_tostring(luaState_, -1);
        printf("Execute Lua function failed: %s", message);
        lua_pop(luaState_, 1);
        return false;
    }

    return true;
}

void ScriptFunctionImpl::pushBool(bool value)
{
    ++numArguments_;
    lua_pushboolean(luaState_, value);
}

void ScriptFunctionImpl::pushInt(int value)
{
    ++numArguments_;
    lua_pushinteger(luaState_, value);
}

void ScriptFunctionImpl::pushFloat(float value)
{
    ++numArguments_;
    lua_pushnumber(luaState_, value);
}

void ScriptFunctionImpl::pushDouble(double value)
{
    ++numArguments_;
    lua_pushnumber(luaState_, value);
}

void ScriptFunctionImpl::pushString(const std::string &string)
{
    ++numArguments_;
    tolua_pushstring(luaState_, string.c_str());
}

void ScriptFunctionImpl::pushUserType(void* userType, const char* typeName)
{
    ++numArguments_;
    tolua_pushusertype(luaState_, userType, typeName);
}

void ScriptFunctionImpl::pushLuaTable(const std::string &tableName)
{
    ++numArguments_;
    lua_getglobal(luaState_, tableName.c_str());
    if (!lua_istable(luaState_, -1))
        printf("Could not find lua table %s", tableName.c_str());
}


}
}
}