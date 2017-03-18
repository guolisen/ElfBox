//
// Created by Lewis on 2017/2/26.
//

#ifndef ELFBOX_ISCENETMXPARSER_H
#define ELFBOX_ISCENETMXPARSER_H

#include <common/IObject.h>
#include <common/Context.h>
#include "ISceneNode.h"

namespace elfbox
{
namespace scene
{

struct SceneInfo
{
    double version;
    int orientation;
    int renderOrder;
    int width;
    int height;
    int widthPixel;
    int heightPixel;
    int tileWidth;
    int tileHeight;
    int numTileLayers;
    int numObjectGroups;
    int numTilesets;

    SceneInfo(): version(1.0), orientation(0),
                 renderOrder(0), width(0),
                 height(0), tileWidth(0),
                 tileHeight(0), numTileLayers(0),
                 numObjectGroups(0), numTilesets(0) {}
    SceneInfo(const SceneInfo& other)
    {
        version = other.version;
        orientation = other.orientation;
        renderOrder = other.renderOrder;
        width = other.width;
        height = other.height;
        tileWidth = other.tileWidth;
        tileHeight = other.tileHeight;
        numTileLayers = other.numTileLayers;
        numObjectGroups = other.numObjectGroups;
        numTilesets = other.numTilesets;
    }
};

class ISceneTmxParser : public common::IObject
{
ELF_OBJECT(ISceneTmxParser, common::IObject);
public:
    virtual ~ISceneTmxParser() = default;

    virtual bool loadTmxFile(const std::string &fileName) = 0;
    virtual const SceneInfo& getSceneInfo() const = 0;
    virtual SceneNodePtr Parser() = 0;
};

typedef std::shared_ptr<ISceneTmxParser> SceneTmxParserPtr;
}
}

#endif //ELFBOX_SCENETMXPARSER_H
