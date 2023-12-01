#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H

#include<vector>
#include "Player.h"

using namespace std;

class Player;

class Territory;

class PlayerStrategy {
protected:
    Player *p;
public:
    virtual vector<Territory *> toAttack() = 0;

    virtual vector<Territory *> toDefend() = 0;

    virtual void issueOrder() = 0;

    virtual string getType() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
    explicit HumanPlayerStrategy(Player *player);

    vector<Territory *> toAttack() override;

    vector<Territory *> toDefend() override;

    void issueOrder() override;

    string getType() override;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    explicit AggressivePlayerStrategy(Player *player);

    vector<Territory *> toAttack() override;

    vector<Territory *> toDefend() override;

    void issueOrder() override;

    string getType() override;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    explicit BenevolentPlayerStrategy(Player *player);

    vector<Territory *> toAttack() override;

    vector<Territory *> toDefend() override;

    void issueOrder() override;

    string getType() override;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    explicit NeutralPlayerStrategy(Player *player);

    vector<Territory *> toAttack() override;

    vector<Territory *> toDefend() override;

    void issueOrder() override;

    string getType() override;

};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
    explicit CheaterPlayerStrategy(Player *player);

    vector<Territory *> toAttack() override;

    vector<Territory *> toDefend() override;

    void issueOrder() override;

    string getType() override;

    void cheat();  // take all adjacent territories to the player's

};

#endif
