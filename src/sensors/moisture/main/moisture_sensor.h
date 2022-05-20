/**
 * @file moisture_sensor.h
 * @implementation of an object that inherits from Sensor.h
 * @date 23/12/2021
 */

#ifndef MOISTURE_SENSOR_H_INCLUDED
#define MOISTURE_SENSOR_H_INCLUDED

#include "sensor.h"

class Moisture_sensor:public Sensor{

	public:
    //~Constructor
		Moisture_sensor(int plot_num, int height ,int gpio_in): Sensor(plot_num, height) { pin_in = gpio_in; }

    // update_value() implementation
		virtual void update_value();

  private: // Add pinout
    int pin_in;
};

#endif // MOISTURE_SENSOR_H_INCLUDED
