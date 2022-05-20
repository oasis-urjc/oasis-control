/**
 * @file Photoresistance.h
 * @implementation of an object that inherits from Sensor.h 
 * @date 23/12/2021
 */

#ifndef PHOTORESISTANCE_H_INCLUDED
#define PHOTORESISTANCE_H_INCLUDED

#include "Sensor.h"


class Photoresistance:public Sensor{

	public:

    //~Constructor
		Photoresistance(int plot_num, int gpio_in): Sensor(plot_num){pin_in = gpio_in;}

    // update_value() implementation
		virtual void update_value();

    private: // Add pinout
      int pin_in;  
};



#endif // PHOTORESISTANCE_H_INCLUDED
