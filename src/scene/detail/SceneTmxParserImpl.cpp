//
// Created by Lewis on 2017/2/26.
//

#include <sstream>
#include "SceneTmxParserImpl.h"

namespace elfbox
{
namespace scene
{
namespace detail
{
SceneTmxParserImpl::SceneTmxParserImpl(
    common::ContextPtr context, SceneNodeFactoryPtr nodeFactory) :
    context_(context), nodeFactory_(nodeFactory),
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

    sceneInfo_.version = tmxMap_->GetVersion();
    sceneInfo_.orientation = tmxMap_->GetOrientation();
    sceneInfo_.renderOrder = tmxMap_->GetRenderOrder();
    sceneInfo_.width = tmxMap_->GetWidth();
    sceneInfo_.height = tmxMap_->GetHeight();
    sceneInfo_.tileWidth = tmxMap_->GetTileWidth();
    sceneInfo_.tileHeight = tmxMap_->GetTileHeight();
    sceneInfo_.numTileLayers = tmxMap_->GetNumTileLayers();
    sceneInfo_.numObjectGroups = tmxMap_->GetNumObjectGroups();
    sceneInfo_.numTilesets = tmxMap_->GetNumTilesets();

    for (auto i = 0; i < tmxMap_->GetNumTilesets(); ++i)
    {
        tilesetList_.push_back(tmxMap_->GetTileset(i));
    }

    return true;
}

Point2DFloat SceneTmxParserImpl::tilePositionToWorld(int tileX, int tileY)
{
    int tileW = tmxMap_->GetTileWidth();
    int tileH = tmxMap_->GetTileHeight();
    int mapYTile = tmxMap_->GetHeight();
    Point2DFloat point;

    point.x = (tileW / 2) * mapYTile + (tileX - tileY - 1) * (tileW / 2);
    point.y = (tileX + tileY - 1) * (tileH / 2);

    return point;
}

const Tmx::Tileset* SceneTmxParserImpl::getTileSet(int tileGId)
{
    const Tmx::Tileset* result = nullptr;
    for (auto tileSet = tilesetList_.begin();
         tileSet != tilesetList_.end(); ++tileSet)
    {
        int gid = (*tileSet)->GetFirstGid();
        if (tileGId >= (*tileSet)->GetFirstGid())
        {
            result = *tileSet;
        }
        else
        {
            break;
        }
    }

    return result;
}

const Tmx::Image* SceneTmxParserImpl::getTileImage(int tileGId, const Tmx::Tileset* tileSet)
{
    if (tileSet->GetTiles().size() == 0)
    {
        return tileSet->GetImage();
    }

    for (auto tile : tileSet->GetTiles())
    {
        int id = tile->GetId();
        int gid = tileSet->GetFirstGid() + tile->GetId();
        if (gid != tileGId)
            continue;

        return tile->GetImage();
    }
}

SceneNodePtr SceneTmxParserImpl::Parser()
{
    SceneNodePtr rootNode = std::make_shared<SceneNode>(context_, "root", nullptr);
    for (auto i = 0 ; i < sceneInfo_.numTileLayers; ++i)
    {
        const Tmx::TileLayer *tileLayer = tmxMap_->GetTileLayer(i);
        int MapWidth = tileLayer->GetWidth();
        int MapHeight = tileLayer->GetHeight();

        for (int Y = 0; Y < MapWidth; Y++) {
            for (int X = 0; X < MapHeight; X++)
            {
                Point2DFloat worldPosition = tilePositionToWorld(X, Y);
                int tileGId = tileLayer->GetTileGid(X, Y);

                const Tmx::Tileset* tileSet = getTileSet(tileGId);
                const Tmx::Image* tileSetImage = getTileImage(tileGId, tileSet);
                if (!tileSetImage)
                {
                    ELFBOX_LOGERROR(log_, "tileId(%d) doesn't have Image", tileGId);
                    return scene::SceneNodePtr();
                }

                float tilePixelWidth = tileSet->GetTileWidth();
                float tilePixelHeight = tileSet->GetTileHeight();
                float tileImagePixelWidth = tileSetImage->GetWidth();
                int TilesetWidthCount = (int)(tileImagePixelWidth / tilePixelWidth);

                float tileSrcX = ((tileGId - 1) % TilesetWidthCount) * tilePixelWidth;
                float tileSrcY = ((tileGId - 1) / TilesetWidthCount) * tilePixelHeight;

                RectFloat srcRect = { tileSrcX, tileSrcY, tilePixelWidth, tilePixelHeight };
                RectFloat worldtRect = { worldPosition.x, worldPosition.y,
                    tilePixelWidth, tilePixelHeight };

                //tileSet
                std::stringstream ss;
                ss << X << ":" << Y;
                std::string nodeName;
                ss >> nodeName;

                SceneNodePtr tileNode = nodeFactory_->createNode<render::ImageDrawable>(
                    nodeName, tileSetImage->GetSource(), worldtRect, srcRect, 0);

                rootNode->addChild(tileNode);
            }
        }
    }

    for (auto i = 0 ; i < sceneInfo_.numObjectGroups; ++i)
    {
        const Tmx::ObjectGroup *objectGroup = tmxMap_->GetObjectGroup(i);

        for (auto j = 0; j < objectGroup->GetNumObjects(); ++j)
        {
            const Tmx::Object* object = objectGroup->GetObject(j);

            int tileGId = object->GetGid();
            if (tileGId == 0) //polyLine
                continue;
            const Tmx::Tileset* tileSet = getTileSet(tileGId);
            const Tmx::Image* tileSetImage = getTileImage(tileGId, tileSet);
            if (!tileSetImage)
            {
                ELFBOX_LOGERROR(log_, "tileId(%d) doesn't have Image", tileGId);
                return scene::SceneNodePtr();
            }

            float objectWorldX = object->GetX();
            float objectWorldY = object->GetY();
            float objectPixelWidth = object->GetWidth();
            float objectPixelHeight = object->GetHeight();

            RectFloat srcRect = { 0, 0, objectPixelWidth, objectPixelHeight };
            RectFloat worldtRect = { objectWorldX, objectWorldY,
                objectPixelWidth, objectPixelHeight };

            SceneNodePtr tileNode = nodeFactory_->createNode<render::ImageDrawable>(
                object->GetName(), tileSetImage->GetSource(), worldtRect, srcRect, 0);

            rootNode->addChild(tileNode);
        }
    }

    return rootNode;
}

}
}
}