#include "timer.h"

void initialize_timer(Timer *timer, int max_time) {
    timer->seconds = 0;
    timer->max_time = MAX_TIME;
    bool is_active = false;
}

void start_timer(Timer *timer) {
    if (timer->seconds > 0)
    timer->is_active = true;
}

void stop_timer(Timer *timer) {
    timer->is_active = false;
}

void reset_timer(Timer *timer) {
    timer->seconds = timer->max_time;
    timer->is_active = false;
}

void decrement_timer(Timer *timer) {
    if (timer->is_active && timer->seconds > 0) {
        timer->seconds--;
        if (timer->seconds == 0) {
            timer->seconds = timer->max_time;
            timer->is_active = false;
        }
    }
}

bool timer_expired(const Timer *timer) {
    return timer->seconds == 0;
}