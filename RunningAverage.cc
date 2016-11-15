#include "RunningAverage.h"
using namespace cv;


RunningAverage::RunningAverage() {}


RunningAverage::RunningAverage(float threshold) {
  _threshold = threshold;
}


Mat RunningAverage::getAverage(Mat image) {
  Mat toReturn;

  // If the size of the input image and
  // _avg is not same. Then discard the
  // already present _avg and replace it
  // with image. Else accumulate the frame
  if(image.rows != _avg.rows || image.cols != _avg.cols) {
	image.convertTo(_avg,CV_32FC3, 1/255.0);
  } else {
	accumulateWeighted(image, _avg, _threshold);
  }

  convertScaleAbs(_avg, toReturn);
  return toReturn;
}
