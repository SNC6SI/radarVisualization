#include "rv_common.h"
#include "rv_param.h"
#include "menuhelper.h"
#include "dialoghelper.h"
#include "capturehelper.h"
#include "vectorhelper.h"
#include "binloghelper.h"
#include "replayhelper.h"
#include "videohelper.h"
#include "signalhelper.h"
#include "plothelper.h"
#include "mousehelper.h"
#include "systimehelper.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>


using namespace cv;
static char backspace[256];
char video_filename[512];
char binlog_filename_write[512];
char binlog_filename_read[512];
int binlog_filename_read_len;
static int KEYPressed = 0xFFFF;
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
    imshow("radar visualization online", recframe);
    setMouseCallback("radar visualization online", mouseCallBackFunc, NULL);
    video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), 25, Size(XCOL + CAM1_XCOL, YROW), true);

    while ((KEYPressed = waitKey(40)) != KEY_ESC) {
        if (KEYPressed == KEY_SPACE) {
            restore_axis();
        }
        update_img();
        update_video_online();
        imshow("radar visualization online", recframe);
        video_writer.write(recframe);
    }
    video_writer.release();
    deinit_capture();
    deinit_binlog();
}


static void offline_mode(void) {
    double percent = 0;
    double percent_anchor = 0;
    gReplayCANThreadRun = 1;
    BasicFileOpen();
    init_sig();
    init_axis();
    prepareVideoFileName();
    video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), 25, Size(XCOL, YROW), true);
    moveWindow("radar visualization offline", -15, 0);
    imshow("radar visualization offline", recframe_offline);
    setMouseCallback("radar visualization offline", mouseCallBackFunc, NULL);
    ReplayCreateRxThread();
    while ((KEYPressed = waitKey(40)) != KEY_ESC) {
        if (KEYPressed == KEY_SPACE) {
            restore_axis();
        }
        update_img();
        update_video_offline();
        imshow("radar visualization offline", recframe_offline);
        video_writer.write(recframe_offline);
        percent = (double)greadcnt / (double)blstatistics.mObjectCount * 100;
        if (percent - percent_anchor > 1) {
            percent_anchor = percent;
            printf("%s %3d.0%%  %10ld/%ld", backspace, (unsigned char)percent, greadcnt, blstatistics.mObjectCount);
        }
        if (gReplayCANThreadRun) {
            SetEvent(g_hEvent);
        }
        else {
            break;
        }
    }
    g_RXCANThreadRun = 0;
    video_writer.release();
    printf("%s  %3d.0%%  %10ld/%ld\n\n  done!\n", backspace, (unsigned char)100, blstatistics.mObjectCount, blstatistics.mObjectCount);
    deinit_binlog();
}