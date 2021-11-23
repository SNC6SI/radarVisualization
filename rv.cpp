#if defined(_Windows) || defined(_MSC_VER) || defined (__GNUC__)
 #define  STRICT
 #include <windows.h>
#endif

#include <stdio.h>

#define UNUSED_PARAM(a) { a=a; }

#include "rv_common.h"
#include "vxlapi.h"
#include "updatesig.h"
#include "updateimg.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

char            g_AppName[XL_MAX_LENGTH+1]  = "radarVisulization";
XLportHandle    g_xlPortHandle              = XL_INVALID_PORTHANDLE;
XLdriverConfig  g_xlDrvConfig;
XLaccess        g_xlChannelMask             = 0;
XLaccess        g_xlPermissionMask          = 0;
unsigned int    g_BaudRate                  = 500000;

XLhandle        g_hMsgEvent;
HANDLE          g_hRXThread; 
int             g_RXCANThreadRun;

Mat canvas(YROW, XCOL, CV_8UC3, Scalar(255, 255, 255));



XLstatus rvInitDriver(XLaccess *pxlChannelMaskTx, unsigned int *pxlChannelIndex) {
    XLstatus          xlStatus;

    xlStatus = xlOpenDriver ();

    if(XL_SUCCESS == xlStatus) {
        xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus) {
        g_xlChannelMask   = 1;
        g_xlPermissionMask = g_xlChannelMask;
        *pxlChannelMaskTx = 1;
        *pxlChannelIndex  = 0;
    }

    if(XL_SUCCESS == xlStatus) {
        // CAN FD
        xlStatus = xlOpenPort(&g_xlPortHandle, g_AppName, g_xlChannelMask, &g_xlPermissionMask, 16000, XL_INTERFACE_VERSION_V4, XL_BUS_TYPE_CAN);
    }

    if ( (XL_SUCCESS == xlStatus) && (XL_INVALID_PORTHANDLE != g_xlPortHandle) ) {

        if (g_xlChannelMask == g_xlPermissionMask) {
                XLcanFdConf fdParams;
                memset(&fdParams, 0, sizeof(fdParams));
                
                // arbitration bitrate
                fdParams.arbitrationBitRate = 500000;
                fdParams.tseg1Abr           = 3;
                fdParams.tseg2Abr           = 1;
                fdParams.sjwAbr             = 1;

                // data bitrate
                fdParams.dataBitRate = 2000000;
                fdParams.tseg1Dbr    = 15;
                fdParams.tseg2Dbr    = 4;
                fdParams.sjwDbr      = 4;

                xlStatus = xlCanFdSetConfiguration(g_xlPortHandle, g_xlChannelMask, &fdParams);
        } else {
            printf("NO init access!\n");
        }
    } else {
        xlClosePort(g_xlPortHandle);
        g_xlPortHandle = XL_INVALID_PORTHANDLE;
        xlStatus = XL_ERROR;
    }
    return xlStatus;
}

DWORD WINAPI RxCanFdThread(LPVOID par)
{
    XLstatus        xlStatus = XL_SUCCESS;
    // DWORD           rc;
    XLcanRxEvent    xlCanRxEvt;
    
    UNUSED_PARAM(par); 

    g_RXCANThreadRun = 1;
    
    while (g_RXCANThreadRun) {
        /*rc = WaitForSingleObject(g_hMsgEvent, 10);
        if(rc != WAIT_OBJECT_0) continue;*/
        WaitForSingleObject(g_hMsgEvent, 10);
        
        do {
            xlStatus = xlCanReceive(g_xlPortHandle, &xlCanRxEvt);
#if 0
             printf("%lld,%lX,%ld\t%X %X %X %X %X %X %X %X\n",
                    xlCanRxEvt.timeStampSync,
                    xlCanRxEvt.tagData.canRxOkMsg.canId,
                    xlCanRxEvt.tagData.canRxOkMsg.dlc,
                    xlCanRxEvt.tagData.canRxOkMsg.data[0],
                    xlCanRxEvt.tagData.canRxOkMsg.data[1],
                    xlCanRxEvt.tagData.canRxOkMsg.data[2],
                    xlCanRxEvt.tagData.canRxOkMsg.data[3],
                    xlCanRxEvt.tagData.canRxOkMsg.data[4],
                    xlCanRxEvt.tagData.canRxOkMsg.data[5],
                    xlCanRxEvt.tagData.canRxOkMsg.data[6],
                    xlCanRxEvt.tagData.canRxOkMsg.data[7]);
#endif
            if(xlStatus==XL_ERR_QUEUE_IS_EMPTY ) {
                break;
            }
            memcpy(ptr, &(xlCanRxEvt.tagData.canRxOkMsg.data), 64);
            gcanid = xlCanRxEvt.tagData.canRxOkMsg.canId;
            ts = xlCanRxEvt.timeStampSync;
            update_sig();
        } while(XL_SUCCESS == xlStatus);
    }
    return(NO_ERROR); 
}

VideoCapture cap1;
VideoCapture cap2;
Mat cap1frame, cap2frame;
int capOpened;

Mat recframe(YROW, XCOL + CAM1_XCOL, CV_8UC3, Scalar(255, 255, 255));
Mat r_l, r_r1, r_r2;

int myFourCC = VideoWriter::fourcc('m', 'p', '4', 'v');;
Size recSize = Size(XCOL + CAM1_XCOL, YROW);
VideoWriter writer("D:/hello.mp4", myFourCC, 25, recSize, true);

XLstatus rvCreateRxThread(void) {
    XLstatus      xlStatus = XL_ERROR;
    DWORD         ThreadId = 0;

    if (g_xlPortHandle != XL_INVALID_PORTHANDLE) {
        xlStatus = xlSetNotification(g_xlPortHandle, &g_hMsgEvent, 1);
        g_hRXThread = CreateThread(0, 0x1000, RxCanFdThread, (LPVOID)0, 0, &ThreadId);
    }
    return xlStatus;
}

int main(int argc, char *argv[]) {
    XLstatus      xlStatus;
    XLaccess      xlChanMaskTx = 0;
    unsigned int  xlChanIndex = 0;
    int           activated = 0;

    xlStatus = rvInitDriver(&xlChanMaskTx, &xlChanIndex);

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
    /*cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);*/
    cap1.open(0, CAP_DSHOW);
    cap2.open(2, CAP_DSHOW);
    if (!cap1.isOpened() || !cap2.isOpened()) {
        capOpened = 0;
    }
    else {
        capOpened = 1;
    }

    //imshow("radar visualization", canvas);
    moveWindow("radar visualization", -15, 0);
    //cap >> capframe;
    //imshow("camera", capframe);
    moveWindow("camera", -15 + XCOL, 0);

    while (waitKey(40) != 27) {
        update_img();
        //imshow("radar visualization", canvas);
        if (capOpened) {
            
            r_l = recframe(Rect(0, 0, XCOL, YROW));
            canvas.copyTo(r_l);

            cap1 >> cap1frame;
            //imshow("camera", capframe);
            r_r1 = recframe(Rect(XCOL, 0, CAM1_XCOL, CAM1_YROW));
            cap1frame.copyTo(r_r1);

            cap2 >> cap2frame;
            r_r2 = recframe(Rect(XCOL, CAM1_YROW, CAM1_XCOL, CAM1_YROW));
            cap2frame.copyTo(r_r2);

            imshow("recframe", recframe);
            writer.write(recframe);
        }
    }
    cap1.release();
    cap2.release();
    writer.release();
}