//
// Created by Lewis on 2017/2/26.
//

#ifndef ELFBOX_SCENETMXPARSER_H
#define ELFBOX_SCENETMXPARSER_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ISceneTmxParser.h"

namespace elfbox
{
namespace scene
{
class SceneTmxParser : public ISceneTmxParser
{
ELF_OBJECT(SceneTmxParser, ISceneTmxParser);
public:
    SceneTmxParser(common::ContextPtr context);
    virtual ~SceneTmxParser() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_SCENETMXPARSER_H
