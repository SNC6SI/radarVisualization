#ifndef _RV_PARAM_H_
#define _RV_PARAM_H_

#include <opencv2/opencv.hpp>
extern float gScale;

#define RED     Scalar(0, 0, 255)
#define BLUE    Scalar(255, 0, 0)
#define BLACK   Scalar(0, 0, 0)
#define GRAY    Scalar(224,224,224)
#define DIMGREY Scalar(105,105,105)

#define BLUEH   BLUE                     // 1
#define BLUEL   Scalar(255, 144, 30)     // 0
#define BLUET   Scalar(255, 260, 135)    // 2
#define BLUEU   Scalar(255, 226, 198)    // 3

#define XCOL 1200
#define YROW 1000

#define CAM1_XCOL 640
#define CAM1_YROW 480

#define DEFAULTSCALE  0.5
#define SCALESTEP     0.01
#define ORIGINSTEP    5

#define RO (88.8 * gScale)
#define FO (365.9 * gScale)
#define HW (95.3 * gScale)

#define LINSPACESTEP 50
#define LINSPACEMAXNUM 100

#endif