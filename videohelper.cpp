#include <ctime>
#include <opencv2/opencv.hpp>
#include "rv_param.h"
#include "canvashelper.h"
#include "capturehelper.h"

#define VIDEONAMEPRE  "D:/rv"
#define VIDEONAMEPOST ".mp4"

using namespace cv;

Mat capframe[2];
Mat recframe(YROW, XCOL + CAM1_XCOL, CV_8UC3, Scalar(255, 255, 255));
Mat frames[3];

char video_filename[64];
VideoWriter writer;

void get_video_rectime(void) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    sprintf(video_filename, "%s_%d%02d%02d_%02d%02d%02d%s",
        VIDEONAMEPRE,
        ltm->tm_year + 1900,
        ltm->tm_mon + 1,
        ltm->tm_mday,
        ltm->tm_hour,
        ltm->tm_min,
        ltm->tm_sec,
        VIDEONAMEPOST);
}

void update_video(void) {
    frames[0] = recframe(Rect(0, 0, XCOL, YROW));
    canvas.copyTo(frames[0]);

    if (capOpened) {
        capture[0].read(capframe[0]);
        frames[1] = recframe(Rect(XCOL, 0, CAM1_XCOL, CAM1_YROW));
        capframe[0].copyTo(frames[1]);
        if (cameraSelected.size() == 2) {
            capture[1].read(capframe[1]);
            frames[2] = recframe(Rect(XCOL, CAM1_YROW, CAM1_XCOL, CAM1_YROW));
            capframe[1].copyTo(frames[2]);
        }
    }    
}