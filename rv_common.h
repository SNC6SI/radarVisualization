#ifndef _RV_COMMON_
#define _RV_COMMON_

#include <stdio.h>

typedef short rv_status;

#define RV_SUCCESS 0 
#define RV_FAILURE -1

#define RV_DEBUG

#ifdef RV_DEBUG
#define RV_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define RV_PRINTF(f_, ...)
#endif

#define KEY_ESC 27

#define UTC 8
#define FILENAMEPRE       "D:/rv"
#define FILENAMEPOSTVIDEO  ".mp4"
#define FILENAMEPOSTBINLOG ".mp4"

#endif
