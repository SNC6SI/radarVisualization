#include <stdio.h>
#include "systimehelper.h"
#include "rv_common.h"

SYSTEMTIME systemTime;

extern char video_filename[512];
extern char binlog_filename_write[512];

void get_rectime(void) {
    GetLocalTime(&systemTime);
    sprintf(video_filename, "%s_%d%02d%02d_%02d%02d%02d%s",
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTVIDEO);
    sprintf(binlog_filename_write, "%s_%d%02d%02d_%02d%02d%02d%s",
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTBINLOG);
}