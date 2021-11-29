#include <iostream>
#include <opencv2/opencv.hpp>
#include "rv_param.h"
#include "signalhelper.h"

using namespace std;
using namespace cv;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_MOUSEWHEEL) {
        if (sgn(flags) > 0) {      // zoom out
            gScale -= SCALESTEP;
            if (y > Y0) {
                Y0 += ORIGINSTEP;
            }
            else if (y < Y0) {
                Y0 -= ORIGINSTEP;
            }
        }
        else if (sgn(flags) < 0) { // zoom in
            gScale += SCALESTEP;
            if (y > Y0) {
                Y0 -= ORIGINSTEP;
            }
            else if (y < Y0) {
                Y0 += ORIGINSTEP;
            }
        }
        else {
            printf("interesting \n");
        }
    }
}
