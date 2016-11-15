#include "OpenCV.h"
#include "RunningAverage.h"

using namespace cv;
class RetinaFilter {
public:
  RetinaFilter();
  RetinaFilter(float learningRate);

  void setAdaptiveKernelSize(int val);
  void setNoiseSupressionLeveL(int val);
  void setBackgroundAveragingThreshold(int val);
  void setBrightness(int val);
  Mat getFrame(Mat image);


private:
  RunningAverage _accumulator;
  int _subtractFromMean;
  int _averageThreshGridSize;
  int _backgroundAverageThreshold;
  int _desiredMaxIntensity;

  Mat enhanceOutput(Mat mask,Mat originalImage);
};
