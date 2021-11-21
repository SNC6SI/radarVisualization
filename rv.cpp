#if defined(_Windows) || defined(_MSC_VER) || defined (__GNUC__)
 #define  STRICT
 #include <windows.h>
#endif

#include <stdio.h>

#define UNUSED_PARAM(a) { a=a; }

#include "vxlapi.h"
#include "updatesig.h"
#include<opencv2/opencv.hpp>
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
            //ptr = &(xlCanRxEvt.tagData.canRxOkMsg.data);
            memcpy(ptr, &(xlCanRxEvt.tagData.canRxOkMsg.data), 64);
            gcanid = xlCanRxEvt.tagData.canRxOkMsg.canId;
            update_sig();
        } while(XL_SUCCESS == xlStatus);
    }
    return(NO_ERROR); 
}

XLstatus rvCreateRxThread(void) {
    XLstatus      xlStatus = XL_ERROR;
    DWORD         ThreadId = 0;

    if (g_xlPortHandle != XL_INVALID_PORTHANDLE) {
        xlStatus = xlSetNotification(g_xlPortHandle, &g_hMsgEvent, 1);
        g_hRXThread = CreateThread(0, 0x1000, RxCanFdThread, (LPVOID)0, 0, &ThreadId);
    }
    return xlStatus;
}

#define w 400
void MyEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    ellipse(img,
        Point(w / 2, w / 2),
        Size(w / 4, w / 16),
        angle,
        0,
        360,
        Scalar(255, 0, 0),
        thickness,
        lineType);
}
void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        w / 32,
        Scalar(0, 0, 255),
        FILLED,
        LINE_8);
}

void MyRectangle(Mat img, Point pt1, Point pt2) {
    rectangle(img,
        pt1,
        pt2,
        Scalar(0, 0, 255),
        1,
        LINE_8,
        0
    );
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


    unsigned int i=0;
    Mat bg(900, 900, CV_8UC3, Scalar(255, 255, 255));
    imshow("test", bg);
    while (waitKey(10) != 27) {
        bg.setTo(cv::Scalar::all(255));
        MyRectangle(bg, Point(0+i, 0+i), Point(200+i,450+i));
        i++;
        imshow("test", bg);
        
    }

}