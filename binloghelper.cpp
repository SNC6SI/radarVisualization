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
extern unsigned int msgEdlFlag;

HANDLE hbinlogFile;
VBLFileStatisticsEx blstatistics;
VBLCANFDMessage64 messageFD;
VBLCANMessage2 message2;
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

void update_binlog_write() {
    if (msgEdlFlag) {
        memset(&messageFD, 0, sizeof(VBLCANFDMessage64));

        messageFD.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
        messageFD.mHeader.mBase.mHeaderSize = sizeof(messageFD.mHeader);
        messageFD.mHeader.mBase.mHeaderVersion = 1;
        messageFD.mHeader.mBase.mObjectSize = sizeof(VBLCANFDMessage64);
        messageFD.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_FD_MESSAGE_64;
        messageFD.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
        messageFD.mHeader.mObjectTimeStamp = g_xlCanRxEvt.timeStampSync;

        messageFD.mChannel = g_xlCanRxEvt.channelIndex + 1;
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
    else {
        memset(&message2, 0, sizeof(VBLCANMessage2));
        message2.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
        message2.mHeader.mBase.mHeaderSize = sizeof(message2.mHeader);
        message2.mHeader.mBase.mHeaderVersion = 1;
        message2.mHeader.mBase.mObjectSize = sizeof(VBLCANMessage2);
        message2.mHeader.mBase.mObjectType = BL_OBJ_TYPE_CAN_MESSAGE2;
        message2.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
        message2.mHeader.mObjectTimeStamp = g_xlCanRxEvt.timeStampSync;

        message2.mChannel = g_xlCanRxEvt.channelIndex + 1;
        message2.mFlags = 0;
        message2.mDLC = g_xlCanRxEvt.tagData.canRxOkMsg.dlc;
        message2.mID = g_xlCanRxEvt.tagData.canRxOkMsg.canId;
        memcpy(message2.mData, g_xlCanRxEvt.tagData.canRxOkMsg.data, 8);
        BLWriteObject(hbinlogFile, &message2.mHeader.mBase);
    }
    
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


int update_binlog_read(void) {
    if (blSuccess && BLPeekObject(hbinlogFile, &blObjHeaderbase)) {
        switch (blObjHeaderbase.mObjectType) {
            case BL_OBJ_TYPE_CAN_FD_MESSAGE_64:
                messageFD.mHeader.mBase = blObjHeaderbase;
                blSuccess = BLReadObjectSecure(hbinlogFile, &messageFD.mHeader.mBase, sizeof(messageFD));
                if (blSuccess) {
                    BLFreeObject(hbinlogFile, &messageFD.mHeader.mBase);
                }
                msgEdlFlag = 1;
                break;
            case BL_OBJ_TYPE_CAN_MESSAGE2:
                message2.mHeader.mBase = blObjHeaderbase;
                blSuccess = BLReadObjectSecure(hbinlogFile, &message2.mHeader.mBase, sizeof(message2));
                if (blSuccess) {
                    BLFreeObject(hbinlogFile, &message2.mHeader.mBase);
                }
                msgEdlFlag = 0;
                break;
            default:
                blSuccess = BLSkipObject(hbinlogFile, &blObjHeaderbase);
                break;
        }
        return 0;
    }
    else {
        return -1;
    }
}


void deinit_binlog(void) {
    BLCloseHandle(hbinlogFile);
}