#ifndef _VECTORHELPER_H_
#define _VECTORHELPER_H_

#if defined(_Windows) || defined(_MSC_VER) || defined (__GNUC__)
#define  STRICT
#include <windows.h>
#endif

#include "vxlapi.h"


extern char            g_AppName[XL_MAX_LENGTH + 1];
extern XLportHandle    g_xlPortHandle;
extern XLdriverConfig  g_xlDrvConfig;
extern XLaccess        g_xlChannelMask;
extern XLaccess        g_xlPermissionMask;

extern XLhandle        g_hMsgEvent;
extern HANDLE          g_hRXThread;
extern int             g_RXCANThreadRun;


extern XLstatus rvInitDriver();
extern XLstatus rvOpenDriver();
extern XLstatus rvCreateRxThread(void);

#endif