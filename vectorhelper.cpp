#include "vectorhelper.h"
#include "rv_common.h"
#include "signalhelper.h"
#include "binloghelper.h"

char            g_AppName[XL_MAX_LENGTH + 1] = "radarVisulization";
XLportHandle    g_xlPortHandle = XL_INVALID_PORTHANDLE;
XLdriverConfig  g_xlDrvConfig;
XLaccess        g_xlChannelMask = 0;
XLaccess        g_xlPermissionMask = 0;
XLcanRxEvent    g_xlCanRxEvt;

XLhandle        g_hMsgEvent;
HANDLE          g_hRXThread;
int             g_RXCANThreadRun;

extern unsigned int msgEdlFlag;


XLstatus rvInitDriver() {
    XLstatus          xlStatus;
    xlStatus = xlOpenDriver();
    if (XL_SUCCESS == xlStatus) {
        xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }
    return xlStatus;
}

XLstatus rvOpenDriver() {
    XLstatus          xlStatus;
    g_xlPermissionMask = g_xlChannelMask;
    // CAN FD
    xlStatus = xlOpenPort(&g_xlPortHandle, g_AppName, g_xlChannelMask, &g_xlPermissionMask, 16000, XL_INTERFACE_VERSION_V4, XL_BUS_TYPE_CAN);
    if ((XL_SUCCESS == xlStatus) && (XL_INVALID_PORTHANDLE != g_xlPortHandle)) {
        //if (g_xlChannelMask == g_xlPermissionMask) {
        XLcanFdConf fdParams;
        memset(&fdParams, 0, sizeof(fdParams));
        // arbitration bitrate
        fdParams.arbitrationBitRate = 500000;
        fdParams.tseg1Abr = 3;
        fdParams.tseg2Abr = 1;
        fdParams.sjwAbr = 1;
        // data bitrate
        fdParams.dataBitRate = 2000000;
        fdParams.tseg1Dbr = 15;
        fdParams.tseg2Dbr = 4;
        fdParams.sjwDbr = 4;
        xlStatus = xlCanFdSetConfiguration(g_xlPortHandle, g_xlPermissionMask, &fdParams);
        //}
        //else {
            //printf("NO init access!\n");
        //}
    }
    else {
        xlClosePort(g_xlPortHandle);
        g_xlPortHandle = XL_INVALID_PORTHANDLE;
        xlStatus = XL_ERROR;
    }
    return xlStatus;
}

static DWORD WINAPI RxCanFdThread(LPVOID par) {
    XLstatus        xlStatus = XL_SUCCESS;
    g_RXCANThreadRun = 1;
    while (g_RXCANThreadRun) {
        WaitForSingleObject(g_hMsgEvent, 10);
        do {
            xlStatus = xlCanReceive(g_xlPortHandle, &g_xlCanRxEvt);
            if (xlStatus == XL_ERR_QUEUE_IS_EMPTY) {
                break;
            }
            memcpy(ptr, &(g_xlCanRxEvt.tagData.canRxOkMsg.data), 64);
            gcanid = g_xlCanRxEvt.tagData.canRxOkMsg.canId;
            ts = g_xlCanRxEvt.timeStampSync;
            msgEdlFlag = (g_xlCanRxEvt.tagData.canRxOkMsg.msgFlags & XL_CAN_RXMSG_FLAG_EDL);
            // printf("0x%X, %d\n", gcanid, msgEdlFlag);
            update_sig();
            update_binlog_write();
        } while (XL_SUCCESS == xlStatus);
    }
    xlClosePort(g_xlPortHandle);
    g_xlPortHandle = XL_INVALID_PORTHANDLE;
    return(NO_ERROR);
}

XLstatus rvCreateRxThread(void) {
    XLstatus      xlStatus = XL_ERROR;
    DWORD         ThreadId = 0;
    if (g_xlPortHandle != XL_INVALID_PORTHANDLE) {
        xlStatus = xlSetNotification(g_xlPortHandle, &g_hMsgEvent, 1);
        if (xlStatus == XL_SUCCESS) {
            xlStatus = init_binlog_write();
        }
        if (xlStatus == XL_SUCCESS) {
            g_hRXThread = CreateThread(0, 0x1000, RxCanFdThread, (LPVOID)0, 0, &ThreadId);
        }
    }
    return xlStatus;
}