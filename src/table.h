#ifndef TABLE_H
#define TABLE_H

#include "npc.h"

class Table : public NPC {
private:
    Item onTable;
public:
    Table(SDL_Renderer* r);
    virtual void interact(Item* holding);
    virtual void update(double deltaTime);

};

#endif
