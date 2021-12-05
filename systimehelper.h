#ifndef _SYSTIMEHELPER_H_
#define _SYSTIMEHELPER_H_

#include <windows.h>

typedef union TM_t {
    ULARGE_INTEGER li;
    FILETIME       ft;
} TM_u;

extern SYSTEMTIME systemTime, localTime;
extern FILETIME timeInSec;
extern TM_u TM;

void gen_name_with_rectime(void);

#endif
