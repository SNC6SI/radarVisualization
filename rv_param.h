#ifndef _RV_PARAM_H_
#define _RV_PARAM_H_

#include <opencv2/opencv.hpp>
extern float gScale;

#define CONSOLE_COLOR() system("color F0")

#define RED     Scalar(0, 0, 255)
#define BLUE    Scalar(255, 0, 0)
#define BLACK   Scalar(0, 0, 0)
#define GRAY    Scalar(224,224,224)
#define DIMGREY Scalar(105,105,105)
#define WHITE   Scalar(255,255,255)
#define GREEN   Scalar(0,255,0)

#define Purple  Scalar(240, 32, 160)
#define Magenta Scalar(255, 0, 255)

#define BLUEH   BLUE                     // 1
#define BLUEL   Magenta  //Scalar(255, 144, 30)     // 0
#define BLUET   DIMGREY //Scalar(255, 206, 135)    // 2
#define BLUEU   Scalar(255, 226, 198)    // 3

#define GREENDARK Scalar(0, 100, 0)
#define GREENDIM  Scalar(50, 205, 50)
#define GREENPALE Scalar(152, 251, 152)

#define SlateGray1 Scalar(255, 226, 198)
#define LightBlue1 Scalar(255, 239, 191)
#define LightYellow2 Scalar(209, 238, 238)

#define OrangeRed1 Scalar(0, 69, 255)
#define ORANGE Scalar(0, 165, 255)
#define YELLOW Scalar(0, 255, 255)

#define Chocolate Scalar(30, 105, 210)

#define XCOL 1200
#define YROW 1000

#define YOFFSET -135

#define CAM1_XCOL 640
#define CAM1_YROW 480

#define DEFAULTSCALE  0.35
#define SCALESTEP     0.01
#define ORIGINSTEP    5

#define RO_ 88.8
#define FO_ 365.9
#define HW_ 95.3
#define GAP_ 50.0
#define SP_  20.0
#define AG_  40.0

#define RO (88.8 * gScale)
#define FO (365.9 * gScale)
#define HW (95.3 * gScale)

#define LINSPACESTEP 50
#define LINSPACEMAXNUM 100

#define TM_0x121 400
#define TM_0x171 400
#define TM_0x150 400
#define TM_0x172 400

#define DE_LIM 20

#endif