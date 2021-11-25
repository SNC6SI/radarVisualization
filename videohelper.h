#ifndef _VIDEOHELPER_H_
#define _VIDEOHELPER_H_

#include <opencv2/opencv.hpp>

extern cv::Mat capframe[2];
extern cv::Mat recframe;
extern cv::Mat frames[3];

extern cv::VideoWriter writer;

void update_video(void);

#endif
