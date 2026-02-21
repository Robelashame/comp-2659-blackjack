#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

#define MAX_TIME 60

typedef struct {
    int seconds;
    int max_time;
    bool is_active;
} Timer;

void initialize_timer(Timer *timer, int max_time);

void start_timer(Timer *timer);
void stop_timer(Timer *timer);
void reset_timer(Timer *timer);


void update_timer(Timer *timer);


bool timer_expired(const Timer *timer);

#endif