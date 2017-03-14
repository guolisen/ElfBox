//
// Created by Lewis on 2017/3/12.
//
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <tolua++.h>
#include "ScriptUtil.h"

namespace elfbox
{
namespace script
{
namespace detail
{

common::ContextPtr getContext(lua_State* L)
{
    lua_getglobal(L, ".context");
    tolua_Error error;      // Ensure we are indeed getting a Context object before casting
    common::ContextPtr* context = tolua_isusertype(L, -1, "ContextPtr", 0, &error) ?
           static_cast<common::ContextPtr*>(tolua_tousertype(L, -1, 0)) : nullptr;

    return context ? *context : common::ContextPtr();
}

}
}
}