#ifndef _BINLOGHELPER_H_
#define _BINLOGHELPER_H_

#include <windows.h>
#include "binlog.h"

extern HANDLE hbinlogFile;
extern VBLCANFDMessage64 messageFD;
extern VBLCANMessage2 message2;
extern VBLFileStatisticsEx blstatistics;

extern int init_binlog_write(void);
extern void update_binlog_write();

extern int init_binlog_read(void);
extern int update_binlog_read(void);

extern void deinit_binlog(void);

#endif