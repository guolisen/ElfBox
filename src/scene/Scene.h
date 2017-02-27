//
// Created by Lewis on 2017/2/25.
//

#ifndef ELFBOX_SCENE_H
#define ELFBOX_SCENE_H

#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace scene
{
class Scene : public common::IObject
{
ELF_OBJECT(Scene, common::IObject);
public:
    Scene(common::ContextPtr context);
    virtual ~Scene() = default;

    virtual void update(float timeStep);
    virtual bool load(const std::string& fileName);
private:
    common::ContextPtr context_;
};
}
}

#endif //ELFBOX_SCENE_H
