/***************************************************************************//**
INCLUDES
*******************************************************************************/
#include "LEDController.h"
#include <fstream>
#include <string>

/***************************************************************************//**
CONSTANTS
*******************************************************************************/
#define LED0_PATH "/sys/class/leds/beaglebone:green:usr0"
#define LED1_PATH "/sys/class/leds/beaglebone:green:usr1"
#define LED2_PATH "/sys/class/leds/beaglebone:green:usr2"
#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

/***************************************************************************//**
NAMESPACES
*******************************************************************************/
using namespace std;

/***************************************************************************//**
FUNCTION IMPLEMENTATION
*******************************************************************************/
LEDController::LEDController(void)
{
    fstream fs;

    fs.open(LED0_PATH"/trigger", fstream::out);
    fs << "none";
    fs.close();

    fs.open(LED1_PATH"/trigger", fstream::out);
    fs << "none";
    fs.close();

    fs.open(LED2_PATH"/trigger", fstream::out);
    fs << "none";
    fs.close();

    fs.open(LED3_PATH"/trigger", fstream::out);
    fs << "none";
    fs.close();
}

void LEDController::vON(void)
{
    fstream fs;
    
    fs.open(LED0_PATH"/brightness", fstream::out);
    fs << "1";
    fs.close();
    
    fs.open(LED1_PATH"/brightness", fstream::out);
    fs << "1";
    fs.close();
    
    fs.open(LED2_PATH"/brightness", fstream::out);
    fs << "1";
    fs.close();
    
    fs.open(LED3_PATH"/brightness", fstream::out);
    fs << "1";
    fs.close();
}

void LEDController::vOFF(void)
{
    fstream fs;
    
    fs.open(LED0_PATH"/brightness", fstream::out);
    fs << "0";
    fs.close();
    
    fs.open(LED1_PATH"/brightness", fstream::out);
    fs << "0";
    fs.close();
    
    fs.open(LED2_PATH"/brightness", fstream::out);
    fs << "0";
    fs.close();
    
    fs.open(LED3_PATH"/brightness", fstream::out);
    fs << "0";
    fs.close();
}

LEDController::~LEDController(void)
{
    fstream fs;
    
    fs.open(LED0_PATH"/trigger", fstream::out);
    fs << "heartbeat";
    fs.close();
    
    fs.open(LED1_PATH"/trigger", fstream::out);
    fs << "mmc0";
    fs.close();
    
    fs.open(LED2_PATH"/trigger", fstream::out);
    fs << "cpu0";
    fs.close();
    
    fs.open(LED3_PATH"/trigger", fstream::out);
    fs << "mmc1";
    fs.close();
}
