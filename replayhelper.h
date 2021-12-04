#ifndef _REPLAYHELPER_H_
#define _REPLAYHELPER_H_

extern int gPauseStatus;
extern int gReplayCANThreadRun;
extern unsigned long greadcnt;
extern char greadcnt_fraction[512];
extern HANDLE g_hEvent;


extern int update_sig_interval_wrapper(void);
extern int CreateReplayThread(void);
extern void prepareVideoFileName(void);


extern void initProgreassPercent(void);
extern void queryProgressPercentSilent(void);
extern void queryProgressPercentDisplay(void);
extern void deinit_progressPercent(void);

extern void toggle_pause_status(void);
extern int query_pause_status(void);


#endif