#ifndef _VIDEOHELPER_H_
#define _VIDEOHELPER_H_

#include <opencv2/opencv.hpp>

extern cv::Mat capframe[2];
extern cv::Mat recframe, recframe_offline;
extern cv::Mat frames[3];

extern cv::VideoWriter video_writer;

void update_video_online(void);
void update_video_offline(void);

#endif
