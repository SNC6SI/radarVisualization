#include <opencv2/opencv.hpp>
#include "rv_param.h"
#include "canvashelper.h"
#include "capturehelper.h"

using namespace cv;

Mat capframe[2];
Mat recframe(YROW, XCOL + CAM1_XCOL, CV_8UC3, Scalar(255, 255, 255));
Mat frames[3];

VideoWriter video_writer;

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