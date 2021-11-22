#ifndef _UPDATEIMG_H_
#define _UPDATEIMG_H_

#include<opencv2/opencv.hpp>

#define RED   Scalar(0, 0, 255)
#define BLUE    Scalar(255, 0, 0)
#define BLACK  Scalar(0, 0, 0)
#define GRAY   Scalar(224,224,224)

#define XCOL 1600
#define YROW 1000

#define RO 88.8
#define FO 365.9
#define HW 95.3

#define LINSPACESTEP 50
#define LINSPACEMAXNUM 100

void init_axis(void);
void update_img(void);

#endif