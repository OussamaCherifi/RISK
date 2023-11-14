#include "Orders.h"
#include <iostream>
using namespace std;

//void testOrdersLists()
//{

    //cout<<'\n';
    //Creating one of each order
    //Deploy* deploy = new Deploy();
    //Advance* advance = new Advance();
    //Bomb* bomb = new Bomb();
    //Blockade* blockade = new Blockade();
    //Airlift* airlift = new Airlift();
    //Negotiate* negotiate = new Negotiate();

    //Creating an OrderList
    //OrdersList* list = new OrdersList();

    //Adding each order in the list
    //list->addList(deploy);
    //list->addList(advance);
    //list->addList(bomb);

    //cout<< *list<< '\n';

    //cout << "--------Testing removing an order from the OrderList (index 1)----------\n";
    //list->remove(1);
    //cout<< *list<< '\n';

    //cout << "--------Testing moving an order from the OrderList (index 1 and index 3)----------\n";
    //list->move(1,3);
    //cout<< *list<< '\n';

//}

void testOrderExecution(){
    // Create players and territories for testing
    Player player1;
    Player player2;
    Deck deck1;

    player1.setName("John");
    player2.setName("Mark");
    player1.setDeck(deck1);
    player2.setDeck(deck1);
    player1.setReinforcementPool(new int(10));
    player2.setReinforcementPool(new int(15));

    // Add territories to the map
    Territory France("France", "Europe", 1, 1);
    Territory Germany("Germany", "Europe", 1, 2);
    Territory Spain("Spain", "Europe", 1, 3);
    Territory Greece("Greece", "Europe", 2, 3);
    Territory Turkey("Turkey", "Europe", 2,4);

    //give troops to each territory for testing purposes
    France.addArmies(100);
    //Germany.addArmies(100);
    Spain.addArmies(100);
    Greece.addArmies(100);
    Turkey.addArmies(100);

    //Add adjacent territories to map
    France.addAdjacent(&Germany);
    Germany.addAdjacent(&France);
    France.addAdjacent(&Spain);
    Spain.addAdjacent(&France);
    Turkey.addAdjacent(&Greece);
    Greece.addAdjacent(&Turkey);

    //set Player territories
    Spain.setPlayer(&player2);
    France.setPlayer(&player1);
    Germany.setPlayer(&player2);
    Greece.setPlayer(&player2);
    Turkey.setPlayer(&player2);

    // Deploy order that should work
    Deploy deployOrder(&player1, &France, 5);
    deployOrder.validate();
    deployOrder.execute();

    //Deploy order that should not work
    Deploy deployOrder2(&player1, &France, 100);
    deployOrder2.validate();
    deployOrder2.execute();

    // Airlift order that should work (assuming player1 has an airlift card)
    Cards airliftCard(AIRLIFT);
    player1.getHand()->addCard(airliftCard);

    Airlift airlift(&player2, &Turkey, &Greece, 2);
    airlift.validate();
    airlift.execute();

    // Airlift order that should not work
    player1.getHand()->addCard(airliftCard);

    Airlift airliftOrder2(&player1, &Germany, &France, 2);
    airliftOrder2.validate();
    airliftOrder2.execute();

    // Advance order that should not work
    Advance advanceOrder(&player2, &Germany, &Greece, 3);
    advanceOrder.validate();
    advanceOrder.execute();

    //Advance order that should work
    Advance advanceOrder2(&player2, &Greece, &Turkey, 3);
    advanceOrder2.validate();
    advanceOrder2.execute();

    // Bomb order that should work
    Cards bombCard(BOMB);
    player1.getHand()->addCard(bombCard);

    Bomb bombOrder(&player1, &Spain);
    bombOrder.validate();
    bombOrder.execute();

    // Blockade order that should work
    Cards blockadeCard(BLOCKADE);
    player1.getHand()->addCard(blockadeCard);

    Blockade blockadeOrder(&player1, &France);
    blockadeOrder.validate();
    blockadeOrder.execute();

    cout << "Territory Germany is now owned by: " << Germany.getPlayer()->getPlayerName() << endl;

    //Advance order that transfers territory
    Advance advanceOrder3(&player1, &France, &Germany, 8);
    advanceOrder3.validate();
    advanceOrder3.execute();

    cout << "Territory Germany is now owned by: " << Germany.getPlayer()->getPlayerName() << endl;

    // Negotiate order (assuming player1 has a diplomacy card)
    Cards diplomacyCard(DIPLOMACY);
    player1.getHand()->addCard(diplomacyCard);

    Negotiate negotiateOrder(&player1, &player2);
    negotiateOrder.validate();
    negotiateOrder.execute();

    //Proof they cannot attack
    Advance advanceOrder4(&player1, &France, &Spain, 1);
    advanceOrder4.validate();
    advanceOrder4.execute();
}


