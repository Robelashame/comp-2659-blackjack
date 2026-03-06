#ifndef TIMER_H
#define TIMER_H
#define TRUE 1
#define FALSE 0

#define MAX_TIME 60

typedef struct {
    int seconds;
    int max_time;
    int is_active;
} Timer;

void initialize_timer(Timer *timer, int max_time);

void start_timer(Timer *timer);
void stop_timer(Timer *timer);
void reset_timer(Timer *timer);


void decrement_timer(Timer *timer);


int timer_expired(const Timer *timer);

#endif