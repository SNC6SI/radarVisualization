#ifndef _BINLOGHELPER_H_
#define _BINLOGHELPER_H_

#include <windows.h>
#include "binlog.h"

extern HANDLE hbinlogFile;
extern VBLCANFDMessage64 messageFD;
extern VBLFileStatisticsEx blstatistics;

extern int init_binlog_write(void);
extern void update_binlog_write(void);
extern void deinit_binlog_write(void);

extern int init_binlog_read(void);
extern void update_binlog_read(void);
extern void deinit_binlog_read(void);

#endif