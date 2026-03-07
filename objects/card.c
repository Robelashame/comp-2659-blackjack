#include "card.h"
#include <stdlib.h>
#include <string.h>

void set_value(Card *card) {
    if (strcmp(card->rank, "A") == 0) {
        card->value = 11;
    }
    else if (strcmp(card->rank, "K") == 0 || 
            strcmp(card->rank, "Q") == 0 ||
            strcmp(card->rank, "J") == 0) {
        card->value = 10;
    } else {
        card->value = atoi(card->rank);
    }
}

