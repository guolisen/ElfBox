//
// Created by Lewis on 2017/3/7.
//

#ifndef ELFBOX_SCRIPTCENTER_H
#define ELFBOX_SCRIPTCENTER_H

#include <common/IObject.h>
#include <common/Context.h>
#include "IScriptCenter.h"
#include "IScriptFunction.h"

namespace elfbox
{
namespace script
{
class ScriptCenter : public IScriptCenter
{
ELF_OBJECT(ScriptCenter, IScriptCenter);
public:
    ScriptCenter(common::ContextPtr context,
                 ScriptCenterPtr impl) :
        context_(context), impl_(impl) {}
    virtual ~ScriptCenter() = default;

    virtual bool initialize()
    {
        return impl_->initialize();
    }

    virtual bool execute(const std::string &fileName)
    {
        return impl_->execute(fileName);
    }

    virtual bool executeString(const std::string &codeStr)
    {
        return impl_->executeString(codeStr);
    }

    virtual ScriptFunctionPtr getFunction(int index)
    {
        return impl_->getFunction(index);
    }

    virtual ScriptFunctionPtr getFunction(const std::string &functionName)
    {
        return impl_->getFunction(functionName);
    }

private:
    common::ContextPtr context_;
    ScriptCenterPtr impl_;
};
}
}

#endif //ELFBOX_SCRIPTCENTER_H
