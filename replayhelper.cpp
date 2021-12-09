#include <windows.h>
#include "rv_common.h"
#include "binloghelper.h"
#include "signalhelper.h"


extern char video_filename[512];
extern char binlog_filename_read[512];
extern int binlog_filename_read_len;

int gPauseStatus;
int gReplayCANThreadRun;
unsigned long greadcnt;
char greadcnt_fraction[512] = {0};
HANDLE g_hEvent;

static HANDLE g_hReplayThread;
static unsigned __int64 ts_anchor;

static double percent = 0;
static double percent_anchor = 0;
static char backspace[256];

static unsigned __int64 ts_additional;

extern unsigned int msgEdlFlag;

void push_fast_forward(void){
    ts_additional = TS_ADDITIONAL_DEFAULT;
}


void restore_fash_forward(void) {
    ts_additional = 0;
}


int update_sig_interval_wrapper(void) {
    int status = NO_ERROR;
    while ((status = update_binlog_read()) == NO_ERROR) {
        greadcnt++;
        if (msgEdlFlag == 1) {
            memcpy(ptr, messageFD.mData, 64);
            gcanid = messageFD.mID;
            ts = messageFD.mHeader.mObjectTimeStamp;
        }
        else if (msgEdlFlag == 0) {
            memcpy(ptr, message2.mData, 8);
            gcanid = message2.mID;
            ts = message2.mHeader.mObjectTimeStamp;
        }
        update_sig();
        if (ts - ts_anchor > (TS_INT + ts_additional)) {
            ts_anchor = ts;
            restore_fash_forward();
            break;
        }
    }
    return status;
}


static DWORD WINAPI ReplayCanFdThread(LPVOID par) {
    int status = NO_ERROR;
    while (gReplayCANThreadRun) {
        WaitForSingleObject(g_hEvent, INFINITE);
        status = update_sig_interval_wrapper();
        if (status != NO_ERROR) {
            gReplayCANThreadRun = 0;
            break;
        }
    }
    return(NO_ERROR);
}


int CreateReplayThread(void) {
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


void initProgreassPercent(void) {
    memset(backspace, '\b', 256);
    backspace[255] = '\0';
    ts_additional = 0;
}


void queryProgressPercentSilent(void) {
    percent = (double)greadcnt / (double)blstatistics.mObjectCount * 100;
    if (percent - percent_anchor > SILENT_PERCENT_THRESHOLD) {
        percent_anchor = percent;
        sprintf(greadcnt_fraction, "%3.1f%%  %10ld/%ld", percent, greadcnt, blstatistics.mObjectCount);
        printf("%s  %s", backspace, greadcnt_fraction);
    }
}


void queryProgressPercentDisplay(void) {
    percent = (double)greadcnt / (double)blstatistics.mObjectCount * 100;
    sprintf(greadcnt_fraction, "%3.1f%%  %10ld/%ld", percent, greadcnt, blstatistics.mObjectCount);
    if (percent - percent_anchor > DISPLAY_PERCENT_THRESHOLD) {
        printf("%s  %s", backspace, greadcnt_fraction);
    }
}


void deinit_progressPercent(void) {
    printf("%s  %3d.0%%  %10ld/%ld\n\n  done!\n\n", backspace, (unsigned char)100, blstatistics.mObjectCount, blstatistics.mObjectCount);
    percent_anchor = 0;
    ts_anchor = 0;
}


void toggle_pause_status(void) {
    gPauseStatus = !gPauseStatus;
}


int query_pause_status(void) {
    return gPauseStatus;
}