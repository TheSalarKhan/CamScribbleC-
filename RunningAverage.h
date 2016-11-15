#include "OpenCV.h"
using namespace cv;

class RunningAverage {
public:
	RunningAverage();
	RunningAverage(float threshold);
	Mat getAverage(Mat image);

private:
  bool _readFirstFrame;
  float _threshold;
  Mat _avg;
};
