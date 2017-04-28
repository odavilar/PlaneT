/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include "Recognizer.h"
#include <rtdk.h>

/***************************************************************************//**
CONSTANTS
*******************************************************************************/
#define CLASSIFIER "lbpcascade_frontalface.xml"

/***************************************************************************//**
NAMESPACES
*******************************************************************************/
using namespace std;

/***************************************************************************//**
FUNCTION IMPLEMENTATION
*******************************************************************************/
Recognizer::Recognizer(void)
{
	rt_printf("Recognizer Constructor\n");

    if(!this->p_oCascade.load(CLASSIFIER))
    {
    	rt_printf("Failed to load cascade classifier\n");
        this->boInitialized = false;
    }
    else
    {
        this->boInitialized = true;
    }
}

vector<Rect> Recognizer::oDetect(Mat oFrame)
{
    vector<Rect> ovResult;

    if(this->boInitialized)
    {
        this->p_oCascade.detectMultiScale(oFrame,
                                          ovResult,
                                          1.09,
                                          3,
                                          0 | CV_HAAR_SCALE_IMAGE,
                                          Size(30, 30));
    }

    return ovResult;
}


bool Recognizer::boIsLoaded(void)
{
    return this->boInitialized;
}

Recognizer::~Recognizer(void)
{

}

