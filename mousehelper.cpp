#include <iostream>
#include <opencv2/opencv.hpp>
#include "rv_param.h"

using namespace std;
using namespace cv;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEWHEEL) {
        if (sgn(flags) > 0) {
            //printf("zoom out\n");
            gScale -= SCALESTEP;
        }
        else if (sgn(flags) < 0) {
            //printf("zoom in \n");
            gScale += SCALESTEP;
        }
        else {
            printf("interesting \n");
        }
    }
}
