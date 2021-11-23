#ifndef _RV_COMMON_
#define _RV_COMMON_

#ifdef RV_DEBUG
#define RV_PRINTF(f_, ...) printf((f_), ##__VA_ARGS__)
#else
#define RV_PRINTF(f_, ...)
#endif

#endif
