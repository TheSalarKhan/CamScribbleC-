#include "OpenCV.h"
#include "RetinaFilter.h"
#include "PerspectiveCorrection.h"
#include "BigCanvas.h"
#include <sstream>
#include <iostream>


using namespace cv;
using namespace std;

//RetinaFilter filt;
BigCanvas filt;
int adaptiveThresh =0;
int adaptiveKernelSize = 3;
int brightness = 255;
int width = 50;
int height = 50;

int red = 255;
int green = 255;
int blue = 255;

void adaptiveThreshChanged(int,void*) {
	filt.setNoise(adaptiveThresh);
}

void adaptiveKernelSizeChanged(int,void*) {
	filt.setStrokeWidth(adaptiveKernelSize);
}

void brightnessChanged(int,void*) {
	filt.setBrightness(brightness/255.0);
}

void heightChanged(int,void*) {
	filt.setHeight(height/100.0);

}

void widthChanged(int,void*) {
	filt.setWidth(width/100.0);
}

void colorChanged(int,void*) {
	filt.setInkColor(Point3f(red/255.0,green/255.0,blue/255.0));
}




/**********************************************************************/
int pointIndex = 0;
float imageWidth,imageHeight;
vector<Point2f> points; // tl,tr,bl,br
void my_mouse_callback( int event, int x, int y, int flags, void* param ) {
    if(event==EVENT_LBUTTONDBLCLK){
    	points.push_back(Point2f(x/float(imageWidth),y/float(imageHeight)));
    	pointIndex++;
    }
}

void setupPerspectiveTransform(VideoCapture& cap,BigCanvas& persp) {
	Mat image;
	namedWindow("select four points");
	setMouseCallback("select four points", my_mouse_callback, &image );
	int k;
	while(pointIndex < 4) {
		cap >> image;

		imageWidth = image.cols;
		imageHeight = image.rows;

		imshow("select four points",image);

		k = waitKey(10) & 0xFF;
		if (k == 27)
			exit(0);
	}

	destroyWindow("select four points");


	persp = BigCanvas(Size(400,400),Scalar(0,0,0),points);

}
/**********************************************************************/

int main()
{
    int k;

    Mat img;
    Mat output;

    Mat r,g,b,a;

    Point3f color(0.3,0.4,0.7);
    Point2f position(0.5f,0.5f);


    ///open video camera
    VideoCapture cap = cv::VideoCapture(0);



    setupPerspectiveTransform(cap,filt);


    if ( !cap.isOpened() )
    {   cout << "Unable to open video file" << endl;    return -1;    }

    cap >> img;
    imshow("image",img);

    namedWindow("controls");
    createTrackbar("Adaptive thresh","controls",&adaptiveThresh,255,adaptiveThreshChanged);
	createTrackbar("Adaptive kernel","controls",&adaptiveKernelSize,25,adaptiveKernelSizeChanged);
	createTrackbar("Brightness","controls",&brightness,255,brightnessChanged);

	createTrackbar("Height","controls",&height,100,heightChanged);
	createTrackbar("Width","controls",&width,100,widthChanged);




	createTrackbar("R","controls",&red,255,colorChanged);
	createTrackbar("G","controls",&green,255,colorChanged);
	createTrackbar("B","controls",&blue,255,colorChanged);


    while (1)
    {
        cap >> img;
        if ( img.empty() )
            break;

        filt.getFrame(img,output);

        imshow("image", output);


		k = waitKey(10) & 0xFF;



		switch(k) {
		case 27:
			exit(0);
			break;
		case 'w':
			position.y -= ((position.y+0.1f) >= 0)? 0.1f:0;
			filt.setPosition(position);
			break;
		case 's':
			position.y += ((position.y-0.1f) <= 1)? 0.1f:0;
			filt.setPosition(position);
			break;
		case 'a':
			position.x -= ((position.x-0.1f) >= 0)? 0.1f:0;
			filt.setPosition(position);
			break;
		case 'd':
			position.x += ((position.x+0.1f) <= 1)? 0.1f:0;
			filt.setPosition(position);
			break;
		case 'l':
			filt.lock();
			break;
		case 'u':
			filt.undo();
			break;
		case 'r':
			filt.redo();
			break;
		}

    }

    return 0;
}

