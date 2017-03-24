//
// Created by Lewis on 2017/2/26.
//

#include <sstream>
#include "SceneTmxParserImpl.h"
#include "../component/AnimationComponent.h"

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
    sceneInfo_.widthPixel = sceneInfo_.width * sceneInfo_.tileWidth;
    sceneInfo_.heightPixel = sceneInfo_.height * sceneInfo_.tileHeight;
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
    Point2DFloat point;
    int tileW = sceneInfo_.tileWidth;
    int tileH = sceneInfo_.tileHeight;

    if (sceneInfo_.orientation == 1)
    {
        point.x = tileX * tileW;
        point.y = tileY * tileH;
    }
    else if (sceneInfo_.orientation == 2)
    {
        int mapYTile = tmxMap_->GetHeight();

        point.x = (tileW / 2) * mapYTile + (tileX - tileY - 1) * (tileW / 2);
        point.y = (tileX + tileY - 1) * (tileH / 2);
    }
    else
    {
        printf("Unknow Map type!\n");
    }

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
        
        if (!tile->GetImage())
            break;

        return tile->GetImage();
    }

    return tileSet->GetImage();
}

SceneNodePtr SceneTmxParserImpl::Parser()
{
    SceneNodePtr rootNode = std::make_shared<SceneNode>(context_, "root", nullptr);
    for (auto i = 0 ; i < sceneInfo_.numTileLayers; ++i)
    {
        const Tmx::TileLayer *tileLayer = tmxMap_->GetTileLayer(i);
        int MapWidth = tileLayer->GetWidth();
        int MapHeight = tileLayer->GetHeight();

        for (int X = 0; X < MapWidth; X++) {
            for (int Y = 0; Y < MapHeight; Y++)
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

                //float tileSrcX = ((tileGId - 1) % TilesetWidthCount) * tilePixelWidth;
                //float tileSrcY = ((tileGId - 1) / TilesetWidthCount) * tilePixelHeight;
                float tileSrcX = 0.0f;
                float tileSrcY = 0.0f;

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
                ELFBOX_LOGERROR(log_, "object tileId(%d) doesn't have Image", tileGId);
                return scene::SceneNodePtr();
            }

            float objectWorldX = object->GetX();
            float objectWorldY = object->GetY() - tileSetImage->GetHeight();
            float objectWorldWidth = object->GetWidth();
            float objectWorldHeight = object->GetHeight();
            float objectPixelWidth = tileSet->GetTileWidth();
            float objectPixelHeight = tileSet->GetTileHeight();

            RectFloat srcRect = { 0, 0, objectPixelWidth, objectPixelHeight };
            RectFloat worldtRect = { objectWorldX, objectWorldY,
                objectWorldWidth, objectWorldHeight };

            SceneNodePtr tileNode = nodeFactory_->createNode<render::ImageDrawable>(
                object->GetName(), tileSetImage->GetSource(), worldtRect, srcRect, 0);

            const Tmx::Tile* tile = isAnimation(tileGId, tileSet);
            if (tile)
            {
                system::ResourceCachePtr cache =
                    context_->getComponent<elfbox::system::IResourceCache>(nullptr);
                render::RenderMaterialPtr material =
                    cache->getResource<render::IRenderMaterial>(tileSetImage->GetSource());
                if (!material)
                {
                    printf("Animation material read error(%s)!\n", tileSetImage->GetSource().c_str());
                    return SceneNodePtr();
                }

                NodeComponentPtr component =
                    std::make_shared<component::AnimationComponent>(
                        material, tile->GetFrames().size(), tileSetImage->GetWidth(),
                        tileSetImage->GetHeight(), objectPixelWidth, objectPixelHeight,
                        100.0f);
                tileNode->addComponent(tileSet->GetName(), component);
            }

            rootNode->addChild(tileNode);
        }
    }

    return rootNode;
}

const Tmx::Tile* SceneTmxParserImpl::isAnimation(int tileGId, const Tmx::Tileset* tileSet)
{
    int tt = tileSet->GetTiles().size();
    for (auto tile : tileSet->GetTiles())
    {
        int id = tile->GetId();
        int gid = tileSet->GetFirstGid() + tile->GetId();
        if (gid != tileGId)
            continue;

        bool ttw = tile->IsAnimated();
        return tile->IsAnimated() ? tile : nullptr;
    }

    return nullptr;
}
}
}
}