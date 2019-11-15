#include "easy_log.h"
#include "easy_timer.h"

#include <sys/time.h>
#include <string.h>

EasyTimer::EasyTimer(const char *msg)
{
    timeval tm;
    gettimeofday(&tm, NULL);
    t1 = tm.tv_sec * 1000 + tm.tv_usec / 1000;
    strcpy(this->msg, msg);
}

EasyTimer::~EasyTimer()
{
    timeval tm;
    gettimeofday(&tm, NULL);
    long t2 = tm.tv_sec * 1000 + tm.tv_usec / 1000;
    long t = t2 - t1;
    EASY_LOGI("%s time cost: %ld ms", msg, t);
}