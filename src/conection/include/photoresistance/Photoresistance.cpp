/**
 * @file Photoresistance.cpp
 * @methods for the Photoresistance
 * @date 23/12/2021
*/

#include "Arduino.h"
#include "sensor.h"
#include "Photoresistance.h"

void Photoresistance::update_value(){
  // Values between 0 - 100
  int reading  = analogRead(pin_in);
  set_value(reading/10); 
  increment_cont();
}
