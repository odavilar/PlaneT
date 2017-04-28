/***************************************************************************//**
 INCLUDES
 *******************************************************************************/
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <opencv2/opencv.hpp>

#include "ImageCapturer.h"
#include "LEDController.h"
#include "Recognizer.h"

#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>

/***************************************************************************//**
 NAMESPACES
 *******************************************************************************/
using namespace std;
using namespace cv;

/***************************************************************************//**
 CONSTANTS
 *******************************************************************************/
#define SAVE_IMAGES

/***************************************************************************//**
 LOCAL VARIABLES
 *******************************************************************************/
ImageCapturer oCapture;
LEDController oLEDS;
RT_TASK TaskCapture;
Recognizer oRecognize;

/***************************************************************************//**

 *******************************************************************************/
void vTaskCapture(void *arg);
void vTaskController(void *arg);

/***************************************************************************//**
 FUNCTION IMPLEMENTATION
 *******************************************************************************/
#if 0
void vCapture(int iSize)
{
	Recognizer oRecognize;
	Mat oFrame;
	vector<Rect> oObject;
#ifdef SAVE_IMAGES
	char sname[30] =
	{	0};
#endif

	if(!oRecognize.boIsLoaded())
	{
		cout << "Failed to load Recognizer" << endl;
		return;
	}

	for (int i = 0, j = 0; i <= iSize;)
	{
		//Get a new frame from camera
		oCapture >> oFrame;
		if(oFrame.empty())
		{
			cout << "Failed to capture an image" << endl;
			return;
		}
		oObject = oRecognize.oDetect(oFrame);

		if(oObject.size() != 0)
		{
#ifdef SAVE_IMAGES
			Mat oMirror;

			rectangle(oFrame, oObject[0], Scalar(0, 0, 255), 2);
			flip(oFrame, oMirror, 1);
			sprintf(sname, "test/test%02d.jpg", i);
			imwrite(sname, oMirror);
			i++;
#endif
			cout << "Hello! :D " << j << endl;
			j++;
			oLEDS.vON();
		}
		else
		{
			oLEDS.vOFF();
		}
	}
}

void vCaptureRT(void)
{
	//OpenCV saves detection rules as something called a CascadeClassifier which
	//can be used to detect objects in images.
	CascadeClassifier oCascade;
	//This variable will hold the image from the camera.
	Mat oFrame;
	//This vector will hold the rectangle coordinates to a detection inside the image.
	vector<Rect> vFaces;

	if(!oCascade.load("lbpcascade_frontalface.xml"))
	{
		cout << "Failed to load cascade classifier" << endl;
		return;
	}

	for (;;)
	{
		//Read an image from the camera.
		oCapture >> oFrame;

		//This function detects the faces in the image and
		// places the rectangles of the faces in the vector.
		//See the detectMultiScale() documentation for more details
		// about the rest of the parameters.
		oCascade.detectMultiScale(oFrame,
				vFaces,
				1.09,
				3,
				0 | CV_HAAR_SCALE_IMAGE,
				Size(30, 30));

		//Here we draw the rectangles onto the image with a red border of thikness 2.
		for(int i = 0; i < vFaces.size(); i++ )
		rectangle(oFrame, vFaces[i], Scalar(0, 0, 255), 2);

		//Mirror Effect
		Mat oMirror;
		flip(oFrame, oMirror, 1);

		//Here we show the drawn image in a named window called "output".
		imshow("output", oMirror);
		waitKey(50);
	}
}
#endif
void vCapture15FPS(void)
{

	Mat oFrame;
	vector < Rect > oObject;
	RTIME now, previous;
	int i = 0;

#ifdef SAVE_IMAGES
	char sname[30] =
	{ 0 };
#endif

	rt_printf("Loading Recognizer\n");

	if (!oRecognize.boIsLoaded())
	{
		rt_printf("Failed to load Recognizer\n");
		return;
	}

	rt_printf("Recognizer Loaded\n");

	rt_task_set_periodic(NULL, TM_NOW, 50000000);
	previous = rt_timer_read();

	while (1)
	{
		rt_task_wait_period(NULL);
		now = rt_timer_read();
		//Get a new frame from camera
		oCapture >> oFrame;
		if (oFrame.empty())
		{
			rt_printf("Failed to capture an image\n");
			oCapture.boConnectToCamera();
		}

		oObject = oRecognize.oDetect(oFrame);

		if (oObject.size() != 0)
		{
#ifdef SAVE_IMAGES
			Mat oMirror;
			rectangle(oFrame, oObject[0], Scalar(0, 0, 255), 2);
			flip(oFrame, oMirror, 1);
			if (i > 15)
			{
				i = 0;
			}
			sprintf(sname, "test/test%02d.jpg", i);
			imwrite(sname, oMirror);
			i++;
#endif
			oLEDS.vON();
		}
		else
		{
			oLEDS.vOFF();
		}

		rt_printf("Time since last turn: %ld.%06ld ms\n",
				(long) (now - previous) / 1000000,
				(long) (now - previous) % 1000000);
		previous = now;
	}
}

void sig_handler(int signo)
{
	cout << "Bye! :(" << endl;

	rt_task_delete(&TaskCapture);

	exit(signo);
}

int main(int argc, const char * argv[])
{

	rt_print_auto_init(1);

	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		cout << "can't catch SIGINT" << endl;
	}

	if (signal(SIGTERM, sig_handler) == SIG_ERR)
	{
		cout << "can't catch SIGINT" << endl;
	}

	mlockall(MCL_CURRENT | MCL_FUTURE);

	cout << "Create Tasks" << endl;

	rt_task_create(&TaskCapture, "Capture", 0, 99, 0);

	if (!oCapture.boIsConnected())
	{
		return -1;
	}
	cout << "Started Processing - Capturing Image" << endl;

	cout << "Start Tasks" << endl;

	rt_task_start(&TaskCapture, &vTaskCapture, NULL);

	pause();

	rt_task_delete(&TaskCapture);

	return 0;
}

void vTaskCapture(void *arg)
{
	rt_printf("Capturing\n");
	vCapture15FPS();
}

void vTaskController(void *arg)
{

}
