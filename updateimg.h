#ifndef _UPDATEIMG_H_
#define _UPDATEIMG_H_

#include<opencv2/opencv.hpp>

#define BLUE   Scalar(0, 0, 255)
#define RED    Scalar(255, 0, 0)
#define BLACK  Scalar(0, 0, 0)
#define GRAY   Scalar(224,224,224)

#define XCOL 1600
#define YROW 1000
void update_img(void);

#endif