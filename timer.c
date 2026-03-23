#include "timer.h"

void initialize_timer(Timer *timer, int max_time) {
    timer->seconds = max_time;
    timer->max_time = max_time;
    timer->is_active = FALSE;
}

void start_timer(Timer *timer) {
    if (timer->seconds > 0) {
        timer->is_active = TRUE;
        timer->last_tick = time(NULL);
    }
}

void stop_timer(Timer *timer) {
    timer->is_active = FALSE;
}

void reset_timer(Timer *timer) {
    timer->seconds = timer->max_time;
    timer->is_active = FALSE;
}

int timer_expired(const Timer *timer) {
    return timer->seconds == 0;
}

void updateing_timer(Timer *timer) {
    time_t now;

    if (!timer->is_active)
        return;
    
    now = time(NULL);

    if (now > timer->last_tick) {
        timer->seconds--;
        timer->last_tick = now;
    }

    if (timer->seconds <= 0) {
        timer->seconds = 0;
        timer->is_active = FALSE;
    }
}