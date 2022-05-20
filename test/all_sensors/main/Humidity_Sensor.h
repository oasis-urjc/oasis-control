/**
 * @file Humidity_Sensor.h
 * @implementation of an object that inherits from Sensor.h
 * @date 23/12/2021
 */

#ifndef SENSOR_HUMEDAD_H_INCLUDED
#define SENSOR_HUMEDAD_H_INCLUDED

#include "Sensor.h"


class Humidity_Sensor:public Sensor{

	public:

        //~Constructor
		Humidity_Sensor(int plot_num, int gpio_in): Sensor(plot_num){pin_in = gpio_in;}

        // update_value() implementation
		virtual void update_value();

    private: // Add pinout
      int pin_in;
};



#endif // SENSOR_HUMEDAD_H_INCLUDED
