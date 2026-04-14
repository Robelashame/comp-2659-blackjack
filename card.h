#ifndef CARD_H
#define CARD_H

typedef struct {
    char rank[10];
    char suit[10];
    int value;
    int position[2];
    int start_position[2];
    int target_position[2];
    int path_progress;
    int is_hidden;
    int is_moving;
} Card;

void set_value(Card *card);

#endif