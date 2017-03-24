//
// Created by Lewis on 2017/2/25.
//

#ifndef ELFBOX_ISCENE_H
#define ELFBOX_ISCENE_H

#include <memory>
#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace scene
{
class IScene : public common::IObject
{
ELF_OBJECT(IScene, common::IObject);
public:
    virtual ~IScene() = default;

    virtual bool initialize() = 0;
    virtual void update(float timeStep) = 0;
    virtual bool load(const std::string& fileName) = 0;
    virtual void startToDraw() = 0;
};
typedef std::shared_ptr<IScene> ScenePtr;
}
}

#endif //ELFBOX_SCENE_H
