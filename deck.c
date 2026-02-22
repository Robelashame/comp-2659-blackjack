#include "deck.h"
#include <string.h>
#include <stdlib.h>

void initialize_deck(Deck *deck) {

    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const char *suits[] = {"H","D","C","S"};

    int index = 0;

    for (int d = 0; d < NUMBER_OF_DECKS; d++) {       // repeat for how many decks
        for (int s = 0; s < 4; s++) {           // suits
            for (int r = 0; r < 13; r++) {      // ranks
                strcpy(deck->cards[index].rank, ranks[r]);
                strcpy(deck->cards[index].suit, suits[s]);
                set_value(&deck->cards[index]); // set card value
                index++;
            }
        }
    }

    deck->top = 0;  // dealing from first card
}

void shuffle(Deck *deck)
{
    srand(time(NULL)); // gets the time so its always random
    for (int i = NUMBER_OF_DECKS * CARDS_PER_DECK - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
    deck->top = 0;
}

Card deal(Deck *deck) {
    Card delt_card = deck->cards[deck->top];
    deck->top++;
    return delt_card;
}