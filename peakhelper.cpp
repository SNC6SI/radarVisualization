#include <stdio.h>
#include "peakhelper.h"
#include "signalhelper.h"
#include "binloghelper.h"


static TPCANHandle channelsToCheck[2] = { PCAN_USBBUS1, PCAN_USBBUS2 };
static const char pcan_channel_name[2][32]  = { "PCAN USB Channel 1", "PCAN USB Channel 2" };
static DWORD condition; 

static LPSTR BitrateFD = const_cast<LPSTR>("f_clock_mhz=80, nom_brp=32, nom_tseg1=3, nom_tseg2=1, nom_sjw=1, data_brp=8, data_tseg1=3, data_tseg2=1, data_sjw=1");

PEAKdriverConfig g_peakDrvConfig;


const TPCANHandle PcanHandle = PCAN_USBBUS1;
HANDLE iBuffer = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE g_peakhRXThread;
int    g_peakRXCANThreadRun;

TPCANMsgFD peakCANMsg;
TPCANTimestampFD peakCANTimeStamp;
TPCANTimestampFD peakCANTimeStampAnchor;

extern unsigned int msgEdlFlag;


TPCANStatus peakInitDriver(void) {
	short ret = -1;
	g_peakDrvConfig.channelCount = 0U;
	for (int i = 0; i < sizeof(channelsToCheck)/sizeof(channelsToCheck[0]); i++) {
		if (CAN_GetValue(channelsToCheck[i], PCAN_CHANNEL_CONDITION, &condition, 4) == PCAN_ERROR_OK) {
			if ((condition & PCAN_CHANNEL_AVAILABLE) == PCAN_CHANNEL_AVAILABLE) {
				strcpy(g_peakDrvConfig.channel[g_peakDrvConfig.channelCount].name, pcan_channel_name[i]);
				g_peakDrvConfig.channel[g_peakDrvConfig.channelCount].macro = channelsToCheck[i];
				g_peakDrvConfig.channelCount++;
			}
		}	
	}
	ret = 0;
	return ret;
}


TPCANStatus peakOpenDriver(void) {
	TPCANStatus stsResult = PCAN_ERROR_UNKNOWN;
	stsResult = CAN_InitializeFD(PcanHandle, BitrateFD);
	return (stsResult);
}



static DWORD WINAPI peakRxCanFdThread(LPVOID par) {
	TPCANStatus   stsResult = PCAN_ERROR_UNKNOWN;
	g_peakRXCANThreadRun = 1;
	while (g_peakRXCANThreadRun) {
		WaitForSingleObject(iBuffer, 10);
		do { 
			TPCANStatus stsResult = CAN_ReadFD(PcanHandle, &peakCANMsg, &peakCANTimeStamp);
			if (stsResult == PCAN_ERROR_QRCVEMPTY) {
				break;
			}
			if (peakCANMsg.ID == 1) {
				peakCANTimeStampAnchor = peakCANTimeStamp * 1000;
				break;
			}
			memcpy(ptr, &(peakCANMsg.DATA[0]), 64);
			gcanid = peakCANMsg.ID;
			ts = peakCANTimeStamp * 1000 - peakCANTimeStampAnchor;
			msgEdlFlag = 1;
			update_sig();
			peak_update_binlog_write();
		} while (stsResult == PCAN_ERROR_OK);
	}
	CAN_Uninitialize(PCAN_NONEBUS);
	return(NO_ERROR);
}


TPCANStatus peakCreateRxThread(void) {
	TPCANStatus   stsResult = PCAN_ERROR_UNKNOWN;
	DWORD         ThreadId = 0;
	
	stsResult = CAN_SetValue(PcanHandle, PCAN_RECEIVE_EVENT, &iBuffer, sizeof(iBuffer));
	if (stsResult == PCAN_ERROR_OK) {
		stsResult = init_binlog_write();
	}
	if (stsResult == PCAN_ERROR_OK) {
		g_peakhRXThread = CreateThread(0, 0x1000, peakRxCanFdThread, (LPVOID)0, 0, &ThreadId);
	}

	return (stsResult);
}