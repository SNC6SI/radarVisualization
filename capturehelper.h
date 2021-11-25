#ifndef _CAPTUREHELPER_H_
#define _CAPTUREHELPER_H_

#include <vector>
#include <iostream>
#include "dshow.h"
#include <opencv2/opencv.hpp>
#include "rv_common.h"

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "quartz.lib")

extern std::vector<std::string> cameraList;
extern std::vector<int> cameraSelected;
rv_status query_camera();

extern cv::VideoCapture capture[2];

extern int capOpened;

void init_capture(void);
void deinit_capture(void);

#endif