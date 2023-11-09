#include "Orders.h"
#include <iostream>
using namespace std;
#include "OrdersDriver.h"

void testOrdersList()
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

