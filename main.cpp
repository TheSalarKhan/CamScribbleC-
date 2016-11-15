#include "OpenCV.h"
#include "RetinaFilter.h"
#include "PerspectiveCorrection.h"
#include <sstream>


using namespace cv;
using namespace std;

RetinaFilter filt;
int adaptiveThresh =0;
int adaptiveKernelSize = 3;
int brightness = 255;

void adaptiveThreshChanged(int,void*) {
	filt.setNoiseSupressionLeveL(adaptiveThresh);
}

void adaptiveKernelSizeChanged(int,void*) {
	filt.setAdaptiveKernelSize(adaptiveKernelSize);
}

void brightnessChanged(int,void*) {
	filt.setBrightness(brightness);
}




/**********************************************************************/
int pointIndex = 0;
Point2f points[4]; // tl,tr,bl,br
void my_mouse_callback( int event, int x, int y, int flags, void* param ) {
    if(event==EVENT_LBUTTONDBLCLK){
    	points[pointIndex++] = Point2f(x,y);
    }
}
void setupPerspectiveTransform(VideoCapture& cap,PerspectiveCorrection& persp) {
	Mat image;
	namedWindow("select four points");
	setMouseCallback("select four points", my_mouse_callback, &image );
	int k;
	while(pointIndex < 4) {
		cap >> image;
		imshow("select four points",image);

		k = waitKey(10) & 0xFF;
		if (k == 27)
			exit(0);
	}

	destroyWindow("select four points");

	PerspectiveCorrectionParams params;
	params.tl = points[0];
	params.tr = points[1];
	params.bl = points[2];
	params.br = points[3];
	params.width = 400;
	params.height = 400;

	persp = PerspectiveCorrection(params);
}
/**********************************************************************/

int main()
{
    int k;
    Mat img;
    ///open video camera
    VideoCapture cap = cv::VideoCapture(1);
    PerspectiveCorrection persp;


    setupPerspectiveTransform(cap,persp);


    if ( !cap.isOpened() )
    {   cout << "Unable to open video file" << endl;    return -1;    }

    cap >> img;
    imshow("image",img);
    createTrackbar("Adaptive thresh","image",&adaptiveThresh,255,adaptiveThreshChanged);
	createTrackbar("Adaptive kernel","image",&adaptiveKernelSize,25,adaptiveKernelSizeChanged);
	createTrackbar("Brightness","image",&brightness,255,brightnessChanged);

    while (1)
    {
        cap >> img;
        if ( img.empty() )
            break;

        //cv::cvtColor(img,img,CV_BGR2GRAY);
        img = persp.applyPerspectiveCorrection(img);
        img = filt.getFrame(img);








        imshow("image", img);
		k = waitKey(10) & 0xFF;
			if (k == 27)
				break;
    }

    return 0;
}
