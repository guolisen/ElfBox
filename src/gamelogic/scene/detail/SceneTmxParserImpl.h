//
// Created by Lewis on 2017/2/26.
//

#ifndef ELFBOX_SCENETMXPARSERIMPL_H
#define ELFBOX_SCENETMXPARSERIMPL_H

#include <list>
#include <vector>
#include <memory>
#include <common/IObject.h>
#include <common/Context.h>
#include <util/BaseLogger.h>
#include <tmxparser/Tmx.h>
#include "../ISceneTmxParser.h"
#include "../ISceneNodeFactory.h"

namespace elfbox
{
namespace scene
{
namespace detail
{

class SceneTmxParserImpl : public ISceneTmxParser
{
ELF_OBJECT(SceneTmxParserImpl, ISceneTmxParser);
public:
    SceneTmxParserImpl(common::ContextPtr context,
                       SceneNodeFactoryPtr nodeFactory);
    virtual ~SceneTmxParserImpl() = default;

    bool loadTmxFile(const std::string &fileName);
    const SceneInfo& getSceneInfo() const
    {
        return sceneInfo_;
    }

    std::list<SceneNodePtr> Parser();

private:
    Point2DFloat tilePositionToWorld(int tileX, int tileY);
    const Tmx::Tileset* getTileSet(int tileGId);
    const Tmx::Tileset* getTileSetByName(const std::string& tileSetName);
    const Tmx::Tile* getTile(int tileGId, const Tmx::Tileset* tileSet);
    const Tmx::Image* getTileImage(int tileGId, const Tmx::Tileset* tileSet);
    bool setAnimation(std::shared_ptr<ISceneNode> node,
                      const Tmx::Image* tileSetImage,
                      float objectPixelWidth, float objectPixelHeight,
                      const Tmx::Tile* tile);
    SceneNodePtr objectProcessor(const std::string& type, const Tmx::Object* object);

    common::ContextPtr context_;
    SceneNodeFactoryPtr nodeFactory_;
    LoggerPtr log_;
    std::shared_ptr<Tmx::Map> tmxMap_;
    SceneInfo sceneInfo_;
    std::vector<const Tmx::Tileset*> tilesetList_;
};
}
}
}
#endif //ELFBOX_SCENETMXPARSERIMPL_H
