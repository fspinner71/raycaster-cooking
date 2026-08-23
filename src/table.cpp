#include "table.h"

Table::Table(SDL_Renderer* r)
: NPC(r, AssetManager::getInstance().getTextureID("table"), InteractionID::None), onTable{Item::None} {
  getSprite()->setSize({500, 500});
  getSprite()->setZOffset(-250);
  getSprite()->setFrameWidth(64);
  getSprite()->setFrameIndex(0);
}

void Table::interact(Item* holding) {
    NPC::interact(holding);
    if (*holding == Item::None && onTable != Item::None) {
        *holding = onTable;
        onTable = Item::None;
    } else if(*holding != Item::None && onTable == Item::None) {
        onTable = *holding;
        *holding = Item::None;
    }
}

void Table::update(double deltaTime) {
    NPC::update(deltaTime);
}
