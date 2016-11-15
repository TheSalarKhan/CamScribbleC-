#include "OpenCV.h"
#include "PerspectiveCorrection.h"
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
  PerspectiveCorrection& getPerspectiveCorrection();

private:
  int _subtractFromMean;
  int _averageThreshGridSize;
  int _backgroundAverageThreshold;
  int _desiredMaxIntensity;
  PerspectiveCorrection _persp;
  RunningAverage _accumulator;

  Mat enhanceOutput(Mat mask,Mat originalImage);
};
