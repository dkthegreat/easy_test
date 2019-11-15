#ifndef _EASY_LOG_H_
#define _EASY_LOG_H_

#define TAG "EASY_TEST"

#include <stdio.h>

#ifdef __ANDROID__
    #include <android/log.h>

    #define EASY_LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__); \
                            __android_log_print(ANDROID_LOG_INFO, TAG, "\n"); \
                            printf(__VA_ARGS__); \
                            printf("\n")
    #define EASY_LOGW(x,...) __android_log_print(ANDROID_LOG_WARN, TAG, "\e[0;31m" x "\033[0m",##__VA_ARGS__); \
                            __android_log_print(ANDROID_LOG_WARN, TAG, "\n"); \
                            printf("\e[0;31m" x "\033[0m",##__VA_ARGS__); \
                            printf("\n"); printf("\e[1;34m now file:%s ==== now line:%d\n \033[0m", __FILE__, __LINE__)
    #define EASY_LOGE(x,...) __android_log_print(ANDROID_LOG_ERROR, TAG, "\e[1;31m" x "\033[0m",##__VA_ARGS__); \
                            __android_log_print(ANDROID_LOG_ERROR, TAG, "\n"); \
                            printf("\e[1;31m" x "\033[0m",##__VA_ARGS__); \
                            printf("\n"); printf("\e[1;34m now file:%s ==== now line:%d\n \033[0m", __FILE__, __LINE__)
    #define EASY_LOGD(x,...) __android_log_print(ANDROID_LOG_DEBUG, TAG, "\e[1;32m" x "\033[0m",##__VA_ARGS__); \
                            __android_log_print(ANDROID_LOG_DEBUG, TAG, "\n"); \
                            printf("\e[1;32m" x "\033[0m",##__VA_ARGS__); \
                            printf("\n"); printf("\e[1;34m now file:%s ==== now line:%d\n \033[0m", __FILE__, __LINE__)
#else // linux x86 64

    #define EASY_LOGI(...) printf(__VA_ARGS__); printf("\n")
    #define EASY_LOGW(x,...) printf("\e[0;31m" x "\033[0m",##__VA_ARGS__); printf("\n"); printf("\e[1;34mnow file:%s ==== now line:%d\n\033[0m", __FILE__, __LINE__)
    #define EASY_LOGE(x,...) printf("\e[1;31m" x "\033[0m",##__VA_ARGS__); printf("\n"); printf("\e[1;34mnow file:%s ==== now line:%d\n\033[0m", __FILE__, __LINE__)
    #define EASY_LOGD(x,...) printf("\e[1;32m" x "\033[0m",##__VA_ARGS__); printf("\n"); printf("\e[1;34mnow file:%s ==== now line:%d\n\033[0m", __FILE__, __LINE__)
   
#endif



#endif