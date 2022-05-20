/**
 * @file moisture_sensor.cpp
 * @methods for de moisture sensor
 * @date 23/12/2021
 */
#include "Arduino.h"

#include "moisture_sensor.h"


 void Moisture_sensor::update_value(){
   // Values between 0 - 30
   int reading  = analogRead(pin_in);
   set_value(reading/10);
   increment_cont();
  }
