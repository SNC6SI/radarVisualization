#include "rv_common.h"
#include "rv_param.h"
#include "menuhelper.h"
#include "dialoghelper.h"
#include "capturehelper.h"
#include "vectorhelper.h"
#include "binloghelper.h"
#include "videohelper.h"
#include "signalhelper.h"
#include "plothelper.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

using namespace cv;
static char backspace[256];
SYSTEMTIME systemTime;
char video_filename[512];
char binlog_filename_write[512];
char binlog_filename_read[512];
int binlog_filename_read_len;
static unsigned __int64 ts_anchor;
static void get_rectime(void);
static void online_mode(void);
static void offline_mode(void);


int main(int argc, char* argv[]) {
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_WARNING);
    memset(backspace, '\b', 256);
    backspace[255] = '\0';
    select_mode();
    if (selected_mode == 1) {
        online_mode();
    }
    else if (selected_mode == 2) {
        offline_mode();
    }
    else {
        return 0;
    }
}


static void online_mode(void) {
    XLstatus      xlStatus;
    int           activated = 0;
    rv_status     rvStatus;
    
    get_rectime();

    xlStatus = rvInitDriver();
    if (XL_SUCCESS == xlStatus) {
        select_can_channel();
    }
    xlStatus = rvOpenDriver();
    if(XL_SUCCESS == xlStatus) {
        xlStatus = rvCreateRxThread();
    }
    if(XL_SUCCESS == xlStatus) {
        xlStatus = xlActivateChannel(g_xlPortHandle, g_xlChannelMask, XL_BUS_TYPE_CAN, XL_ACTIVATE_RESET_CLOCK);
        if(xlStatus == XL_SUCCESS) {
            activated = 1;
        }
    }

    init_sig();
    init_axis();
    rvStatus = query_camera();
    if (rvStatus == RV_SUCCESS) {
        select_camera();
        init_capture();
    }
 
    moveWindow("radar visualization online", -15, 0);
    video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), 25, Size(XCOL + CAM1_XCOL, YROW), true);

    while (waitKey(40) != KEY_ESC) {
        update_img();
        update_video_online();
        imshow("radar visualization online", recframe);
        video_writer.write(recframe);
    }
    video_writer.release();
    deinit_capture();
    deinit_binlog_write();
}


static void offline_mode(void) {
    XLstatus xlStatus;
    unsigned long readcnt;
    double percent, percent_anchor;
    capOpened = 0;
    BasicFileOpen();
    init_sig();
    init_axis();
    xlStatus = (XLstatus)init_binlog_read();
    if (xlStatus == 0) {
        strcpy(video_filename, binlog_filename_read);
        strcpy(video_filename + (binlog_filename_read_len - 4), videoext);
        printf("\n  video:  %s\n\n", video_filename);
        if (blstatistics.mObjectCount != 0) {
            readcnt = 0;
            ts_anchor = 0;
            percent = 0;
            percent_anchor = 0;
            video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), 25, Size(XCOL, YROW), true);
            while (1) {
                if (!(readcnt < blstatistics.mObjectCount)) {
                    break;
                }
                update_binlog_read();
                memcpy(ptr, messageFD.mData, 64);
                gcanid = messageFD.mID;
                ts = messageFD.mHeader.mObjectTimeStamp;
                update_sig();
                if (ts - ts_anchor > TS_INT) {
                    ts_anchor = ts;
                    update_img();
                    update_video_offline();
                    video_writer.write(recframe_offline);
                }
                readcnt++;
                percent = (double)readcnt / (double)blstatistics.mObjectCount * 100;
                if (percent - percent_anchor > 1) {
                    percent_anchor = percent;
                    printf("%s %3d.0%%  %10ld/%ld", backspace, (unsigned char)percent, readcnt, blstatistics.mObjectCount);
                }
            }
            printf("%s  %3d.0%%  %10ld/%ld", backspace, (unsigned char)100, blstatistics.mObjectCount, blstatistics.mObjectCount);
            printf("\n\n  done!\n");
            video_writer.release();
        }
        deinit_binlog_read();
    }
}


static void get_rectime(void) {
    GetSystemTime(&systemTime);
    sprintf(video_filename, "%s_%d%02d%02d_%02d%02d%02d%s",
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour + UTC,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTVIDEO);
    sprintf(binlog_filename_write, "%s_%d%02d%02d_%02d%02d%02d%s",
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour + UTC,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTBINLOG);
}
