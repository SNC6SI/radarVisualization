#ifndef _VIDEOHELPER_H_
#define _VIDEOHELPER_H_

#include <opencv2/opencv.hpp>

extern cv::Mat capframe[2];
extern cv::Mat recframe;
extern cv::Mat frames[3];

extern cv::VideoWriter writer;
extern char video_filename[64];

void get_video_rectime(void);
void update_video(void);

#endif
