#ifndef _MOUSEHELPER_H_
#define _MOUSEHELPER_H_

extern unsigned char LBUTTONDOWN_flg;
extern int x_anno, y_anno;
extern std::vector<float> x_meas_label, y_meas_label;

void init_measure_status(void);
void toggle_measure_status(void);
int query_measure_status(void);
int query_measure_data_size(void);

void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata);

#endif