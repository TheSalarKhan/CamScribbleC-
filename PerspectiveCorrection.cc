#include "PerspectiveCorrection.h"
using namespace cv;


PerspectiveCorrection::PerspectiveCorrection() {
  _params.tl =
    _params.tr =
    _params.bl =
    _params.br = Point2f(0.0f,0.0f);

  _params.width = _params.height = 0;
}

PerspectiveCorrection::PerspectiveCorrection(PerspectiveCorrectionParams p) {
  _params = p;

  calculateTransformationMatrix();
}

void PerspectiveCorrection::setSurfaceCorners(Point2f tl, Point2f tr, Point2f bl, Point2f br) {
  _params.tl = tl;
  _params.tr = tr;
  _params.bl = bl;
  _params.br = br;

  calculateTransformationMatrix();

}

void PerspectiveCorrection::setOutputWidth(int width) {
  if(width <= 0)
    return;
  _params.width = width;

  calculateTransformationMatrix();
}

void PerspectiveCorrection::setOutputHeight(int height) {
  if(height <= 0)
    return;
  _params.height = height;

  calculateTransformationMatrix();
}


Mat PerspectiveCorrection::applyPerspectiveCorrection(Mat image) {
  Mat toReturn;
  warpPerspective(image, toReturn, _transformationMatrix,
    Size(_params.width,_params.height));
  return toReturn;
}


void PerspectiveCorrection::calculateTransformationMatrix() {
  const Point2f src[] = {_params.tl,_params.tr,_params.bl,_params.br};
  const Point2f dst[] = {
    Point2f(0.0f,0.0f),
    Point2f(_params.width,0.0f),
    Point2f(0.0f,_params.height),
    Point2f(_params.width,_params.height)
  };
  _transformationMatrix = cv::getPerspectiveTransform(src,dst);
}
