#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <sys/time.h>

class Timer{
private:
    long int current, last, diff;
public:
    Timer(long int);
    void update();
    bool valid();
    long int now();
};

#endif
