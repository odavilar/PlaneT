#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include <stdio.h>

/***************************************************************************//**
CLASS
*******************************************************************************/
class LEDController
{
    private:
        
    public:
        LEDController(void);
        
        void vON(void);
        void vOFF(void);
        
        ~LEDController(void);
};

#endif /* LEDCONTROLLER_H */
