#ifndef _BINLOGHELPER_H_
#define _BINLOGHELPER_H_

#include <windows.h>
#include "binlog.h"

extern HANDLE hbinlogFile;
extern VBLCANFDMessage64 messageFD;

extern int init_binlog(void);
extern void update_binlog(void);
extern void deinit_binlog(void);

#endif