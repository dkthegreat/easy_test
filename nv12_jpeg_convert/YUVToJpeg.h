/****************************************************************************
 * FileName: YUVToJpeg.h
 * Description: 
 * Author: Murphys
 * Date: 2016.06.07
 * 
 ****************************************************************************/
#ifndef _H_YUVTOJPEG_
#define _H_YUVTOJPEG_
 
#include "ErrorDefine.h"
#include <malloc.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
eRetMsg NV21ToJpeg(
	const unsigned char * pDataNV21,
	int nNV21Width,
	int nNV21Height,
	unsigned char ** ppDataJpg,			// must be free by call: free(*ppDataJpg)
	int * nJpgLen
);

//-----------------------------------------------------------------------------
eRetMsg NV12ToJpeg(
	const unsigned char * pDataNV12,
	int nNV12Width,
	int nNV12Height,
	unsigned char ** ppDataJpg,			// must be free by call: free(*ppDataJpg)
	int * nJpgLen
);

#ifdef __cplusplus
}
#endif



#endif
