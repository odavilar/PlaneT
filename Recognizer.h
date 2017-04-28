#ifndef RECOGNIZER_H
#define RECOGNIZER_H

/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include <stdio.h>
#include <opencv2/opencv.hpp>

/***************************************************************************//**
NAMESPACES
*******************************************************************************/
using namespace std;
using namespace cv;

/***************************************************************************//**
CLASS
*******************************************************************************/
class Recognizer
{
private:
    bool boInitialized;
    CascadeClassifier p_oCascade;
    
public:
    Recognizer(void);
    
    vector<Rect> oDetect(Mat oFrame);
    bool boIsLoaded(void);
    
    ~Recognizer(void);
};

#endif /* RECOGNIZER_H */
