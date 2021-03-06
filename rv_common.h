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

#define KEY_F     70
#define KEY_f     102

#define KEY_G     71
#define KEY_g     103

#define KEY_H     72
#define KEY_h     104

#define KEY_I     73
#define KEY_i     105

#define KEY_M     77
#define KEY_m     109

#define KEY_W     87
#define KEY_w     119

#define KEY_A_L   0x250000
#define KEY_A_U   0x260000
#define KEY_A_R   0x270000
#define KEY_A_D   0x280000

#define FPS 25
#define WAITMS (1000/FPS)
#define TS_INT (WAITMS*1000000)
#define TS_ADDITIONAL_DEFAULT (TS_INT*FPS)

#define SILENT_PERCENT_THRESHOLD  1
#define DISPLAY_PERCENT_THRESHOLD  0.1

#define UTC 8

#define DEFAULTRECORDFOLDER "./record"
#define FILENAMEPRE         "rv"
#define FILENAMEPOSTVIDEO   ".mp4"
#define FILENAMEPOSTBINLOG  ".blf"

const char videoext[] = FILENAMEPOSTVIDEO;

#endif
