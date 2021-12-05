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

#define KEY_ENTER 13
#define KEY_ESC   27
#define KEY_SPACE 32

#define KEY_D     68
#define KEY_d     100

#define KEY_M     77
#define KEY_m     109

#define FPS 25
#define WAITMS (1000/FPS)
#define TS_INT (WAITMS*1000000)

#define SILENT_PERCENT_THRESHOLD  1
#define DISPLAY_PERCENT_THRESHOLD  0.1

#define UTC 8

#define FILENAMEPRE       "D:/rv_test/rv"
#define FILENAMEPOSTVIDEO  ".mp4"
#define FILENAMEPOSTBINLOG ".blf"

const char videoext[] = FILENAMEPOSTVIDEO;

#endif
