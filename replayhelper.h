#ifndef _REPLAYHELPER_H_
#define _REPLAYHELPER_H_


extern int gReplayCANThreadRun;
extern unsigned long greadcnt;
extern HANDLE g_hEvent;


extern int update_sig_interval_wrapper(void);
extern int CreateReplayThread(void);
extern void prepareVideoFileName(void);


extern void initProgreassPercent(void);
extern void queryProgressPercent(void);
extern void deinit_progressPercent(void);


#endif