/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include "ImageCapturer.h"

/***************************************************************************//**
NAMESPACES
*******************************************************************************/
using namespace std;

/***************************************************************************//**
FUNCTION IMPLEMENTATION
*******************************************************************************/
ImageCapturer::ImageCapturer(void)
{
    this->p_oCapture = VideoCapture();
    this->boConnectToCamera();

    if(this->p_oCapture.isOpened())
    {
        /* Set Camera Parameters */
        this->p_oCapture.set(CV_CAP_PROP_FRAME_WIDTH,  320);
        this->p_oCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
        this->p_oCapture.set(CV_CAP_PROP_GAIN, 0);
    }
    else
    {
        cout << "Failed to connect to the camera." << endl;
    }
}

bool ImageCapturer::boIsConnected(void)
{
    return this->p_oCapture.isOpened();
}

ImageCapturer& ImageCapturer::operator>>(Mat& image)
{
    this->p_oCapture >> image;
    return *this;
}

bool ImageCapturer::boConnectToCamera(void)
{
	int iIndex = 0;
    /* Check if Object has already a connection to a Camera */
    if (this->p_oCapture.isOpened())
    {
        /* Release Camera */
        this->p_oCapture.release();
    }

    while ( true && iIndex < 10 ) {
        if ( this->p_oCapture.open(iIndex) ) {
            break;
        }
        else
        {
        	iIndex++;
        }
    }
    std::cout << "devices count : " << iIndex << std::endl;

    /* Return connection status */
    return this->p_oCapture.isOpened();
}

ImageCapturer::~ImageCapturer(void)
{
    this->p_oCapture.release();
}
