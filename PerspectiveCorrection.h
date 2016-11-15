#include "OpenCV.h"
using namespace cv;

class PerspectiveCorrectionParams {
public:
  Point2f tl,tr,bl,br;
  int width,height;
};

class PerspectiveCorrection {
public:
  PerspectiveCorrection();
  PerspectiveCorrection(PerspectiveCorrectionParams p);

  void setSurfaceCorners(Point2f tl, Point2f tr, Point2f bl, Point2f br);
  void setOutputWidth(int width);
  void setOutputHeight(int height);

  Mat applyPerspectiveCorrection(Mat image);

private:
  PerspectiveCorrectionParams _params;
  Mat _transformationMatrix;

  void calculateTransformationMatrix();
};
