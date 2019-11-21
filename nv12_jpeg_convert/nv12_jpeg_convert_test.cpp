#include "YUVToJpeg.h"
#include <stdio.h>

#include "easy_auto_file_io.h"
#include "easy_log.h"

int nv12_jpeg_convert_test()
{
    EasyAutoFileIn file_nv12("./6016x4512_nv12.yuv");
    int nNV12Width = 6016;
    int nNV12Height = 4512;
    unsigned char * pDataJpg = NULL;
    int nJpgLen = 0;
    eRetMsg msg = NV12ToJpeg(
        (unsigned char*)file_nv12.data(),
        nNV12Width,
        nNV12Height,
        &pDataJpg,
        &nJpgLen
    );
    EASY_LOGI("msg = %s", msg);
    if(pDataJpg)
    {
        EasyAutoFileOut file_jpeg("./6016x4512_nv12.jpg");
        int n_write_size = file_jpeg.write(pDataJpg, nJpgLen);
        EASY_LOGI("n_write_size = %d", n_write_size);
        free(pDataJpg);
    }

    return 0;
}