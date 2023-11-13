#include "Orders.h"
#include <iostream>
using namespace std;

void testOrdersLists()
{
    cout<<'\n';
    //Creating one of each order
    Deploy* deploy = new Deploy();
    Advance* advance = new Advance();
    Bomb* bomb = new Bomb();
    Blockade* blockade = new Blockade();
    Airlift* airlift = new Airlift();
    Negotiate* negotiate = new Negotiate();

    //Creating an OrderList
    OrdersList* list = new OrdersList();

    //Adding each order in the list
    list->addList(deploy);
    list->addList(advance);
    list->addList(bomb);

    cout<< *list<< '\n';

    cout << "--------Testing removing an order from the OrderList (index 1)----------\n";
    list->remove(1);
    cout<< *list<< '\n';

    cout << "--------Testing moving an order from the OrderList (index 1 and index 3)----------\n";
    list->move(1,3);
    cout<< *list<< '\n';

}

void testOrderExecution(){
    // Create players and territories for testing
    Player player1("Player1");
    Player player2("Player2");

    Territory sourceTerritory("SourceTerritory", &player1);
    Territory targetTerritory("TargetTerritory", &player2);

    // Add territories to the map
    Map gameMap;
    gameMap.addTerritory(&sourceTerritory);
    gameMap.addTerritory(&targetTerritory);

    // Deploy order
    Deploy deployOrder(&player1, &sourceTerritory, 5);
    deployOrder.validate();
    deployOrder.execute();

    // Advance order
    Advance advanceOrder(&player1, &sourceTerritory, &targetTerritory, 3);
    advanceOrder.validate();
    advanceOrder.execute();

    // Airlift order (assuming player1 has an airlift card)
    Cards airliftCard(AIRLIFT);
    player1.getHand()->addCard(airliftCard);

    Airlift airliftOrder(&player1, &sourceTerritory, &targetTerritory, 2);
    airliftOrder.validate();
    airliftOrder.execute();

    // Bomb order (assuming player1 has a bomb card)
    Cards bombCard(BOMB);
    player1.getHand().addCard(bombCard);

    Bomb bombOrder(&player1, &targetTerritory);
    bombOrder.validate();
    bombOrder.execute();

    // Blockade order (assuming player1 has a blockade card)
    Cards blockadeCard(BLOCKADE);
    player1.getHand()->addCard(blockadeCard);

    Blockade blockadeOrder(&player1, &sourceTerritory);
    blockadeOrder.validate();
    blockadeOrder.execute();

    // Negotiate order (assuming player1 has a diplomacy card)
    Cards diplomacyCard(DIPLOMACY);
    player1.getHand()->addCard(diplomacyCard);

    Negotiate negotiateOrder(&player1, &player2);
    negotiateOrder.validate();
    negotiateOrder.execute();
}
}

