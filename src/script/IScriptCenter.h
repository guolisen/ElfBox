//
// Created by Lewis on 2017/3/7.
//

#ifndef ELFBOX_ISCRIPTCENTER_H
#define ELFBOX_ISCRIPTCENTER_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IScriptFunction.h"

namespace elfbox
{
namespace script
{
class IScriptCenter : public common::IObject
{
ELF_OBJECT(IScriptCenter, common::IObject);
public:
    virtual ~IScriptCenter() = default;
    virtual bool initialize() = 0;
    virtual bool execute(const std::string &fileName) = 0;
    virtual bool executeString(const std::string &codeStr) = 0;

    virtual ScriptFunctionPtr getFunction(int index) = 0;
    virtual ScriptFunctionPtr getFunction(const std::string &functionName) = 0;
};

typedef std::shared_ptr<IScriptCenter> ScriptCenterPtr;

}
}

#endif //ELFBOX_ISCRIPTCENTER_H
