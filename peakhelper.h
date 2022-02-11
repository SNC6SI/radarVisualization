#ifndef _PEAKHELPER_H_
#define _PEAKHELPER_H_

#include <windows.h>
#include "PCANBasic.h"

//typedef XL_DRIVER_CONFIG  XLdriverConfig;
//typedef struct s_xl_driver_config {
//    unsigned int      dllVersion;
//    unsigned int      channelCount;  // total number of channels
//    unsigned int      reserved[10];
//    XLchannelConfig   channel[XL_CONFIG_MAX_CHANNELS];    // [channelCount]
//} XL_DRIVER_CONFIG;

#define PEAK_CONFIG_MAX_CHANNELS 2

typedef struct s_PEAK_channel_config {
	char                name[32];
	TPCANHandle         macro;
} PEAK_CHANNEL_CONFIG;

typedef PEAK_CHANNEL_CONFIG  PEAKchannelConfig;

typedef struct s_peak_driver_config {
	unsigned int        channelCount;
	unsigned int        reserved[3];
	PEAKchannelConfig   channel[PEAK_CONFIG_MAX_CHANNELS];
} PEAK_DRIVER_CONFIG;

typedef PEAK_DRIVER_CONFIG  PEAKdriverConfig;

extern PEAKdriverConfig g_peakDrvConfig;

extern TPCANMsgFD peakCANMsg;
extern TPCANTimestampFD peakCANTimeStamp;
extern TPCANTimestampFD peakCANTimeStampAnchor;

TPCANStatus peakInitDriver(void);
TPCANStatus peakOpenDriver(void);
TPCANStatus peakCreateRxThread(void);

#endif