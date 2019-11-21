#include "easy_auto_file_io.h"
#include "easy_log.h"

EasyAutoFileIn::EasyAutoFileIn(const char * p_pathname) :
p_file(NULL),
n_file_len(0),
p_data(NULL)
{
    p_file = fopen(p_pathname, "rb");
    if(p_file)
    {
        fseek(p_file, 0, SEEK_END);
        n_file_len = ftell(p_file);
        if(n_file_len > 0)
        {
            fseek(p_file, 0, SEEK_SET);
            p_data = new unsigned char[n_file_len];
            int n_file_read = fread(p_data, n_file_len, 1, p_file);
            n_file_read = n_file_read * n_file_len;
            if(n_file_read != n_file_len)
            {
                EASY_LOGE("%s: n_file_read = %d, n_file_len = %d", p_pathname, n_file_read, n_file_len);
            }
        }
        else
        {
            EASY_LOGE("%s: n_file_len = %d", p_pathname, n_file_len);
        }
        
    }
}

EasyAutoFileIn::~EasyAutoFileIn()
{
    if(p_file)
    {
        fclose(p_file);
    }

    if(p_data)
    {
        delete p_data;
    }
}

void * EasyAutoFileIn::data()
{
    return p_data;
}

int EasyAutoFileIn::size()
{
    return n_file_len;
}

//
EasyAutoFileOut::EasyAutoFileOut(const char * p_pathname) :
p_pathname(p_pathname)
{

}

EasyAutoFileOut::~EasyAutoFileOut()
{

}

int EasyAutoFileOut::write(const unsigned char * p_data, int n_length)
{
    FILE * p_file = fopen(p_pathname, "wb+");
    int n_write_len = fwrite(p_data, n_length, 1, p_file);
    fclose(p_file);
    return n_write_len * n_length;
}