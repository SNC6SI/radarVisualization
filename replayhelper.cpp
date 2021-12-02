#include <windows.h>
#include "rv_common.h"
#include "binloghelper.h"
#include "signalhelper.h"


extern char video_filename[512];
extern char binlog_filename_read[512];
extern int binlog_filename_read_len;

int gReplayCANThreadRun;
unsigned long greadcnt;
HANDLE g_hEvent;

static HANDLE g_hReplayThread;
static unsigned __int64 ts_anchor;


static DWORD WINAPI ReplayCanFdThread(LPVOID par) {
    int status = NO_ERROR;
    greadcnt = 0;
    while (gReplayCANThreadRun) {
        WaitForSingleObject(g_hEvent, 40);
        while ((status = update_binlog_read()) == NO_ERROR) {
            greadcnt++;
            memcpy(ptr, messageFD.mData, 64);
            gcanid = messageFD.mID;
            ts = messageFD.mHeader.mObjectTimeStamp;
            update_sig();
            if (ts - ts_anchor > TS_INT) {
                ts_anchor = ts;
                break;
            }
        }
        if (status != NO_ERROR) {
            gReplayCANThreadRun = 0;
            break;
        }
    }
    return(NO_ERROR);
}

int ReplayCreateRxThread(void) {
    int status = -1;
    DWORD ThreadId = 0;

    g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    status = init_binlog_read();
    if (status == 0) {
        g_hReplayThread = CreateThread(0, 0x1000, ReplayCanFdThread, (LPVOID)0, 0, &ThreadId);
    }

    return status;
}


void prepareVideoFileName(void) {
    strcpy(video_filename, binlog_filename_read);
    strcpy(video_filename + (binlog_filename_read_len - 4), videoext);
    printf("\n  blf:    %s", binlog_filename_read);
    printf("\n  video:  %s\n\n", video_filename);
}