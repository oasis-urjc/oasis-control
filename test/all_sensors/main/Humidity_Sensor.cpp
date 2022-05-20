/**
 * @file Humidity_Sensor.cpp
 * @methods for de Humidity sensor
 * @date 23/12/2021
 */

#include "Sensor.h"
#include "Humidity_Sensor.h"
#include "Arduino.h"

 void Humidity_Sensor::update_value(){
   // Values between 0 - 30
   int reading  = analogRead(pin_in);
   set_value(reading/10);
   increment_cont();
  }
