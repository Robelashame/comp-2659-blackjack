#ifndef CARD_H
#define CARD_H

typedef struct {
    char rank[10];
    char suit[10];
    int value;
    int position[2];
} Card;

void set_value(Card *card);

#endif