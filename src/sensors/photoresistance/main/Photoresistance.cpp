/**
 * @file Photoresistance.cpp
 * @methods for the Photoresistance
 * @date 23/12/2021
 */

#include "Sensor.h"
#include "Photoresistance.h"
#include "Arduino.h"

 void Photoresistance::update_value(){
   // Values between 0 - 100
   int reading  = analogRead(pin_in);
   set_value(reading/10); 
   increment_cont();
  }
