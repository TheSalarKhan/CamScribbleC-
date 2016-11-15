#ifndef __NODE_OPENCV_H__
#define __NODE_OPENCV_H__




#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#if CV_MAJOR_VERSION >= 3
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv_modules.hpp>
#endif
#if ((CV_MAJOR_VERSION == 2) && (CV_MINOR_VERSION >=4) && (CV_SUBMINOR_VERSION>=4))
#define HAVE_OPENCV_FACE
#endif

#include <string.h>


#endif
