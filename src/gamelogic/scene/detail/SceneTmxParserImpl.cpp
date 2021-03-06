//
// Created by Lewis on 2017/2/26.
//

#include <sstream>
#include "SceneTmxParserImpl.h"
#include "gamelogic/scene/NodeAnimation.h"
#include <gamelogic/IGameManager.h>
#include <gamelogic/GameSprite.h>

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

	int tilessetNum = tmxMap_->GetNumTilesets();
    for (auto i = 0; i < tilessetNum; ++i)
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
        point.x = (float)(tileX * tileW);
        point.y = (float)(tileY * tileH);
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
    for (auto tileSet : tilesetList_)
    {
        int gid = tileSet->GetFirstGid();
        if (tileGId >= tileSet->GetFirstGid())
        {
            result = tileSet;
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

    auto tiles = tileSet->GetTiles();
    for (auto tile : tiles)
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

std::list<SceneNodePtr> SceneTmxParserImpl::Parser()
{
    std::list<SceneNodePtr> layerList;

    for (auto i = 0 ; i < sceneInfo_.numTileLayers; ++i)
    {
        const Tmx::TileLayer *tileLayer = tmxMap_->GetTileLayer(i);
        std::string layerName = tileLayer->GetName();
        int MapWidth = tileLayer->GetWidth();
        int MapHeight = tileLayer->GetHeight();

        SceneNodePtr layer = std::make_shared<SceneNode>(context_, layerName, nullptr);
        for (int X = 0; X < MapWidth; X++)
        {
            for (int Y = 0; Y < MapHeight; Y++)
            {
                Point2DFloat worldPosition = tilePositionToWorld(X, Y);
                int tileGId = tileLayer->GetTileGid(X, Y);
                int tileId = tileLayer->GetTileId(X, Y);

                if (0 == tileGId) //transparent continue
                    continue;

                const Tmx::Tileset* tileSet = getTileSet(tileGId);
                const Tmx::Image* tileSetImage = getTileImage(tileGId, tileSet);
                if (!tileSetImage)
                {
                    ELFBOX_LOGERROR(log_, "tileId(%d) doesn't have Image", tileGId);
                    return std::list<scene::SceneNodePtr>();
                }

                float tilePixelWidth = tileSet->GetTileWidth();
                float tilePixelHeight = tileSet->GetTileHeight();
                float tileImagePixelWidth = tileSetImage->GetWidth();
                int TilesetWidthCount = (int)(tileImagePixelWidth / tilePixelWidth);

                float tileSrcX = (tileId % TilesetWidthCount) * tilePixelWidth;
                float tileSrcY = (tileId / TilesetWidthCount) * tilePixelHeight;

                RectFloat srcRect = { tileSrcX, tileSrcY, tilePixelWidth, tilePixelHeight };
                RectFloat worldtRect = { worldPosition.x, worldPosition.y,
                    tilePixelWidth, tilePixelHeight };

                //tileSet
                std::stringstream ss;
                ss << X << ":" << Y;
                std::string nodeName;
                ss >> nodeName;

                SceneNodePtr tileNode = nodeFactory_->createNode<render::ImageDrawable>(
                    nodeName, tileSetImage->GetSource(), worldtRect, srcRect, i);

                const Tmx::Tile* tile = getTile(tileGId, tileSet);
                if (tile && tile->IsAnimated())
                    setAnimation(tileNode, tileSetImage,
                                 tileSet->GetTileWidth(),
                                 tileSet->GetTileHeight(),
                                 tileSet);
                layer->addChild(tileNode);
            }
        }
        layerList.push_back(layer);
    }

	SceneNodePtr objectLayer = std::make_shared<SceneNode>(context_, "ObjectLayer", nullptr);
    for (auto i = 0 ; i < sceneInfo_.numObjectGroups; ++i)
    {
        const Tmx::ObjectGroup *objectGroup = tmxMap_->GetObjectGroup(i);

        for (auto j = 0; j < objectGroup->GetNumObjects(); ++j)
        {
            const Tmx::Object* object = objectGroup->GetObject(j);

            //int tileGId = object->GetGid();
            //if (tileGId == 0) //polyLine
            //    continue;

            auto objPropertiesMap = object->GetProperties().GetList();
            SceneNodePtr tileNode = objectProcessor(objPropertiesMap["Type"], object);

			if (tileNode)
				objectLayer->addChild(tileNode);
        }
    }
	layerList.push_back(objectLayer);

    return layerList;
}

bool SceneTmxParserImpl::setAnimation(std::shared_ptr<ISceneNode> node,
                                      const Tmx::Image* tileSetImage,
                                      float objectPixelWidth, float objectPixelHeight,
                                      const Tmx::Tileset* tileSet)
{

    system::ResourceCachePtr cache =
        context_->getComponent<elfbox::system::IResourceCache>(nullptr);
    render::RenderMaterialPtr material =
        cache->getResource<render::IRenderMaterial>(tileSetImage->GetSource());
    if (!material)
    {
        printf("Animation material read error(%s)!\n", tileSetImage->GetSource().c_str());
        return false;
    }

    auto animationSet = tileSet->GetTiles();
    for(auto tile : animationSet)
    {
        auto propMap = tile->GetProperties().GetList();
        std::vector<RectFloat> frameVec;
        const std::vector<Tmx::AnimationFrame> &frames =
            tile->GetFrames();
        for (auto frame : frames)
        {
            int tileId = frame.GetTileID();

            float tilePixelWidth = tileSet->GetTileWidth();
            float tilePixelHeight = tileSet->GetTileHeight();
            float tileImagePixelWidth = tileSetImage->GetWidth();
            int TilesetWidthCount = (int)(tileImagePixelWidth / tilePixelWidth);

            float tileSrcX = (tileId % TilesetWidthCount) * tilePixelWidth;
            float tileSrcY = (tileId / TilesetWidthCount) * tilePixelHeight;

            frameVec.push_back(RectFloat(tileSrcX, tileSrcY, tilePixelWidth, tilePixelHeight));
        }

        AnimationPtr animation =
            std::make_shared<animation::NodeAnimation>(
                material, std::move(frameVec), tile->GetFrames().size(),
                tileSetImage->GetWidth(), tileSetImage->GetHeight(),
                objectPixelWidth, objectPixelHeight,
                100.0f);

        auto activateValue = propMap["Activate"];
        if (activateValue == "true")
        {
            animation->setActivate(true);
        }
        node->addAnimation(propMap["AnimationName"], animation);
    }

    return true;
}

const Tmx::Tile* SceneTmxParserImpl::getTile(int tileGId, const Tmx::Tileset* tileSet)
{
    auto tiles = tileSet->GetTiles();
    for (auto tile : tiles)
    {
        int id = tile->GetId();
        int gid = tileSet->GetFirstGid() + tile->GetId();
        if (gid != tileGId)
            continue;

        return tile;
    }

    return nullptr;
}

SceneNodePtr SceneTmxParserImpl::objectProcessor(const std::string &type, const Tmx::Object* object)
{
    // change if() to std::map
    if(type == "Sprite")
    {
        auto objPropertiesMap = object->GetProperties().GetList();
        auto animationSet = objPropertiesMap["Animation"];
        const Tmx::Tileset* tileSet = getTileSetByName(animationSet);
        if (!tileSet)
        {
            printf("tileSet error\n");
            return SceneNodePtr();
        }
        const Tmx::Image* tileSetImage = tileSet->GetImage();

        float objectWorldX = object->GetX();
		//float objectWorldX = object->GetX() - tileSetImage->GetWidth();
        //float objectWorldY = object->GetY() - tileSetImage->GetHeight();
        float objectWorldY = object->GetY();
        float objectWorldWidth = object->GetWidth();
        float objectWorldHeight = object->GetHeight();
        float objectPixelWidth = tileSet->GetTileWidth();
        float objectPixelHeight = tileSet->GetTileHeight();

        RectFloat srcRect = { 0, 0, objectPixelWidth, objectPixelHeight };
        RectFloat worldtRect = { objectWorldX, objectWorldY,
            objectWorldWidth, objectWorldHeight };

        SceneNodePtr tileNode = nodeFactory_->createNode<render::ImageDrawable>(
            object->GetName(), tileSetImage->GetSource(), worldtRect, srcRect, 0);
        setAnimation(tileNode, tileSetImage,
                     tileSet->GetTileWidth(),
                     tileSet->GetTileHeight(),
                     tileSet);

        gamelogic::GameManagerPtr gameMgr = context_->getComponent<
            gamelogic::IGameManager>(nullptr);
        gameMgr->registerSprite(object->GetName(), tileNode);

		return tileNode;
    }

    return SceneNodePtr();
}

const Tmx::Tileset* SceneTmxParserImpl::getTileSetByName(
    const std::string& tileSetName)
{
    for (auto tileSet : tilesetList_)
    {
        if (tileSet->GetName() == tileSetName)
            return tileSet;
    }
    return nullptr;
}
}
}
}