/**
 * @file dht.h
 * @implementation of a DHT11 sensor that inherits from Sensor.h
 * @date 30/01/2022
 */

#ifndef DHT_H_INCLUDED
#define DHT_H_INCLUDED

#include "sensor.h"

class DHT : public Sensor {

	public:
    //~Constructor
		DHT(int plot_num, int height, int gpio_in): Sensor(plot_num, height) { pin_in = gpio_in; }

    // update_value() implementation
		virtual void update_value();
   
    // inherited value var not used, replaced with local temp and hum
    float get_hum() { return hum; }
    float get_temp() { return temp; }

  private: // Add pinout
    int pin_in;
    float hum;
    float temp;
};



#endif // DHT_H_INCLUDED
