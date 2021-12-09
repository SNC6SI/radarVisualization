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


using namespace std;
using namespace cv;

char record_folder[512];
int record_folder_len;
char video_filename[512];
char binlog_filename_write[512];
char binlog_filename_read[512];
vector<string> binlog_filename_read_list;
int binlog_filename_read_len;
vector<int> binlog_filename_read_len_list;
DWORD num_binlog_files;
static int KEYPressed = 0xFFFF;
unsigned int msgEdlFlag;
static void online_mode(void);
static void offline_mode(void);


int main(int argc, char* argv[]) {
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_WARNING);
    select_mode();
    init_measure_status();
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
    BasicFolderOpenSingle();
    gen_name_with_rectime();
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
    video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), FPS, Size(XCOL + CAM1_XCOL, YROW), true);

    while ((KEYPressed = waitKey(WAITMS)) != KEY_ESC) {
        if (KEYPressed == KEY_SPACE) {
            restore_axis();
        }
        if ((KEYPressed == KEY_D) || (KEYPressed == KEY_d)) {
            toggle_de_status();
        }
        if ((KEYPressed == KEY_W) || (KEYPressed == KEY_w)) {
            toggle_ps_status();
        }
        if ((KEYPressed == KEY_M) || (KEYPressed == KEY_m)) {
            toggle_measure_status();
        }
        check_timeout();
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
    int status = -1;;
    gReplayCANThreadRun = 1;
    select_offline_mode();
    initProgreassPercent();
    if (selected_offline_mode == 1) {
        select_offline_display_mode();
        greadcnt = 0;
        init_sig();
        init_axis();
        BasicFileOpenSingle();
        if (selected_offline_display_mode == 2) {
            prepareVideoFileName();
            video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), FPS, Size(XCOL, YROW), true);
        }
        moveWindow("radar visualization offline", -15, 0);
        imshow("radar visualization offline", recframe_offline);
        setMouseCallback("radar visualization offline", mouseCallBackFunc, NULL);
        CreateReplayThread();
        while ((KEYPressed = waitKey(WAITMS)) != KEY_ESC) {
            if (KEYPressed == KEY_SPACE) {
                restore_axis();
            }
            if (KEYPressed == KEY_ENTER) {
                toggle_pause_status();
            }
            if ((KEYPressed == KEY_D) || (KEYPressed == KEY_d)) {
                toggle_de_status();
            }
            if ((KEYPressed == KEY_W) || (KEYPressed == KEY_w)) {
                toggle_ps_status();
            }
            if ((KEYPressed == KEY_M) || (KEYPressed == KEY_m)) {
                toggle_measure_status();
            }
            if ((KEYPressed == KEY_F) || (KEYPressed == KEY_f)) {
                push_fast_forward();
            }
            check_timeout();
            update_img();
            update_video_offline();
            imshow("radar visualization offline", recframe_offline);
            if (selected_offline_display_mode == 2) {
                video_writer.write(recframe_offline);
            }
            queryProgressPercentDisplay();
            if (gReplayCANThreadRun) {
                if (!query_pause_status()) {
                    SetEvent(g_hEvent);
                }
                else {
                    update_sig();
                }
            }
            else {
                break;
            }
        }
        g_RXCANThreadRun = 0;
    }
    else if (selected_offline_mode == 2) {
        init_sig();
        init_axis();
        BasicFileOpenMulti();
        for (int i = 0; i < num_binlog_files; i++) {
            greadcnt = 0;
            memset(binlog_filename_read, 0, sizeof(binlog_filename_read));
            binlog_filename_read_list[i].copy(binlog_filename_read, binlog_filename_read_list[i].length(), 0);
            binlog_filename_read_len = binlog_filename_read_len_list[i];
            prepareVideoFileName();
            video_writer.open(video_filename, VideoWriter::fourcc('m', 'p', '4', 'v'), FPS, Size(XCOL, YROW), true);
            status = init_binlog_read();
            if (status == 0) {
                while (1) {
                    status = update_sig_interval_wrapper();
                    if (status == NO_ERROR) {
                        check_timeout();
                        update_img();
                        update_video_offline();
                        video_writer.write(recframe_offline);
                        queryProgressPercentSilent();
                    }
                    else {
                        deinit_progressPercent();
                        break;
                    }
                }
            }
        }
    }
    video_writer.release();
    deinit_binlog();
}