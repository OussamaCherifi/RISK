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
    testLoadMaps();

    player1.setReinforcementPool(new int(10));
    player2.setReinforcementPool(new int(15));

    // Add territories to the map
    Territory T("France", "Europe", 1, 1);
    Territory S("Germany", "Europe", 1,2);
    Territory V("Spain", "Europe", 1,3);
    Territory R("Greece", "Europe", 2,3);
    T.addAdjacent(&S);
    S.addAdjacent(&T);
    T.addAdjacent(&V);
    V.addAdjacent(&T);

    V.setPlayer(&player2);
    T.setPlayer(&player1);
    S.setPlayer(&player2);
    R.setPlayer(&player2);

    // Deploy order that should work
    Deploy deployOrder(&player1, &T, 5);
    deployOrder.validate();
    deployOrder.execute();

    //Deploy order that should not work
    Deploy deployOrder2(&player1, &T, 15);
    deployOrder.validate();
    deployOrder.execute();

    // Advance order that should not work
    Advance advanceOrder(&player2, &S, &R, 3);
    advanceOrder.validate();
    advanceOrder.execute();

    //Advance order that should work
    Advance advanceOrder2(&player2, &S, &R, 3);
    advanceOrder.validate();
    advanceOrder.execute();

    cout<<"Territory S is now owned by: "<<S.getPlayer()<<endl;

    //Advance order that transfers territory
    Advance advanceOrder3(&player1, &T, &S, 8);
    advanceOrder.validate();
    advanceOrder.execute();

    cout<<"Territory S is now owned by: "<<S.getPlayer()<<endl;

    // Airlift order that should work (assuming player1 has an airlift card)
    Cards airliftCard(AIRLIFT);
    player1.getHand()->addCard(airliftCard);

    Airlift airliftOrder(&player2, &S, &R, 2);
    airliftOrder.validate();
    airliftOrder.execute();

    // Airlift order that should not work
    Cards airliftCard2(AIRLIFT);
    player1.getHand()->addCard(airliftCard);

    Airlift airliftOrder2(&player2, &S, &T, 2);
    airliftOrder.validate();
    airliftOrder.execute();

    // Bomb order (assuming player1 has a bomb card)
    Cards bombCard(BOMB);
    player1.getHand()->addCard(bombCard);

    Bomb bombOrder(&player1, &R);
    bombOrder.validate();
    bombOrder.execute();

    // Blockade order (assuming player1 has a blockade card)
    Cards blockadeCard(BLOCKADE);
    player1.getHand()->addCard(blockadeCard);

    Blockade blockadeOrder(&player1, &T);
    blockadeOrder.validate();
    blockadeOrder.execute();

    // Negotiate order (assuming player1 has a diplomacy card)
    Cards diplomacyCard(DIPLOMACY);
    player1.getHand()->addCard(diplomacyCard);

    Negotiate negotiateOrder(&player1, &player2);
    negotiateOrder.validate();
    negotiateOrder.execute();

    //Proof they cannot attack
    Advance advanceOrder4(&player1, &T, &V, 1);
    advanceOrder.validate();
    advanceOrder.execute();
}


