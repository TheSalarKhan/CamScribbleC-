#include "RunningAverage.h"
using namespace cv;


RunningAverage::RunningAverage() {}


RunningAverage::RunningAverage(float threshold) {
  _readFirstFrame = false;
  _threshold = threshold;
}


Mat RunningAverage::getAverage(Mat image) {
  Mat toReturn;

  // for the first frame
  // convert the passed frame to float,
  // and store it as average.
  if(_readFirstFrame == false) {
    _readFirstFrame = true;

    image.convertTo(_avg,CV_32FC3, 1/255.0);
    convertScaleAbs(_avg, toReturn);
    return toReturn;
  }

  accumulateWeighted(image, _avg, _threshold);
  convertScaleAbs(_avg, toReturn);
  return toReturn;
}
