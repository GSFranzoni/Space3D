#include "Timer.h"

Timer::Timer(long int ms){
    this->current = this->now();
    this->last = current;
    this->diff = ms;
}

void Timer::update(){
    this->current = this->now();
}

long int Timer::now(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec*1000+tp.tv_usec/1000;
}

bool Timer::valid(){
    if(this->current-this->last>=diff){
        this->last = current;
        return true;
    }
    return false;
}
