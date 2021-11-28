#define _CRT_SECURE_NO_WARNINGS

#include <tchar.h>
#include <stdio.h>
#define STRICT
#include <windows.h>
#include "binlog.h"
#include "vectorhelper.h"
#include "dialoghelper.h"
#include "systimehelper.h"

extern char binlog_filename_write[512];
extern char binlog_filename_read[512];

HANDLE hbinlogFile;
VBLFileStatisticsEx blstatistics;
VBLCANFDMessage64 messageFD;
VBLObjectHeaderBase blObjHeaderbase;
BOOL blSuccess;

int init_binlog_write(void) {
    BOOL bSuccess;
    hbinlogFile = BLCreateFile(binlog_filename_write, GENERIC_WRITE);
    if (INVALID_HANDLE_VALUE == hbinlogFile) {
        return -1;
    }
    BLSetApplication(hbinlogFile, BL_APPID_CANCASEXLLOG, 1, 0, 1);
    BLSetMeasurementStartTime(hbinlogFile, &systemTime);
    BLSetWriteOptions(hbinlogFile, 6, 0);
    return 0;
}

static const BYTE dlcMapping[17] = {0,1,2,3,4,5,6,7,8,12,16,20,24,32,48,64};

void update_binlog_write(void) {
    memset(&messageFD, 0, sizeof(VBLCANFDMessage64));

    messageFD.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    messageFD.mHeader.mBase.mHeaderSize = sizeof(messageFD.mHeader);
    messageFD.mHeader.mBase.mHeaderVersion = 1;
    messageFD.mHeader.mBase.mObjectSize = sizeof(VBLCANFDMessage64);
    messageFD.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_FD_MESSAGE_64;
    messageFD.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    messageFD.mHeader.mObjectTimeStamp = g_xlCanRxEvt.timeStampSync;

    messageFD.mChannel = 1;
    messageFD.mFlags = (BYTE)(0x01) << 12;
    messageFD.mDLC = g_xlCanRxEvt.tagData.canRxOkMsg.dlc;
    if (messageFD.mDLC >= 0 && messageFD.mDLC < 17) {
        messageFD.mValidDataBytes = dlcMapping[messageFD.mDLC];
    }
    else {
        messageFD.mValidDataBytes = 32;
    }
    messageFD.mID = g_xlCanRxEvt.tagData.canRxOkMsg.canId;
    memcpy(messageFD.mData, g_xlCanRxEvt.tagData.canRxOkMsg.data, 64);

    BLWriteObject(hbinlogFile, &messageFD.mHeader.mBase);
}


int init_binlog_read(void) {
    hbinlogFile = BLCreateFile(binlog_filename_read, GENERIC_READ);
    if (INVALID_HANDLE_VALUE == hbinlogFile) {
        return -1;
    }
    blstatistics = {sizeof(VBLFileStatisticsEx)};
    BLGetFileStatisticsEx(hbinlogFile, &blstatistics);
    SystemTimeToFileTime(&blstatistics.mMeasurementStartTime, &timeInSec);
    blSuccess = TRUE;
    return 0;
}


void update_binlog_read(void) {
    if (blSuccess && BLPeekObject(hbinlogFile, &blObjHeaderbase)) {
        switch (blObjHeaderbase.mObjectType) {
            case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
                messageFD.mHeader.mBase = blObjHeaderbase;
                blSuccess = BLReadObjectSecure(hbinlogFile, &messageFD.mHeader.mBase, sizeof(messageFD));
                if (blSuccess) {
                    BLFreeObject(hbinlogFile, &messageFD.mHeader.mBase);
                }
                break;
            default:
                blSuccess = BLSkipObject(hbinlogFile, &blObjHeaderbase);
                break;
        }
    }
}


void deinit_binlog(void) {
    BLCloseHandle(hbinlogFile);
}