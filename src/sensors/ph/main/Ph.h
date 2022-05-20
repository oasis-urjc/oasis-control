/**
 * @file ph.h
 * @implementation of a Ph(SEN0161) sensor that inherits from Sensor.h
 * @date 21/02/2022
 */

#ifndef PH_H_INCLUDED
#define PH_H_INCLUDED

#include "Sensor.h"

class PH : public Sensor {

	  public:
    //~Constructor
	  PH(int plot_num, int height, int gpio_in): Sensor(plot_num, height) { pin_in = gpio_in; }

    // update_value() implementation
	  virtual void update_value();

    private: // Add pinout

    // Consts 
    const int MAX_PH = 14;
    const int MIN_PH = 0;
    const int VALUES_WAIT_TIME = 200;  // Time between sensor measurements(ms) 
    const static int NUM_VALUES = 40;  // Number of values measured to make the average
    float Offset = 0.00;

    // Variables
    int pin_in;
    float values[NUM_VALUES];
    
    // Functions
    float average(float* arr);

};

#endif // PH_H_INCLUDED
