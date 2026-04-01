#include "timer.h"


#define SECONDS_TOFRAMES(s) s*60

void Timer_init(Timer* timer, int maxTime, bool autoStart, bool repeat,void (*callBack)(void)){
    timer->callBack=callBack;
    timer->currentTime=0;
    timer->maxTime=SECONDS_TOFRAMES(maxTime);
    timer->started = autoStart;
    timer->repeat = repeat;
}

void Timer_start(Timer* timer){
    timer->started = true;
}

void Timer_stop(Timer* timer){
    timer->started = false;
    timer->currentTime = 0;
}

void Timer_pause(Timer* timer){
    timer->started = false;
}

void Timer_update(Timer* timer){

    if(!timer->started) return;

    if(timer->currentTime>=timer->maxTime){
        timer->callBack();
        if(timer->repeat){
            timer->currentTime = 0;
        }else{
            timer->started = false;
        }
    }

    timer->currentTime ++;
}
