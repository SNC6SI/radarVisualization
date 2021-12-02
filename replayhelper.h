#ifndef _REPLAYHELPER_H_
#define _REPLAYHELPER_H_

extern int gReplayCANThreadRun;
extern unsigned long greadcnt;
extern HANDLE g_hEvent;

extern int ReplayCreateRxThread(void);

#endif