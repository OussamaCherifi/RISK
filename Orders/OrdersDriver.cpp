#include "Orders.h"
#include <iostream>
using namespace std;

void testOrdersList()
{
    cout<<'\n';
    Deploy* deploy = new Deploy();
    Advance* advance = new Advance();


    OrdersList* list = new OrdersList();

    list->addList(Deploy);


    cout<< *list<< '\n';

    list->remove(1);
    cout<< *list;

}
int main(){
    testOrdersList;
    return 0;
}