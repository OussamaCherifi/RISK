#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include<vector>
#include "Player.h"

using namespace std;

class Player;
class Territory;

class PlayerStrategy{
protected:
    Player *p;
public:
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;
    virtual void issueOrder() = 0;
};

class HumanPlayerStrategy: public PlayerStrategy{
public:
    HumanPlayerStrategy();
    HumanPlayerStrategy(Player *player);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    void issueOrder();
};
#endif
