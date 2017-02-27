//
// Created by Lewis on 2017/2/26.
//

#ifndef ELFBOX_SCENETMXPARSERIMPL_H
#define ELFBOX_SCENETMXPARSERIMPL_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>
#include <tmxparser/Tmx.h>
#include "../ISceneNodeFactory.h"

namespace elfbox
{
namespace scene
{
namespace detail
{

class SceneTmxParserImpl : public common::IObject
{
ELF_OBJECT(SceneTmxParserImpl, common::IObject);
public:
    SceneTmxParserImpl(common::ContextPtr context);
    virtual ~SceneTmxParserImpl() = default;

    bool loadTmxFile(const std::string &fileName);

private:
    //bool buildScene();

    common::ContextPtr context_;
    LoggerPtr log_;
    std::shared_ptr<Tmx::Map> tmxMap_;
};
}
}
}
#endif //ELFBOX_SCENETMXPARSERIMPL_H
