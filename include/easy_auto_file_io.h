#ifndef _EASY_AUTO_FILE_IO_H_
#define _EASY_AUTO_FILE_IO_H_

#include <stdio.h>

//
class EasyAutoFileIn
{
public:
    EasyAutoFileIn(const char * p_pathname);

    ~EasyAutoFileIn();

    void * data();

    int size();

private:
    FILE * p_file;
    int n_file_len;
    unsigned char * p_data;
};

//
class EasyAutoFileOut
{
public:
    EasyAutoFileOut(const char * p_pathname);

    ~EasyAutoFileOut();

    int write(const unsigned char * p_data, int n_length);
private:
    const char * p_pathname;
};

#endif