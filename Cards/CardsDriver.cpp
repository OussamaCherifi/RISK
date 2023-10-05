#include "Cards.h"
using namespace std;

void testCards() {
    Deck deck;
    Hand hand;

    //draw cards to add them to the deck
    for (int i = 0; i < 5; ++i) {
        Cards card = deck.draw();
        hand.addCard(card);
        cout << "Drew a " << card.getTypeAsString() << " card." << endl;
        cout << "Deck size: " << deck.getCardNum() << endl;
    }
    //play a card from your hand, then put in back at the bottom of the deck once it is played
    if (hand.getCardNum() > 0) {
        Cards card = hand.getCard(0);
        card.play();
        deck.addCard(card);
        hand.removeCard(0);
    }
}