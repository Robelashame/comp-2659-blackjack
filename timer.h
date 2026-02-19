#ifndef TIMER_H
#define TIMER_H

typedef struct {
    int seconds;
    int max_time;
    bool is_active;
} Timer;

#endif