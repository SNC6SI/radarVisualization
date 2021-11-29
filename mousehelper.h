#ifndef _MOUSEHELPER_H_
#define _MOUSEHELPER_H_

extern unsigned char LBUTTONDOWN_flg;
extern int x_anno, y_anno;

void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata);

#endif