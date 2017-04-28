#ifndef IMAGECAPTURER_H
#define IMAGECAPTURER_H

/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include <stdio.h>
#include <opencv2/opencv.hpp>

/***************************************************************************//**
NAMESPACES
*******************************************************************************/
using namespace cv;

/***************************************************************************//**
CLASS
*******************************************************************************/
class ImageCapturer
{
private:
    VideoCapture p_oCapture;

public:
    ImageCapturer(void);

    bool boIsConnected(void);
    bool boConnectToCamera(void);
    ImageCapturer& operator>>(Mat& image);

    ~ImageCapturer(void);
};

#endif /* IMAGECAPTURER_H */
