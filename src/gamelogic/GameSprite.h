//
// Created by Lewis on 2018/8/29.
//

#ifndef ELFBOX_GAMESPRITE_H
#define ELFBOX_GAMESPRITE_H

#include <common/IObject.h>
#include <common/Context.h>
#include <gamelogic/IGameDirector.h>
#include <gamelogic/IGameSprite.h>
#include <gamelogic/scene/ISceneNode.h>

namespace elfbox
{
namespace gamelogic
{
class GameSprite : public IGameSprite
{
ELF_OBJECT(GameSprite, IGameSprite);
public:
    GameSprite(common::ContextPtr context, scene::SceneNodePtr spriteNode);
    virtual ~GameSprite() = default;

    virtual void move(int processLineId, float X, float Y, float speed) override;
    void moveTo(){};
private:
    common::ContextPtr context_;
    scene::SceneNodePtr spriteNode_;
    GameDirectorPtr gameDirector_;
};
}
}

#endif //ELFBOX_GAMESPRITE_H
