#include "deck.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void initialize_deck(Deck *deck) {

    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const char *suits[] = {"H","D","C","S"};

    int index = 0;

    int d, s, r;
    for (d = 0; d < NUMBER_OF_DECKS; d++) {       // repeat for how many decks
        for (s = 0; s < 4; s++) {           // suits
            for (r = 0; r < 13; r++) {      // ranks
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
    int i, j;
    Card temp;
    srand(time(NULL)); // gets the time so its always random
    for (i = NUMBER_OF_DECKS * CARDS_PER_DECK - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = deck->cards[i];
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