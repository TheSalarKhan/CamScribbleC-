#ifndef __RUNNING_AVERAGE_H__
#define __RUNNING_AVERAGE_H__

#include "OpenCV.h"
using namespace cv;

class RunningAverage {
public:
	RunningAverage();
	RunningAverage(float threshold);
	Mat getAverage(Mat image);

private:
  float _threshold;
  Mat _avg;
};


#endif
