#include <stdio.h>
#include "systimehelper.h"
#include "rv_common.h"

extern char record_folder[512];
extern int record_folder_len;
extern char video_filename[512];
extern char binlog_filename_write[512];

static char* p_record_folder;
static char record_folder_default[] = { DEFAULTRECORDFOLDER };

SYSTEMTIME systemTime, localTime, local_time;
FILETIME   timeInSec;
TM_u TM, local_time_TM;

void gen_name_with_rectime(void) {
    GetLocalTime(&systemTime);
    if (record_folder_len > 0) {
        p_record_folder = &record_folder[0];
    }
    else {
        p_record_folder = &record_folder_default[0];
    }
    sprintf(video_filename, "%s/%s_%d%02d%02d_%02d%02d%02d%s",
        p_record_folder,
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTVIDEO);
    sprintf(binlog_filename_write, "%s/%s_%d%02d%02d_%02d%02d%02d%s",
        p_record_folder,
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTBINLOG);
}