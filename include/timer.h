#pragma once
#include <raylib.h>

typedef struct _timer{
    int currentTime;
    int maxTime;
    bool started;
    bool repeat;
    void (*callBack)(void);
} Timer;

void Timer_init(Timer* timer, int maxTime, bool started, bool repeat,void (*callBack)(void));
void Timer_start(Timer* timer);
void Timer_stop(Timer* timer);
void Timer_pause(Timer* timer);
void Timer_update(Timer* timer);