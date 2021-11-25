#include "rv_common.h"
#include "rv_param.h"
#include "menuhelper.h"
#include "capturehelper.h"
#include "vectorhelper.h"
#include "videohelper.h"
#include "signalhelper.h"
#include "canvashelper.h"
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
SYSTEMTIME systemTime;
char video_filename[64];
char binlog_datetime[64];
void get_rectime(void);

int main(int argc, char *argv[]) {
    XLstatus      xlStatus;
    int           activated = 0;
    rv_status     rvStatus;
    

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
    get_rectime();
    
    moveWindow("radar visualization", -15, 0);
    writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), 25, Size(XCOL + CAM1_XCOL, YROW), true);

    while (waitKey(40) != KEY_ESC) {
        update_img();
        update_video();
        imshow("radar visualization", recframe);
        writer.write(recframe);
    }
    deinit_capture();
    writer.release();
}



void get_rectime(void) {
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
    sprintf(binlog_datetime, "%s_%d%02d%02d_%02d%02d%02d%s",
        FILENAMEPRE,
        systemTime.wYear,
        systemTime.wMonth,
        systemTime.wDay,
        systemTime.wHour + UTC,
        systemTime.wMinute,
        systemTime.wSecond,
        FILENAMEPOSTBINLOG);
}


