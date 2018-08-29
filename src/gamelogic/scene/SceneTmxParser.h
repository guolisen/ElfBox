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
     SceneTmxParser(common::ContextPtr context,
                    SceneTmxParserPtr sceneTmxParser):
        context_(context), impl_(sceneTmxParser) {}
    virtual ~SceneTmxParser() = default;

    virtual bool loadTmxFile(const std::string& fileName)
    {
        return impl_->loadTmxFile(fileName);
    }

    virtual const SceneInfo& getSceneInfo() const
    {
        return impl_->getSceneInfo();
    }

    virtual std::list<SceneNodePtr> Parser()
    {
        return impl_->Parser();
    }

private:
    common::ContextPtr context_;
    SceneTmxParserPtr impl_;
};
}
}

#endif //ELFBOX_SCENETMXPARSER_H
