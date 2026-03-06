#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "raster.h"
#include "model.h"
#include "bmaps.h"

void render(const Model *model, UINT8 *base);

void render_player(const Player *player, UINT *base);

void render_hand(const Hand *hand, UINT8 *base);

void render_card(const Card *card, UINT8 *base);

void render_dealer(const Dealer *dealer, UINT8 *base);

void render_timer(const Timer *timer, UINT8 *base);

#endif