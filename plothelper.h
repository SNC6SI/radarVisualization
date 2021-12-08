#ifndef _UPDATEIMG_H_
#define _UPDATEIMG_H_

extern cv::Mat canvas;

void init_axis(void);
void restore_axis(void);
void toggle_de_status(void);
void toggle_ps_status(void);
void update_img(void);

void point2pose(float* x, float* y, int iter);

#endif