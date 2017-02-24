//
// Created by Lewis on 2017/2/24.
//

#ifndef ELFBOX_SCENENODE_H
#define ELFBOX_SCENENODE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace
{
class SceneNode : public common::IObject
{
ELF_OBJECT(SceneNode, common::IObject);
public:
    SceneNode(common::ContextPtr context);
    virtual ~SceneNode() = default;

private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_SCENENODE_H
