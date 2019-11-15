#ifndef _EASY_TIMER_H_
#define _EASY_TIMER_H_


class EasyTimer
{
public:
    EasyTimer(const char *msg);

    ~EasyTimer();
private:
    char msg[1024];
    long t1;
};

#endif