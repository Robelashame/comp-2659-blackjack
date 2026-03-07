#include "timer.h"

void initialize_timer(Timer *timer, int max_time) {
    timer->seconds = max_time;
    timer->max_time = max_time;
    timer->is_active = FALSE;
}

void start_timer(Timer *timer) {
    if (timer->seconds > 0)
    timer->is_active = TRUE;
}

void stop_timer(Timer *timer) {
    timer->is_active = FALSE;
}

void reset_timer(Timer *timer) {
    timer->seconds = timer->max_time;
    timer->is_active = FALSE;
}

void decrement_timer(Timer *timer) {
    if (timer->is_active && timer->seconds > 0) {
        timer->seconds--;
        if (timer->seconds == 0) {
            timer->seconds = timer->max_time;
            timer->is_active = FALSE;
        }
    }
}

int timer_expired(const Timer *timer) {
    return timer->seconds == 0;
}