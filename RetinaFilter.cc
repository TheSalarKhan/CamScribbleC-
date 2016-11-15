#include "RetinaFilter.h"
using namespace cv;


RetinaFilter::RetinaFilter() {
  _accumulator = RunningAverage(0.4f);
  _subtractFromMean = 6;
  _averageThreshGridSize = 13;
  _backgroundAverageThreshold = 25;
  _desiredMaxIntensity = 255;
}

RetinaFilter::RetinaFilter(float learningRate) {
  _accumulator = RunningAverage(learningRate);
  _subtractFromMean = 6;
  _averageThreshGridSize = 13;
  _backgroundAverageThreshold = 25;
  _desiredMaxIntensity = 255;
}


void RetinaFilter::setAdaptiveKernelSize(int val) {
  if(val%2 ==1 && val >1 ) {
    _averageThreshGridSize = val;
  }
}

void RetinaFilter::setNoiseSupressionLeveL(int val) {
  _subtractFromMean = val;
}

void RetinaFilter::setBackgroundAveragingThreshold(int val) {
  _backgroundAverageThreshold = val;
}

void RetinaFilter::setBrightness(int val) {
  if(val >= 0 && val <= 255) {
    _desiredMaxIntensity = val;
  }
}

Mat RetinaFilter::enhanceOutput(Mat mask, Mat originalImage) {
  Mat toReturn;

  // original Image should be grayscale.
  // bitwise the (original image + 1) with
  // mask, and invert to get intensity image.
  bitwise_and(mask, originalImage + 1, toReturn);
  toReturn = 255 - toReturn;

  // Where ever there is 255 set it to 0
  threshold(toReturn, toReturn, 244, 0, CV_THRESH_TOZERO_INV);

  // find maximum value in image.
  double mx,temp;
  minMaxLoc(toReturn, &temp, &mx);
  int max = mx;


  int intensityToAdd = _desiredMaxIntensity - max;

  toReturn = toReturn + intensityToAdd;

  // Any values less than zero should be set to zero.
  threshold(toReturn, toReturn, 0, 0, CV_THRESH_TOZERO);

  bitwise_and(mask, toReturn, toReturn);

  return toReturn;

}


Mat RetinaFilter::getFrame(Mat img) {
	cvtColor(img,img,CV_BGR2GRAY);

	GaussianBlur(img,img,Size(3,3),0);

	Mat original;
	img.copyTo(original);

	// We have selected THRESH_BINARY,
	// so that the white bg, becomes 255,
	// and the black ink becomes 0.
	adaptiveThreshold(img,img,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,_averageThreshGridSize,_subtractFromMean);

	// Pass it through averaging filter, to
	// reduce the static noise.
	Mat average = _accumulator.getAverage(img);

	// img[average < _backgroundAverageThreshold] = 255
	threshold(average,img,_backgroundAverageThreshold,255,THRESH_BINARY_INV);

	return enhanceOutput(img,original);
}
