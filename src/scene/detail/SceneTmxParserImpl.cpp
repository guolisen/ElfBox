//
// Created by Lewis on 2017/2/26.
//

#include "SceneTmxParserImpl.h"

namespace elfbox
{
namespace scene
{
namespace detail
{
SceneTmxParserImpl::SceneTmxParserImpl(common::ContextPtr context) : context_(context),
                                                                     log_(context_->getComponent<ILogger>(nullptr)),
                                                                     tmxMap_(std::make_shared<Tmx::Map>())
{
}

bool SceneTmxParserImpl::loadTmxFile(const std::string &fileName)
{
    tmxMap_->ParseFile(fileName);
    if (tmxMap_->HasError())
    {
        ELFBOX_LOGERROR(log_, "Scene Tmx Parse error code: %d", tmxMap_->GetErrorCode());
        ELFBOX_LOGERROR(log_, "Scene Tmx Parse error text: %s", tmxMap_->GetErrorText().c_str());

        return false;
    }

    return true;
}
}
}
}