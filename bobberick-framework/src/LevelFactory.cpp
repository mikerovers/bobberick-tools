#include <tmxlite/TileLayer.hpp>
#include "LevelFactory.h"
#include "entity/components/TileSetComponent.h"
#include "services/ServiceManager.h"
#include "TextureManager.h"

TileSetComponent* LevelFactory::Load(std::string path, SDL_RendererPointer renderer)
{
    tmx::Map tileMap;
    tileMap.load("" + path);

    auto component = new TileSetComponent();

    auto mapDimensions = tileMap.getTileCount();
    component->rows = mapDimensions.y;
    component->cols = mapDimensions.x;
    auto tileSize = tileMap.getTileSize();
    component->tileWidth = tileSize.x;
    component->tileHeight = tileSize.y;

    auto& mapTileSets = tileMap.getTilesets();
    for (auto& tileSet : mapTileSets) {
        auto imagePath = tileSet.getImagePath();
        auto texture = ServiceManager::Instance()->getService<TextureManager>().load(imagePath.c_str(), tileSet.getName(), renderer);
        if (texture) {
            component->tileSets.insert(std::pair<gid, std::string>(tileSet.getFirstGID(), tileSet.getName()));
        } else {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not find texturemap.");

            break;
        }
    }

    auto& mapLayers = tileMap.getLayers();
    for (auto& layer: mapLayers) {
        if (layer->getType() != tmx::Layer::Type::Tile) {
            continue;
        }

        auto* tileLayer = dynamic_cast<const tmx::TileLayer*>(layer.get());

        auto& layerTiles = tileLayer->getTiles();

        for (auto y = 0; y < component->rows; y++) {
            for (auto x = 0; x < component->cols; x++) {
                auto tileIndex = x + (y * component->cols);
                auto curGid = layerTiles[tileIndex].ID;

                // Tile is empty if curGid == 0
                if (curGid == 0) {
                    continue;
                }

                auto tileSetGid = -1;
                for (auto& ts : component->tileSets) {
                    if (ts.first < curGid) {
                        tileSetGid = ts.first;

                        break;
                    }
                }

                // Tileset not found.
                if (tileSetGid == -1) {
                    continue;
                }

                curGid -= tileSetGid;
                auto tileSetWidth = 0;
                auto tileSetHeight = 0;
                auto textureManager = ServiceManager::Instance()->getService<TextureManager>();
                auto texture = textureManager.getTexture(component->tileSets[tileSetGid]).get();
                SDL_QueryTexture(texture, nullptr, nullptr, &tileSetWidth, &tileSetHeight);

                auto regionX = (curGid % (tileSetWidth / component->tileWidth)) * component->tileWidth;
                auto regionY = (curGid / (tileSetWidth / component->tileHeight)) * component->tileHeight;

                auto xPos = x * component->tileWidth;
                auto yPos = y * component->tileHeight;

                auto name = component->tileSets[tileSetGid];
                Tile* tile = new Tile(component->tileSets[tileSetGid], xPos, yPos, regionX, regionY, component->tileWidth, component->tileHeight);
                component->tiles.push_back(tile);
            }
        }
    }

    return component;
}
