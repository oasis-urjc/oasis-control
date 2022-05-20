#include "actuator.h"

#define PI 3.1415926535897932384626433832795

// Const
const int PLOT_NUM = 1;
const int HEIGHT = 1; 
const int GPIO_IN = 5;
const bool ON = true; 
const bool OFF = false; 
const int WATER_FLOW = 50; 
const int RADIO = 0.277 / 100; //cm to meters 
const int LONG = 3;  // meters 
const double LATENCY = 2.5; // seconds

// const double LATENCY = ((PI *(RADIO * RADIO) * LONG) / ((WATER_FLOW / 3600)/ 1000)); // seconds

// Water flow of the pump: 100L/hour

Actuator pump(PLOT_NUM, HEIGHT, GPIO_IN);

void setup()
{
 Serial.begin(9600);
 pinMode(GPIO_IN, OUTPUT);
}

// Recive liters and pump it 
void pump_water(float liters){
 
  
  double on_time = LATENCY + (liters / WATER_FLOW) * 3600; // seconds 
  double on_time_msecs = on_time * 1000; 

  pump.set_status(ON);

  Serial.println(on_time_msecs);
  
  delay(on_time_msecs);
  
  pump.set_status(OFF); 
}


void loop()
{

  pump_water(1); 

  delay(10000);
  
  
}
